//#include "ftp.h"
#include "socket.h"
#include "client.h"
#include <string.h>
#include <stdio.h>
SOCKET connectsock(char* hostname, char* service);
// thuc thi giao thuc
// kiem tra ket noi thanh cong?
bool b_connected = false;
// tao socket local.
SOCKET local;

bool connect_server(char* host, char* service)
{
    local = connectsock(host, service);
    if(local == INVALID_SOCKET)
    {
        printf("Loi ket noi!\n");
        b_connected = false;
    }
    else
    {
        printf("Ket noi thanh cong!\n");
        b_connected = true;
        // nhan welcome message

    }
    return b_connected;
}
// kiem tra
bool is_connected()
{
    return b_connected;
}
int send_1_message(char msg[])
 {
    char buff[512];
    sprintf(buff,"%s \r\n",msg);
    int len = strlen(buff);
    int r = send(local, buff,len,0);
    if (r!= 0 && r!= SOCKET_ERROR)
     {
         printf("Da gui thanh cong!\n");
         return r;
     }
     else
    {
        printf("Loi gui msg!\n");
        return 0;
    }
 }
//
int send_2_message(char msg1[], char msg2[])
{
    char file_name[512];
    sprintf(file_name,"%s %s\r\n",msg1,msg2);
    int len = strlen(file_name);
    int r = send(local,file_name,len,0);
    if (r!= 0 && r!= SOCKET_ERROR)
    {
         printf("Da gui thanh cong!\n");
         return r;
    }
     else
    {
        printf("Loi gui msg!\n");
        return 0;
    }
}
// ham nhan response tu server
int recv_ftp_response()
{
    char buffer[512];
    int total_byte_recv = 0;
    int byte_recv;
    // nhan lenh
    byte_recv = recv(local, buffer, 512, 0);
    while(byte_recv >0 && byte_recv!=SOCKET_ERROR)
    {
        total_byte_recv += byte_recv;
        // kiem tra nhan dang ket thuc lenh
        if(total_byte_recv>=2 && buffer[total_byte_recv-1]=='\n'&& buffer[total_byte_recv-2]=='\r')
            break;
        else if(total_byte_recv>=512)
            break;
        // Tiep tuc nhan lenh
        byte_recv = recv(local,buffer+total_byte_recv, 1, 0);
    }
    buffer[byte_recv] = '\0';
    puts(buffer);
    if(byte_recv==SOCKET_ERROR)
    {
        return -1;
    }
    else if(byte_recv==0)
    {
        errinfo(-2, "Connection closed\n");
        return -2;
    }
}
