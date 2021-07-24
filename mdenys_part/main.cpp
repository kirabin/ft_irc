#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>


/*
 *
 * Everything in C++ 98. socket, setsockopt,
getsockname, getprotobyname, gethostbyname,
getaddrinfo, freeaddrinfo, bind, connect, listen,
accept, htons, htonl, ntohs, ntohl, inet_addr,
inet_ntoa, send, recv, signal, lseek, fstat,fcntl,
poll (or equivalent)
 *
 */


#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    std::string hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    memset(address.sin_zero, '\0', sizeof address.sin_zero);


    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        std::cout <<  "In bind" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        std::cout << "In listen" << std::endl;
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        std::cout << "\n+++++++ Waiting for new connection ++++++++\n\n";
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            std::cout << "In accept" << std::endl;
            exit(EXIT_FAILURE);
        }
        char buffer[30000] = {0};
        valread = read( new_socket , buffer, 30000);
        std::cout << buffer << std::endl;
        write(new_socket , hello.c_str() , hello.length());
        close(new_socket);
    }
    return 0;
}