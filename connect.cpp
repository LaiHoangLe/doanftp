#include "client.h"
#include "socket.h"
#include <winsock2.h>

// ham thuc hien thiet lap ket noi tu socket cua Client den socket cua Server
// + input:  ten cua may server (hostname),  ten dich vu hoac cong dich vu
// + output:  tra ve 1 socket (local socket) da ket noi den server
SOCKET  connectsock(char* hostname, char* service)
{
	struct sockaddr_in  remote; // dia chi socket phia server
	in_addr remote_addr;
	// buoc 1 : Xac dinh dia chi remote socket
	memset(&remote, 0, sizeof(remote));
	remote.sin_family = AF_INET;
	remote_addr = getIPAddressFromHostname(hostname);
	remote.sin_addr.s_addr = remote_addr.s_addr;
	remote.sin_port = getPortFromService(service, "tcp");

	// buoc 2: tao local socket

	SOCKET local = socket(PF_INET, SOCK_STREAM, 0);
	if(local==INVALID_SOCKET)
    {
        errinfo(2, "Khong tao duoc local socket\n");
        return INVALID_SOCKET;
    }


	int r;

	r = connect(local, (struct sockaddr*) &remote, sizeof(remote) )	;

	if(r==SOCKET_ERROR)
    {
        errinfo(3, "Khong ket noi duoc den socket phia Server\n");
        return INVALID_SOCKET;
    }
	return local;
}

