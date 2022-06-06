/**
 * @brief Client part of POP3 session
 *
 * @file pop3session.cpp
 * @author Jiacheng Li (cheng2029@foxmail.com)
 * 
 */

#include <iostream>
#include <sstream>

#include "Pop3Session.h"
#include "Socket.h"
#include "Base64Codec.h"

// void base64CodecTesting(){
//       // Codec testings

//     bool all_tests_passed = true;
    
//     std::string rest0_original = "abc";
//     std::string rest0_reference = "YWJj";

//     std::string rest0_encoded = base64_encode(reinterpret_cast<const unsigned char*>(rest0_original.c_str()),
//       rest0_original.length());
//     std::string rest0_decoded = base64_decode(rest0_encoded);

//     if (rest0_decoded != rest0_original) {
//       std::cout << "rest0_decoded != rest0_original" << std::endl;
//       all_tests_passed = false;
//     }
//     if (rest0_reference != rest0_encoded) {
//       std::cout << "rest0_reference != rest0_encoded" << std::endl;
//       all_tests_passed = false;
//     }

//     std::cout << "encoded:   " << rest0_encoded << std::endl;
//     std::cout << "reference: " << rest0_reference << std::endl;
//     std::cout << "decoded:   " << rest0_decoded << std::endl << std::endl;

//     return;
// }

Pop3Session::Pop3Session()
    : socket(NULL)
{}

Pop3Session::Pop3Session(std::string const& server, int port)
{
    open(server, port);
}

Pop3Session::~Pop3Session()
{
   close();
}

void Pop3Session::sendCommand(std::string const& command)
{
    socket->write(command + "\r\n");
}

void Pop3Session::getResponse(ServerResponse* response)
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

void Pop3Session::getMultilineData(ServerResponse* response)
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

void Pop3Session::open(std::string const& server, int port)
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

        //ServerResponse quitACK;
        //getResponse(&quitACK);

        /* Maybe print a warning when QUIT fails? */

        delete socket;
    }
}

bool Pop3Session::authenticate(std::string const& username, std::string const& password)
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

    for(std::list<std::string>::iterator line = response.data.begin();
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

void Pop3Session::printMessage(int messageId)
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

    while(line != response.data.end()){
        std::cout << *line << std::endl;

        
        if( *line == "Content-Transfer-Encoding: base64" ){

            response.data.pop_front();
            line = response.data.begin();
            std::list<std::string>::iterator blank_line = line;
            std::cout << *line << std::endl;

            response.data.pop_front();
            line = response.data.begin();
            while(*line != ""){

                std::string encode_line =  response.data.front();
                // std::cout << encode_line << std::endl;
                std::string decode_line =  base64_decode(  encode_line , true );
                std::cout << decode_line << std::endl;

                response.data.pop_front();
                line = response.data.begin();
            }

            std::cout << *line << std::endl;
        }


        response.data.pop_front();
        line = response.data.begin();
             
        
    }
}

