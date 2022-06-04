#include <iostream>

#include "CLI.h"

std::string username = "default";
std::string password = "default";

std::string beforeAuth = 
    "---------------- Welcome! ----------------\n"
    "This is a simple POP3 client application.\n"
    "------------------------------------------\n"
    "Please enter an option number to continue -\n"
    "1. Sign In\n"
    "2. Sign Up\n"
    "3. Exit"
;

std::string afterAuth = 
    "--------------- Send Me Email ---------------\n"
    "----\tUser: " + username + "\t----\n"
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

/**
 * @brief SignUp / SignIn process.
 * 
 * @return int 
 */
int userAuth(){
    std::cout << "[INFO] Your username is >> ";
    std::cin >> username;
    std::cout << "[INFO] Your password is >> ";
    std::cin >> password;

    if(password.length() > 9) return -1;
    return 1;
}
/**
 * @brief Get a list of messages and sizes
 * 
 * @return int 
 */
int getListOfInfo(){
    std::cout << "[INFO] Fetching emails' information" << std::endl;
    return 1;
};
/**
 * @brief Get Emails' Statuses
 * 
 * @return int 
 */
int getEmailStatuses();
/**
 * @brief Display mail in detail
 * 
 * @return int 
 */
int displayMailInDetail();
/**
 * @brief Search text in all mails
 * 
 * @return int 
 */
int searchTextInAll();
/**
 * @brief Display by subjects
 * 
 * @return int 
 */
int displayBySubjects();
/**
 * @brief Dowload a mail in the remote service
 * 
 * @return int 
 */
int downloadInRemote();
/**
 * @brief Delete a mail in the remote service
 * 
 * @return int 
 */
int deleteInRemote();
/**
 * @brief After being authorized, loop menu.
 * 
 */
void mainMenu(){
    bool status = true;
    int ret = 0;

    std::cout << afterAuth << std::endl;

    for(;;){
        int option;
        
        std::cout << "mypop >> ";
        std::cin >> option;

        switch(option){
            // "1. Get a list of messages and sizes\n"
            case 1:
                ret = getListOfInfo();
                if(!ret) std::cout << "[ERROR] Get emails' information failed." << std::endl;
                break;
            // "2. Get mail statuses\n"
            case 2:
                break;
            // "3. Display mail in detail\n"
            case 3:
                break;
            // "4. Search text in all mails\n"
            case 4:
                break;
            // "5. Display by subjects\n"
            case 5:
                break;
            // "6. Download mails in the remote service\n"
            case 6:
                break;
            // "7. Delete mails in the remote service\n"
            case 7:
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
    int ret = 0;

    std::cout << beforeAuth << std::endl;

    for(;;){
        int option;

        std::cout << "mypop >> ";
        std::cin >> option;

        switch(option){
            // 1. Sign in
            case 1:
                std::cout << "[INFO] User authentication Entry" << std::endl;
                ret = userAuth();
                if(!ret) std::cout << "[ERROR] User authentication failed. Please make sure you own a valid account" << std::endl;
                else{
                    std::cout << "[INFO] User authentication completed!" << std::endl;
                    mainMenu();
                    status = false;
                }
                break;
            // 2. Sign up
            case 2:
                // display after signing in info
                std::cout << "[INFO] Sign up process!" << std::endl;
                break;
            // 3. Exit
            case 3:
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