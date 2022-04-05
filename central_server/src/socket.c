#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

typedef struct Connection {
    struct sockaddr_in address;
    int socket, opt, address_len;
}Connection;

void socket_configure(int socket_port, char *ip_servidor){

    Connection server;
    server.address_len = sizeof(server.address);
    server.opt = 1;
    if ((server.socket = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        return;
    }


    if (setsockopt(server.socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &server.opt, sizeof(server.opt))) {
        perror("setsockopt");
        return;
    }

    server.address.sin_family = AF_INET;
    server.address.sin_addr.s_addr = INADDR_ANY;
    server.address.sin_port = htons( socket_port );

    if (bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address))<0) {
        perror("bind failed");
        return;
    }

    if (listen(server.socket, 3) < 0) {
        perror("listen");
        return;
    }

    int new_socket, qtde_read;
    if ((new_socket = accept(server.socket, (struct sockaddr *)&server.address, (socklen_t*)&server.address_len))<0) {
        perror("accept");
        return;
    }

    char buffer[1024];

    qtde_read = read(new_socket, buffer, 1024);
}