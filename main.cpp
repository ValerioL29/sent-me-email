/**
 * @brief CLI part for the client
 *
 * @file CLI.h
 * @author Jiacheng Li (cheng2029@foxmail.com)
 * 
 */
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <termios.h>

#include "../config.h"
#include "Socket.h"
#include "Pop3Session.h"
#include "Config.h"
#include "Base64Codec.h"

const std::string beforeAuth = 
    "---------------- Welcome! ----------------\n"
    "This is a simple POP3 client application.\n"
    "------------------------------------------\n"
    "Please enter an option number to continue -\n"
    "1. Sign In\n"
    "2. Exit"
;

const std::string afterAuth = 
    "---------------------------------------------\n"
    "Please enter an option number to continue -\n"
    "1. Get a list of messages and sizes\n"
    "2. Get mail statuses\n"
    "3. Display mail in detail\n"
    "4. Search text in all mails\n"
    "5. Display by subjects\n"
    "6. Download mails in the remote service\n"
    "7. Delete mails in the remote service\n"
    "8. Quit"
;

std::string username = "";
std::string password = "";

/**
 * @brief Get a list of messages and sizes
 * 
 */
void getListOfInfo(){
    std::cout << "[INFO] Fetching email information\n" << std::endl;
};
/**
 * @brief Get Emails' Statuses
 * 
 */
void getEmailStatuses(){
    std::cout << "[INFO] Fetching email statuses..." << std::endl;
    std::cout << "[INFO] Getting email statuses completed.\n" << std::endl;
}
/**
 * @brief Display mail in detail
 * 
 */
void displayMailInDetail(){
    std::cout << "[INFO] Loading target email..." << std::endl;
    std::cout << "[INFO] Details printing completed.\n" << std::endl;
}
/**
 * @brief Search text in all mails
 * 
 * @param pattern Target pattern
 */
void searchTextInAll(std::string &pattern){
    std::vector<std::string> res;

    std::cout << "[INFO] Your target text pattern is: " << pattern << std::endl;

    // Searching process
    res.push_back("test1.eml");
    res.push_back("test2.eml");

    // Display results
    std::cout << "[INFO] Following mails contain target pattern:" << std::endl;
    for(int i = 1; i <= res.size(); i++) printf("%d %s\n", i, res[i - 1].c_str());
    
    std::cout << "[INFO] Pattern matching completed.\n" << std::endl;
}
/**
 * @brief Display by subjects
 * 
 */
void displayBySubjects(){
    std::cout << "[INFO] Fetching targets by subjects" << std::endl;
    std::cout << "[INFO] Display emails by subjects completed.\n" << std::endl;
}
/**
 * @brief Dowload a mail in the remote service
 * 
 */
void downloadInRemote(){
    std::cout << "[INFO] Download emails from remote server..." << std::endl;
    std::cout << "[INFO] Download completed.\n" << std::endl;
}
/**
 * @brief Delete a mail in the remote service
 * 
 */
void deleteInRemote(){
    std::cout << "[INFO] Delete emails from remote server..." << std::endl;
    std::cout << "[INFO] Delete completed.\n" << std::endl;
}
/**
 * @brief After being authorized, loop menu.
 * 
 */
void mainMenu(){
    bool status = true;
    int ret = 0;
    std::string pattern;

    std::cout << "--------------- Send Me Email ---------------" << std::endl;
    std::cout << "----------  Username: " << username << "  ---------" << std::endl;
    std::cout << afterAuth << std::endl;

    for(;;){
        int option;
        
        std::cout << "mypop >> ";
        std::cin >> option;

        switch(option){
            // "1. Get a list of messages and sizes\n"
            case 1:
                getListOfInfo();
                break;
            // "2. Get mail statuses\n"
            case 2:
                getEmailStatuses();
                break;
            // "3. Display mail in detail\n"
            case 3:
                displayMailInDetail();
                break;
            // "4. Search text in all mails\n"
            case 4:
                std::cout << "[INFO] Please enter a text pattern: ";
                std::cin >> pattern;

                searchTextInAll(pattern);
                break;
            // "5. Display by subjects\n"
            case 5:
                displayBySubjects();
                break;
            // "6. Download mails in the remote service\n"
            case 6:
                downloadInRemote();
                break;
            // "7. Delete mails in the remote service\n"
            case 7:
                deleteInRemote();
                break;
            // "8. Quit"
            case 8:
                status = false;
                break;
            default:
                std::cout << "[ERROR] Invalid Option! Please enter a number which is given above." << std::endl;
        }

        if(!status) break;
    }
}
/**
 * @brief This is the main entry application of our POP3 client.
 * 
 */
void mainEntry(){
    bool status = true;
    bool res = false;

    std::cout << beforeAuth << std::endl;

    for(;;){
        int option;

        std::cout << "mypop >> ";
        std::cin >> option;

        switch(option){
            // 1. Sign in
            case 1:
                std::cout << "[INFO] User authentication Entry" << std::endl;
                std::cout << "[INFO] Please enter your username. (e.g. pop3.163.com)" << std::endl;
                std::cout << "mypop >> ";
                std::cin >> username;
                std::cout << "[INFO] Please enter your password." << std::endl;
                std::cout << "mypop >> ";
                std::cin >> password;

                /* Process user's request. */
                try
                {
                    Pop3Session pop3(username, __DEFAULT_PORT);
                    res = pop3.authenticate(username, password);

                    // password.clear(); // Remove password from memory
                }
                catch (Error& error)
                {
                    std::cerr << error.what() << std::endl;
                    exit(EXIT_FAILURE);
                }

                if(!res) std::cout << "[ERROR] User authentication failed!" << std::endl;
                else{
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
            default:
                std::cout << "[ERROR] Invalid Option! Please enter a number which is given above." << std::endl;
        }

        if(!status) break;
    }

    std::cout << "[INFO] Gracefully shutting down POP3 client..." << std::endl;

    return;
}

void base64CodecTesting(){
      // Codec testings

    bool all_tests_passed = true;
    
    std::string rest0_original = "abc";
    std::string rest0_reference = "YWJj";

    std::string rest0_encoded = base64_encode(reinterpret_cast<const unsigned char*>(rest0_original.c_str()),
      rest0_original.length());
    std::string rest0_decoded = base64_decode(rest0_encoded);

    if (rest0_decoded != rest0_original) {
      std::cout << "rest0_decoded != rest0_original" << std::endl;
      all_tests_passed = false;
    }
    if (rest0_reference != rest0_encoded) {
      std::cout << "rest0_reference != rest0_encoded" << std::endl;
      all_tests_passed = false;
    }

    std::cout << "encoded:   " << rest0_encoded << std::endl;
    std::cout << "reference: " << rest0_reference << std::endl;
    std::cout << "decoded:   " << rest0_decoded << std::endl << std::endl;

    return;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {        // report version
        std::cout << argv[0] << " Version " << POP3_VERSION_MAJOR << "."
                  << POP3_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }

    // Enter cli application
    mainEntry();

    std::cout << "[INFO] Goodbye!" << std::endl;

    return 0;
}

