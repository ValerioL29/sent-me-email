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

/**
 * @brief SignUp / SignIn process.
 * 
 * @return int 
 */
int userAuth();
/**
 * @brief Get a list of messages and sizes
 * 
 * @return int 
 */
int getListOfInfo();
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
 * @param pattern Target pattern
 * @return int 
 */
int searchTextInAll(std::string &pattern);
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
void mainMenu();
/**
 * @brief This is the main entry application of our POP3 client.
 * 
 */
void mainEntry();