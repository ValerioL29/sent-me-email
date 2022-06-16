/**
 * @brief Error handling and reporting tools
 *
 * @file Error.h
 * @author Jiacheng Li (cheng2029@foxmail.com)
 * @author Zhenglin Xian (617454220@qq.com)
 * 
 */

#ifndef _ERROR__H
#define _ERROR__H


#include <stdexcept>
#include <string>

/**
 * @brief Base class for errors and exceptions.
 *
 *  All exceptions in this program should be derived
 *  from this class.
 */
class Error : public std::exception
{
    public:
        std::string programName;
        std::string problem;
        std::string reason;

    public:
        Error(std::string what = "", std::string why = "");
        virtual ~Error() throw();
        
        /**
         * @brief Get error report
         *
         *  Return an error report in the following format:
         *      <programName>: <problem>: <reason>
         *
         * @return Error report.
         */
        const char* what() const throw();
};

#endif
