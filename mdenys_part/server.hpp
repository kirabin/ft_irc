//
// Created by Matthos Denys on 7/30/21.
//

#ifndef MDENYS_PART_SERVER_HPP
#define MDENYS_PART_SERVER_HPP


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <exception>
#define PORT "3490"
#define BACKLOG 10


class Server {
private:
    int _yes;
    int _sockfd, _new_fd;
    struct addrinfo _hints, *_servinfo, *_p;
    struct sockaddr_storage _their_addr;
    socklen_t _sin_size;
    char _s[INET6_ADDRSTRLEN];
    int _rv;
public:
    Server();
    void     init(); // иницилизация сервера
    _Noreturn void     get_connect(); // ожидание подключений
    class CustomException : public std::exception {
        const char* what() const throw();
    };
    void send_message(std::string str);
};


void *get_in_addr(struct sockaddr *sa);

#endif //MDENYS_PART_SERVER_HPP
