#include "server.h"

/*
** server.c -- a stream socket server demo
*/

int main()
{
    Server server;
    server.init();
    server.get_connect();
}
