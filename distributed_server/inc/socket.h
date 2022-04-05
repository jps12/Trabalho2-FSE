#ifndef _SOCKET_H_
#define _SOCKET_H_

void socket_configure(int socket_port, char *ip_servidor);
void socket_send_string(char *buffer);

#endif // _SOCKET_H_