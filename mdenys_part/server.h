//
// Created by Matthos Denys on 7/30/21.
//

#ifndef MDENYS_PART_SERVER_H
#define MDENYS_PART_SERVER_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
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
    struct sigaction _sa;
    socklen_t _sin_size;
    char _s[INET6_ADDRSTRLEN];
    int _rv;
public:
    Server();
    void     init(); // иницилизация сервера
    void     get_connect();
    class CustomException : public std::exception {
        const char* what() const throw();
    };
};


void sigchld_handler(int s);

void *get_in_addr(struct sockaddr *sa);

#endif //MDENYS_PART_SERVER_H
