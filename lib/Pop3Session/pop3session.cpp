/**
 * @brief Client part of POP3 session
 *
 * @file pop3session.cpp
 * @author Jiacheng Li (cheng2029@foxmail.com)
 * @author Zhenglin Xian (617454220@qq.com)
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "Pop3Session.h"
#include "Socket.h"
#include "Base64Codec.h"

Pop3Session::Pop3Session()
    : socket(NULL)
{
}

Pop3Session::Pop3Session(std::string const &server, int port)
{
    open(server, port);
}

Pop3Session::~Pop3Session()
{
    close();
}

void Pop3Session::sendCommand(std::string const &command)
{
    socket->write(command + "\r\n");
}

void Pop3Session::getResponse(ServerResponse *response)
{
    std::string buffer;
    socket->readLine(&buffer);

    if (buffer[0] == '+')
    {
        response->status = true;
        buffer.erase(0, 4); // Remove the "+OK "
    }
    else
    {
        response->status = false;
        buffer.erase(0, 5); // Remove the "-ERR "
    }

    response->statusMessage = buffer;
    response->data.clear();
}

void Pop3Session::getMultilineData(ServerResponse *response)
{
    std::string buffer;
    int bytesRead;

    while (true)
    {
        buffer.clear();

        bytesRead = socket->readLine(&buffer);

        if (buffer == "." || bytesRead == 0)
        {
            break;
        }
        else
        {
            if (buffer[0] == '.') /* Strip byte stuffed characters. */
            {
                buffer.erase(0, 1);
            }

            response->data.push_back(buffer);
        }
    }
}

void Pop3Session::open(std::string const &server, int port)
{
    socket = new Socket(server, port);

    ServerResponse welcomeMessage;

    getResponse(&welcomeMessage);

    if (!welcomeMessage.status)
    {
        throw ServerError("Conection refused", welcomeMessage.statusMessage);
    }
}

void Pop3Session::close()
{
    if (socket != NULL)
    {
        sendCommand("QUIT");

        // ServerResponse quitACK;
        // getResponse(&quitACK);

        /* Maybe print a warning when QUIT fails? */

        delete socket;
    }
}

bool Pop3Session::authenticate(std::string const &username, std::string const &password)
{
    ServerResponse response;

    sendCommand("USER " + username);
    getResponse(&response);

    if (!response.status)
    {
        throw ServerError("Authentication failed", response.statusMessage);
    }

    sendCommand("PASS " + password);
    getResponse(&response);

    if (!response.status)
    {
        throw ServerError("Authentication failed", response.statusMessage);
    }

    return response.status;
}

void Pop3Session::printMessageList()

{
    ServerResponse response;

    sendCommand("LIST");

    getResponse(&response);
    if (!response.status)
    {
        throw ServerError("Unable to retrieve message list", response.statusMessage);
    }

    getMultilineData(&response);

    if (response.data.size() == 0)
    {
        std::cout << "No messages available on the server." << std::endl;
    }

    for (std::list<std::string>::iterator line = response.data.begin();
         line != response.data.end();
         line++)
    {
        std::cout << *line << std::endl;
    }
}

void Pop3Session::printStatuses()
{
    ServerResponse response;

    sendCommand("STAT");

    getResponse(&response);
    if (!response.status)
    {
        throw ServerError("Unable to retrieve email statuses", response.statusMessage);
    }

    std::cout << response.statusMessage << std::endl;
}

std::string Pop3Session::retrieveById(int messageId, bool ifshow)
{
    ServerResponse response;

    std::stringstream command;
    command << "RETR " << messageId;

    sendCommand(command.str());

    getResponse(&response);
    if (!response.status)
    {
        throw ServerError("Unable to retrieve requested message", response.statusMessage);
    }

    getMultilineData(&response);

    std::list<std::string>::iterator line = response.data.begin();

    std::string decode_line;

    while (line != response.data.end())
    {
        if (ifshow)
            std::cout << *line << std::endl;

        if (*line == "Content-Transfer-Encoding: base64")
        {
            // skip blank line
            line++;
            line++;

            if (ifshow)
                std::cout << std::endl;

            for (; *line != ""; line++)
            {
                std::string encode_line = *line;
                decode_line = base64_decode(encode_line, true);

                if (ifshow)
                    std::cout << decode_line << std::endl;
            }

            if (ifshow)
                std::cout << *line << std::endl;
        }

        line++;
    }

    return decode_line;
}

void Pop3Session::saveById(int messageId, std::string const &path)
{
    ServerResponse response;

    std::stringstream command;
    command << "RETR " << messageId;

    sendCommand(command.str());

    getResponse(&response);
    if (!response.status)
    {
        throw ServerError("Unable to retrieve requested message", response.statusMessage);
    }

    getMultilineData(&response);

    std::list<std::string>::iterator line = response.data.begin();

    std::fstream fileStream;
    fileStream.open(path, std::ios::out);

    if (fileStream.is_open())
    {
        while (line != response.data.end())
        {
            fileStream << *line << "\n";

            if (*line == "Content-Transfer-Encoding: base64")
            {
                // skip blank line
                line++;
                line++;
                fileStream << "\n";

                for (; *line != ""; line++)
                {
                    std::string encode_line = *line;
                    std::string decode_line = base64_decode(encode_line, true);
                    fileStream << decode_line << "\n";
                }

                fileStream << *line << "\n";
            }

            line++;
        }
        fileStream.close();
    }
    else
    {
        throw FileIOError("Unable to open specified path.");
    }
}

void Pop3Session::markAsDelete(int messageId)
{

    ServerResponse response;

    std::stringstream command;
    command << "DELE " << messageId;
    sendCommand(command.str());

    getResponse(&response);
    if (!response.status)
    {
        throw ServerError("Unable to delete target message", response.statusMessage);
    }

    std::cout << response.statusMessage << std::endl;
}

void Pop3Session::printBySubjects()
{

    ServerResponse response;

    int len = getEmaiLength();

    for (int i = 1; i <= len; i++)
    {
        std::stringstream command;
        command << "RETR " << i;
        sendCommand(command.str());
        getResponse(&response);
        if (!response.status)
        {
            throw ServerError("Unable to retrieve requested message", response.statusMessage);
        }

        getMultilineData(&response);
        std::string spider = response.data.front();
        while (spider != response.data.back())
        {

            if (spider.substr(0, 8) == "Subject:")
            {

                std::string subject = std::to_string(i) + spider.substr(8, spider.length());
                std::cout << subject << std::endl;
            }

            response.data.pop_front();
            spider = response.data.front();
        }
    }
}

bool Pop3Session::searchTxtInOne(int messageId, std::string pattern)
{

    bool re = false;

    std::string content = retrieveById(messageId, false);

    int a = content.find(pattern);

    if (a >= 0)
    {
        re = true;
    }

    return re;
}

int Pop3Session::getEmaiLength()
{

    ServerResponse response;
    sendCommand("STAT");
    getResponse(&response);
    if (!response.status)
    {
        throw ServerError("Unable to retrieve email statuses", response.statusMessage);
    }
    int len = atoi(response.statusMessage.c_str());

    return len;
}
