#include <iostream>
#include <vector>

#include "CLI.h"

std::string username = "";
std::string password = "";

/**
 * @brief SignUp / SignIn process.
 * 
 * @return int 
 */
int userAuth(){
    std::cout << "[INFO] Please enter your username. (e.g. pop3.163.com)" << std::endl;
    std::cout << "mypop >> ";
    std::cin >> username;
    std::cout << "[INFO] Please enter your password." << std::endl;
    std::cout << "mypop >> ";
    std::cin >> password;

    // Test availability

    if(password.length() == 0 || username.length() == 0) return -1;
    return 1;
}
/**
 * @brief Get a list of messages and sizes
 * 
 * @return int 
 */
int getListOfInfo(){
    std::cout << "[INFO] Fetching email information\n" << std::endl;
    return 1;
};
/**
 * @brief Get Emails' Statuses
 * 
 * @return int 
 */
int getEmailStatuses(){
    std::cout << "[INFO] Fetching email statuses..." << std::endl;
    std::cout << "[INFO] Getting email statuses completed.\n" << std::endl;
    return 1;
}
/**
 * @brief Display mail in detail
 * 
 * @return int 
 */
int displayMailInDetail(){
    std::cout << "[INFO] Loading target email..." << std::endl;
    std::cout << "[INFO] Details printing completed.\n" << std::endl;
    return 1;
}
/**
 * @brief Search text in all mails
 * 
 * @param pattern Target pattern
 * @return int 
 */
int searchTextInAll(std::string &pattern){
    std::vector<std::string> res;

    std::cout << "[INFO] Your target text pattern is: " << pattern << std::endl;

    // Searching process
    res.push_back("test1.eml");
    res.push_back("test2.eml");

    // Display results
    std::cout << "[INFO] Following mails contain target pattern:" << std::endl;
    for(int i = 1; i <= res.size(); i++) printf("%d %s\n", i, res[i - 1].c_str());
    
    std::cout << "[INFO] Pattern matching completed.\n" << std::endl;
    return 1;
}
/**
 * @brief Display by subjects
 * 
 * @return int 
 */
int displayBySubjects(){
    std::cout << "[INFO] Fetching targets by subjects" << std::endl;
    std::cout << "[INFO] Display emails by subjects completed.\n" << std::endl;
    return 1;
}
/**
 * @brief Dowload a mail in the remote service
 * 
 * @return int 
 */
int downloadInRemote(){
    std::cout << "[INFO] Download emails from remote server..." << std::endl;
    std::cout << "[INFO] Download completed.\n" << std::endl;
    return 1;
}
/**
 * @brief Delete a mail in the remote service
 * 
 * @return int 
 */
int deleteInRemote(){
    std::cout << "[INFO] Delete emails from remote server..." << std::endl;
    std::cout << "[INFO] Delete completed.\n" << std::endl;
    return 1;
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
                ret = getListOfInfo();
                if(!ret) std::cout << "[ERROR] Get emails' information failed." << std::endl;
                break;
            // "2. Get mail statuses\n"
            case 2:
                ret = getEmailStatuses();
                if(!ret) std::cout << "[ERROR] Get emails' statuses failed." << std::endl;
                break;
            // "3. Display mail in detail\n"
            case 3:
                ret = displayMailInDetail();
                if(!ret) std::cout << "[ERROR] Display emails in detail failed." << std::endl;
                break;
            // "4. Search text in all mails\n"
            case 4:
                std::cout << "[INFO] Please enter a text pattern: ";
                std::cin >> pattern;

                ret = searchTextInAll(pattern);
                if(!ret) std::cout << "[ERROR] Search text failed." << std::endl;
                break;
            // "5. Display by subjects\n"
            case 5:
                ret = displayBySubjects();
                if(!ret) std::cout << "[ERROR] Display emails in subjects failed." << std::endl;
                break;
            // "6. Download mails in the remote service\n"
            case 6:
                ret = downloadInRemote();
                if(!ret) std::cout << "[ERROR] Downloading emails in remote failed." << std::endl;
                break;
            // "7. Delete mails in the remote service\n"
            case 7:
                ret = deleteInRemote();
                if(!ret) std::cout << "[ERROR] Deleting emails in remote failed." << std::endl;
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