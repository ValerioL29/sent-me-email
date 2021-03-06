/**
 * @brief CLI part for the client
 *
 * @author Jiacheng Li (cheng2029@foxmail.com)
 * @author Zhenglin Xian (617454220@qq.com)
 *
 */
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <termios.h>

#include "lib/conio.h"
#include "lib/config.h"
#include "Socket.h"
#include "Pop3Session.h"
#include "Config.h"
#include "Base64Codec.h"

#define BACKSPACE 127

const std::string beforeAuth =
    "---------------- Welcome! ----------------\n"
    "This is a simple POP3 client application.\n"
    "------------------------------------------\n"
    "Please enter an option number to continue -\n"
    "1. Sign In\n"
    "2. Exit";

const std::string afterAuth =
    "---------------------------------------------\n"
    "Please enter an option number to continue -\n"
    "0. Help\n"
    "1. Get a list of messages and sizes\n"
    "2. Get mail statuses\n"
    "3. Display mail in detail\n"
    "4. Search text in all mails\n"
    "5. Display by subjects\n"
    "6. Download mails in the remote service\n"
    "7. Delete mails in the remote service\n"
    "8. Quit";

std::string hostname = "";
std::string username = "";
std::string password = "";

/**
 * @brief Get the Password with stars
 *
 * @return void
 */
void getPassword()
{
    char ch;

    for (int i = 0;;)
    {
        ch = getch();

        if (ch == BACKSPACE)
        {
            if (i >= 1)
            {
                std::cout << "\b \b";
                password.pop_back();
                i--;
            }
            else
                continue;
        }
        else if (ch != '\n' && ch != '\r')
        {
            std::cout << "*";
            password.push_back(ch);
            i++;
        }
        else
        {
            password[i] = '\0';
            std::cout << std::endl;
            break;
        }
    }
}

/**
 * @brief user authentication test.
 * 
 * @return true Authentication successful.
 * @return false Authentication failed.
 */
bool userAuthentication(){
    std::cout << "[INFO] User authentication Entry" << std::endl;

    std::cout << "[INFO] Please enter your hostname. (e.g. pop3.163.com)" << std::endl;
    std::cout << "mypop >> ";
    std::cin >> hostname;

    std::cout << "[INFO] Please enter your username. (e.g. test02122010)" << std::endl;
    std::cout << "mypop >> ";
    std::cin >> username;
    getchar();

    std::cout << "[INFO] Please enter your password." << std::endl;
    std::cout << "mypop >> ";
    getPassword();

    Pop3Session pop3(hostname, __DEFAULT_PORT);
    bool ret = pop3.authenticate(username, password);

    return ret;
}

/**
 * @brief Get a list of messages and sizes
 *
 * @return void
 */
void getListOfInfo()
{
    std::cout << "[INFO] Fetching email information" << std::endl;

    Pop3Session pop3(hostname, __DEFAULT_PORT);
    pop3.authenticate(username, password);
    pop3.printMessageList();

    std::cout << "[INFO] LIST completed.\n"
              << std::endl;
}
/**
 * @brief Get Emails' Statuses
 *
 * @return void
 */
void getEmailStatuses()
{
    std::cout << "[INFO] Fetching email statuses..." << std::endl;

    Pop3Session pop3(hostname, __DEFAULT_PORT);
    pop3.authenticate(username, password);
    pop3.printStatuses();

    std::cout << "[INFO] Getting email statuses completed.\n"
              << std::endl;
}

/**
 * @brief Display mail in detail
 *
 * @param messageId Target message id
 * @return void
 */
void displayMailInDetail(int messageId)
{
    std::cout << "[INFO] Loading target email..." << std::endl;

    Pop3Session pop3(hostname, __DEFAULT_PORT);
    pop3.authenticate(username, password);
    pop3.retrieveById(messageId, true);

    std::cout << "[INFO] Details printing completed.\n"
              << std::endl;
}
/**
 * @brief Search text in all mails
 *
 * @param pattern Target pattern
 * @return void
 */
void searchTextInAll(std::string &pattern)
{
    std::cout << "[INFO] Your target text pattern is: " << pattern << "\n"
              << std::endl;

    Pop3Session pop3(hostname, __DEFAULT_PORT);
    pop3.authenticate(username, password);

    int len = pop3.getEmaiLength();
    int flag[len + 1] = {0};
    for (int i = 1; i <= len; i++)
    {
        if (pop3.searchTxtInOne(i, pattern))
        {
            flag[i] = 1;
            flag[0]++;

            std::cout << "Email with id: " + std::to_string(flag[0]) + " contains the pattern " << std::endl;
        }
    }

    std::cout << "There is(are) " + std::to_string(flag[0]) + " email(s) containing the pattern" << std::endl;

    std::cout << "\n[INFO] Pattern matching completed.\n"
              << std::endl;
}
/**
 * @brief Display by subjects
 *
 * @return void
 */
void displayBySubjects()
{
    std::cout << "[INFO] Fetching targets by subjects" << std::endl;

    Pop3Session pop3(hostname, __DEFAULT_PORT);
    pop3.authenticate(username, password);
    pop3.printBySubjects();

    std::cout << "[INFO] Display emails by subjects completed.\n"
              << std::endl;
}
/**
 * @brief Dowload a mail in the remote service
 *
 * @return void
 */
