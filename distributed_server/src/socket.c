#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>


struct sockaddr_in server_address;
int local_socket, opt = 1;

void socket_configure(int socket_port, char *ip_servidor){
    if ((local_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        return;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons( socket_port );

    if(inet_pton(AF_INET, ip_servidor, &server_address.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return;
    }

    if (connect(local_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        printf("\nConnection Failed \n");
        return;
    }
}

void socket_send_string(char *buffer){
    int teste = send(local_socket, (void *)buffer, strlen(buffer), 0);
    printf("Send %d bytes\n", teste);
}