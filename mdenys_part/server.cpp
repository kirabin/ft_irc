//
// Created by Matthos Denys on 7/30/21.
//

#include "server.h"

void Server::init() {
    memset(&_hints, 0, sizeof _hints);
    _hints.ai_family = AF_UNSPEC;
    _hints.ai_socktype = SOCK_STREAM;
    _hints.ai_flags = AI_PASSIVE; // use my IP

    if ((_rv = getaddrinfo(NULL, PORT, &_hints, &_servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(_rv));
        exit(1);
    }

    // loop through all the results and bind to the first we can
    for(_p = _servinfo; _p != NULL; _p = _p->ai_next) {
        if ((_sockfd = socket(_p->ai_family, _p->ai_socktype,
                             _p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &_yes,
                       sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(_sockfd, _p->ai_addr, _p->ai_addrlen) == -1) {
            close(_sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    if (_p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    freeaddrinfo(_servinfo); // all done with this structure

    if (listen(_sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    _sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&_sa.sa_mask);
    _sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &_sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
}

void Server::get_connect() {
    printf("server: waiting for connections...\n");

    while(1) {  // main accept() loop
        _sin_size = sizeof _their_addr;
        _new_fd = accept(_sockfd, (struct sockaddr *)&_their_addr, &_sin_size);
        if (_new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(_their_addr.ss_family,
                  get_in_addr((struct sockaddr *)&_their_addr),
                  _s, sizeof _s);
        printf("server: got connection from %s\n", _s);

        if (!fork()) { // this is the child process
            close(_sockfd); // child doesn't need the listener
            if (send(_new_fd, "Hello, world!", 13, 0) == -1)
                perror("send");
            close(_new_fd);
            exit(0);
        }
        close(_new_fd);  // parent doesn't need this
    }
}

Server::Server() {
    _yes = 1;

}


const char *Server::CustomException::what() const throw() {
    return exception::what();
}


void sigchld_handler(int s)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

void *get_in_addr(struct sockaddr *sa){
if (sa->sa_family == AF_INET) {
return &(((struct sockaddr_in*)sa)->sin_addr);
}

return &(((struct sockaddr_in6*)sa)->sin6_addr);
}