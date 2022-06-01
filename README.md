# SentMeEmail

#### 0. Introduction
📨 - A POP3 email application in C/C++.

> Goals -
>
> 1. Receive Email from pop3 server.
> 2. Store Email in `*.eml` format.
> 3. Friendly user interface and good interactive user experience.

## Project Structure

```

```

## How to Run this project

1. Install `cmake 3.0.0` or higher version
2. Execute `cmake --build build` to build
3. Run `./build/pop3-client` to start client application, enjoy!

## Function Requirements

#### Basic

- [ ] Connect POP3 server on port ***110***
- [ ] Guide user to login and show information about their mails
- [ ] Display prompt characters such as `mypop >`
- [ ] Can display content of mails in terminal
- [ ] The communication procedure can be captured by Wireshark

#### Advanced

- [ ] Login with implicit password (replace your password by `****`)
- [ ] Can download mails and save them only on local machine  (remove from remote server)
- [ ] Provide function "Display by subject"
- [ ] Provide function "Search text in all mails"