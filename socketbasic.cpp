#include "socket.h"
#include <winsock2.h>
#include "stdio.h"

// ham khoi dong Winsock 2
void startWS()
{
	WSAData wsData;
	int r; // nhan ket qua goi ham API

	r = WSAStartup(MAKEWORD(2,2), &wsData);
	if(r!=0) // loi khoi tao WS
		errexit(1, "Khong khoi tao duoc Win Sock\n");
}

// Ham giai phong WS
void endWS()
{
	WSACleanup();
}

// Ham lay dia chi IP tu ten hostname
// + input :  ten host hoac la dia chi IP dang "192.168.0.1"
// + output:  dia chi IP 4 byte theo cau truc struct in_addr

in_addr getIPAddressFromHostname(char* hostname)
{
	struct hostent* phost;
	in_addr address;

	phost = gethostbyname(hostname);
	if(phost!=NULL)
	{
		u_long*  temp = (u_long*) phost->h_addr_list[0];
		address.s_addr = *temp;
	}
    else
    	address.s_addr = inet_addr(hostname); // chuyen tu dang "192.168.0.1" sang in_addr

	return address;
}

// Ham lay so cong port theo ten cua dich vu (service)
// +input:  ten service ("ftp", "http", "echo") hoac so cong duoi dang xau ("21", "80', "7")
// +output: so cong port duoi dang NBO (2 byte)

u_short getPortFromService(char* service, char * sock_type)
{
	 struct servent *pserv;
	 u_short port;

	 pserv = getservbyname(service, sock_type);

	 if(pserv!= NULL)
	   	port = pserv->s_port;
	 else // neu khong tim duoc cong : chuyen tu xau sang so
	 	port = htons(atoi(service));

	 return port;
}
