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
void mainMenu();
/**
 * @brief This is the main entry application of our POP3 client.
 * 
 */
void mainEntry();