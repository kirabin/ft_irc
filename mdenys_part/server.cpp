//
// Created by Matthos Denys on 7/30/21.
//

#include <iostream>
#include "server.hpp"

void Server::init() {
    memset(&_hints, 0, sizeof _hints);
    _hints.ai_family = AF_UNSPEC;
    _hints.ai_socktype = SOCK_STREAM;
    _hints.ai_flags = AI_PASSIVE; // use my IP

    if ((_rv = getaddrinfo(NULL, PORT, &_hints, &_servinfo)) != 0) {
        std::cerr << "getaddrinfo:" << gai_strerror(_rv) << std::endl;
        exit(1);
    }
    // loop through all the results and bind to the first we can
    for(_p = _servinfo; _p != NULL; _p = _p->ai_next)
    {
        if ((_sockfd = socket(_p->ai_family, _p->ai_socktype, _p->ai_protocol)) == -1)
        {
             std::cerr << "server: socket";
            continue;
        }
        if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &_yes, sizeof(int)) == -1)
        {
             std::cerr << "setsockopt";
            return;
            // здесь был exit
        }
        if (bind(_sockfd, _p->ai_addr, _p->ai_addrlen) == -1)
        {
            close(_sockfd);
             std::cerr << "server: bind";
            continue;
        }
        break;
    }
    if (_p == NULL)  {
        std::cerr << "server: failed to bind" << std::endl;
        return;
        // здесь был exit
    }
    freeaddrinfo(_servinfo); // all done with this structure
    if (listen(_sockfd, BACKLOG) == -1) {
        std::cerr << "listen";
        return;
      // здесь был exit
    }
}

_Noreturn void Server::get_connect() {
    std::cout << "server: waiting for connections..." << std::endl;

    while(1) {  // main accept() loop
        _sin_size = sizeof _their_addr;
        _new_fd = accept(_sockfd, (struct sockaddr *)&_their_addr, &_sin_size);
        if (_new_fd == -1) {
             std::cerr << "accept";
            continue;
        }
        inet_ntop(_their_addr.ss_family, get_in_addr((struct sockaddr *)&_their_addr), _s, sizeof _s);
        std::cout << "server: got connection from" << _s << std::endl;
        this->send_message("Повседневная практика показывает, что укрепление и развитие структуры обеспечивает широкому кругу (специалистов) участие в формировании дальнейших направлений развития. С другой стороны рамки и место обучения кадров способствует подготовки и реализации модели развития.\n"
                           "Повседневная практика показывает, что реализация намеченных плановых заданий в значительной степени обуславливает создание модели развития. Равным образом рамки и место обучения кадров влечет за собой процесс внедрения и модернизации системы обучения кадров, соответствует насущным потребностям.\n"
                           "Равным образом консультация с широким активом требуют определения и уточнения модели развития. . Если у вас есть какие то интересные предложения, обращайтесь! Студия Web-Boss всегда готова решить любую задачу. Равным образом рамки и место обучения кадров влечет за собой процесс внедрения и модернизации системы обучения кадров, соответствует насущным потребностям.");
        close(_new_fd);  // parent doesn't need this
    }
}

Server::Server() {
    _yes = 1;
}

void Server::send_message(std::string str) {
    if (send(this->_new_fd, str.c_str(), str.size(), 0) == -1)
        std::cerr << "send";
}

const char *Server::CustomException::what() const throw() {
    return exception::what();
}

void *get_in_addr(struct sockaddr *sa){
if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in*)sa)->sin_addr);
}
return &(((struct sockaddr_in6*)sa)->sin6_addr);
}