# SentMeEmail

## Introduction
📨 - A POP3 email application in C/C++.

> Goals -
>
> 1. Communicate with pop3 server.
> 2. Store Email in `*.eml` format.
> 3. Friendly user interface and good interactive user experience.

## Project Structure

```
Sent Me Email
├── CMakeLists.txt
├── Config.h.in
├── README.md
├── build
│   └── pop3-client
├── lib
│   ├── Base64Codec
│   │   ├── Base64Codec.h
│   │   ├── CMakeLists.txt
│   │   └── base64.cpp
│   ├── Error
│   │   ├── CMakeLists.txt
│   │   ├── Error.h
│   │   └── error.cpp
│   ├── Pop3Session
│   │   ├── CMakeLists.txt
│   │   ├── Pop3Session.h
│   │   └── pop3session.cpp
│   ├── Socket
│   │   ├── CMakeLists.txt
│   │   ├── Socket.h
│   │   └── socket.cpp
│   └── config.h
│   └── conio.h
├── main.cpp
└── resources
```

## How to Run this project

1. Install `cmake 3.0.0` or higher version
2. Execute `cmake --build build` to build
3. Run `build/pop3-client` to start client application, enjoy!

## Function Requirements

#### Basic

- [x] Connect POP3 server on port ***110***
- [x] Guide user to login and show information about their mails
- [x] Display prompt characters such as `mypop >`
- [x] Can display content of mails in terminal
- [x] The communication procedure can be captured by Wireshark

#### Advanced

- [x] Login with implicit password (replace your password by `****`)
- [x] Can download mails and save them only on local machine  (remove from remote server)
- [x] Provide function "Display by subject"
- [x] Provide function "Search text in all mails"
