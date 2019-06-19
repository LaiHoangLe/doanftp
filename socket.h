#ifndef SOCKET_H
#define SOCET_H
#include <winsock2.h>

void startWS();
void endWS();

in_addr getIPAddressFromHostname(char* hostname);
u_short getPortFromService(char* service, char * sock_type);

void errexit(int code, char* msg);
void errinfo(int code, char* msg);

#endif // SOCKET_H
