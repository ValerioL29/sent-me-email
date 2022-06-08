/**
 * @brief Global program configuration
 *
 * @file config.h
 * @author Jiacheng Li (cheng2029@foxmail.com)
 * @author Zhenglin Xian (617454220@qq.com)
 * 
 *  Global configuration macros and values.
 *
 */

#ifndef _CONFIG__H
#define _CONFIG__H

#define __PROGRAM_NAME "pop3-client"

#define __DEFAULT_PORT 110

/* Timeout for reading from socket. In case
   the server doesn't respond */
#define __SOCKET_READ_TIMEOUT 30 // seconds

#endif