void downloadInRemote()
{
    std::cout << "[INFO] Fetching email information..." << std::endl;

    Pop3Session pop3(hostname, __DEFAULT_PORT);
    pop3.authenticate(username, password);
    pop3.printMessageList();

    int messageId;
    std::string savePath;
    std::cout << "[INFO] Please enter the id of the message that you want to download: ";
    std::cin >> messageId;
    std::cout << "[INFO] Please specify the path that you want to save the message to: ";
    std::cin >> savePath;

    std::cout << "[INFO] Download emails from remote server..." << std::endl;
    pop3.saveById(messageId, savePath);
    std::cout << "[INFO] Download completed.\n"
              << std::endl;
}
/**
 * @brief Delete a mail in the remote service
 *
 * @return void
 */
void deleteInRemote()
{
    std::cout << "[INFO] Fetching email information..." << std::endl;

    Pop3Session pop3(hostname, __DEFAULT_PORT);
    pop3.authenticate(username, password);
    pop3.printMessageList();

    int messageId;
    std::cout << "[INFO] Please enter the id of the message that you want to delete: ";
    std::cin >> messageId;

    std::cout << "[INFO] Mark target email from remote server..." << std::endl;
    pop3.markAsDelete(messageId);
    std::cout << "[INFO] Target email is successfully marked to be deleted."
              << std::endl;

    std::string confirm;
    std::cout << "[INFO] Confirm to delete (Enter [y|N]): ";
    std::cin >> confirm;

    if (confirm == "y")
        std::cout << "[INFO] Message deleting complete.\n"
                  << std::endl;
    else
    {
        std::cout << "[INFO] Reset all delete marks.\n"
                  << std::endl;
        pop3.resetDelete();
    }
}
/**
 * @brief After being authorized, loop menu.
 *
 */
void mainMenu()
{
    bool status = true;
    int ret = 0;
    int messageId;
    std::string pattern;

    std::cout << "--------------- Send Me Email ---------------" << std::endl;
    std::cout << "-----------  Username: " << username << "  -----------" << std::endl;
    std::cout << afterAuth << std::endl;

    for (;;)
    {
        int option;

        std::cout << "mypop >> ";
        std::cin >> option;

        switch (option)
        {
            // "0. Help"
            case 0:
                std::cout << "--------------- Send Me Email ---------------" << std::endl;
                std::cout << "-----------  Username: " << username << "  -----------" << std::endl;
                std::cout << afterAuth << std::endl;
                break;
            // "1. Get a list of messages and sizes\n"
            case 1:
                try
                {
                    getListOfInfo();
                }
                catch(Error& e)
                {
                    std::cout << "[ERROR] Unexpected failure." << std::endl;
                }
                
                break;
            // "2. Get mail statuses\n"
            case 2:
                try
                {
                    getEmailStatuses();
                }
                catch(Error& e)
                {
                    std::cout << "[ERROR] Unexpected failure." << std::endl;
                }
                
                break;
            // "3. Display mail in detail\n"
            case 3:
                try
                {
                    std::cout << "[INFO] Please enter target message id: ";
                    std::cin >> messageId;
                    displayMailInDetail(messageId);
                }
                catch(Error& e)
                {
                    std::cout << "[ERROR] Unexpected failure." << std::endl;
                }
                
                break;
            // "4. Search text in all mails\n"
            case 4:
                try
                {
                    std::cout << "[INFO] Please enter a text pattern: ";
                    std::cin >> pattern;
                    searchTextInAll(pattern);
                }
                catch(Error& e)
                {
                    std::cout << "[ERROR] Unexpected failure." << std::endl;
                }
                
                break;
            // "5. Display by subjects\n"
            case 5:
                try
                {
                    displayBySubjects();
                }
                catch(Error& e)
                {
                    std::cout << "[ERROR] Unexpected failure." << std::endl;
                }
                
                break;
            // "6. Download mails in the remote service\n"
            case 6:
                try
                {
                    downloadInRemote();
                }
                catch(Error& e)
                {
                    std::cout << "[ERROR] Unexpected failure." << std::endl;
                }
                
                break;
            // "7. Delete mails in the remote service\n"
            case 7:
                try
                {
                    deleteInRemote();
                }
                catch(Error& e)
                {
                    std::cout << "[ERROR] Unexpected failure." << std::endl;
                }
                
                break;
            // "8. Quit"
            case 8:
                status = false;
                break;
            default:
                std::cout << "[ERROR] Invalid Option! Please enter a number which is given above." << std::endl;
        }

        if (!status)
            break;
    }
}

/**
 * @brief This is the main entry application of our POP3 client.
 *
 * @return void
 */
void mainEntry()
{
    bool status = true;
    bool res = false;

    std::cout << beforeAuth << std::endl;

    for (;;)
    {
        int option;

        std::cout << "mypop >> ";
        std::cin >> option;

        switch (option)
        {
            // 1. Sign in
            case 1:
                try
                {
                    res = userAuthentication();
                }
                catch(Error& e)
                {
                    std::cout << "[ERROR] User authentication failed!" << std::endl;
                }
                

                if (res)
                {
                    std::cout << "[INFO] User authentication completed!" << std::endl;
                    mainMenu();
                }

                status = false;
                break;
            // 2. Exit
            case 2:
                std::cout << "[INFO] Exit code" << std::endl;
                status = false;
                break;
            case 3:

            default:
                std::cout << "[ERROR] Invalid Option! Please enter a number which is given above." << std::endl;
        }

        if (!status)
            break;
    }

    std::cout << "[INFO] Gracefully shutting down POP3 client..." << std::endl;

    return;
}

int main(int argc, char *argv[])
{
    std::cout << "POP3-Client Version " << POP3_VERSION_MAJOR << "." << POP3_VERSION_MINOR << std::endl
              << std::endl;

    // Enter cli application
    mainEntry();

    std::cout << "[INFO] Goodbye!" << std::endl;

    return 0;
}
