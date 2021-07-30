//
// Created by Matthos Denys on 7/30/21.
//

#ifndef MDENYS_PART_SERVER_H
#define MDENYS_PART_SERVER_H


#include <netdb.h>

class server {
private:
    int _port;
    struct addrinfo _hints, *_servinfo, *_p;
    struct sockaddr_storage _their_addr;
public:
    int     init(); // иницилизация сервера
};


#endif //MDENYS_PART_SERVER_H
