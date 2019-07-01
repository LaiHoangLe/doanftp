#include <bits/stdc++.h>
#include "client.h"
#include "socket.h"
#include "ftp.h"

using namespace std;

bool is_logon = false;
char* server_address;

// khai bao cac ham se su dung
SOCKET connect(char*,char*);

SOCKET connect_to_send;
bool data_connection = false;

string readPort(string s)
{
    string number = "";

    int last = s.find_last_of('|');
    if(last == string::npos)
        return "";

    while(isdigit(s[last - 1])){
        number = s[last-1] + number;
        last--;
    }
    return number;
}

void send_EPSV(){
    char msg[] = "epsv";
    send_1_message(msg);
    int port = recv_epsv();
    char *p = reinterpret_cast<char *>(port);
    connect_to_send = connectsock(server_address,p);
    printf("%d",port);
    data_connection = true;
}

// Hien_thi_dau_hac_lenh
void showCmdPrompt()
{
    printf("%s",PROMPT);
}

void ClearScreen()
{
    system("cls");
}

// Doc lenh nhap tu ban phim
void readCmd(char * sCmdBuf, int buflen)
{
    fflush(stdin); //xoa stdin truoc khi nhap xau
    fgets(sCmdBuf, buflen, stdin); // doc xau
    int slen = strlen(sCmdBuf); // cat bo '\n' o cuoi xau
    if( slen > 0 && sCmdBuf[slen -1] == '\n')
        sCmdBuf[slen-1] = '\0';
}

cmd_id parseCmd(char *sCmdBuf, char * cmd_argv[], int& cmd_argc)
{
  // phan tich xau ki tu nguoi dung nhap vao de xac dinh lenh va tham so

  // Cu phap:  <ten lenh>space<tham so 1>space<tham so 2>
  //           Moi thanh phan cua lenh cach nhau 1 hoac nhieu dau space
    char * arg;
    cmd_argc = 0; // so tham so = 0
    arg = strtok (sCmdBuf,SPACE); // phan tich xau ki tu trong sCmdBuf
    while (arg != NULL && cmd_argc <10)
    {
        cmd_argv[cmd_argc++] = arg;
        arg = strtok (NULL, SPACE);
    }
    int i;

    if(cmd_argc>0)
    {
        for(i = help; i<= quit; i++)
        {
            if(stricmp(cmd_argv[0],CMD_NAME[i])==0)
                return CMD_ID[i] ;
        }
    } else
        return noop;
    return unknown;
}

void doHelp()
{
    printf("\nCac thao tac duoc ho tro thuc thi:\n");
    printf("%15s  %12s  %12s  %12s \n", "HELP", "QUIT", "CLR", "DISCONNECT");
    printf("%15s  %12s  %12s  %12s \n", "OPEN", "USER", "PASS", "RECV");
    printf("%15s  %12s  %12s  %12s \n", "DIR", "LS", "LCD", "PWD");
    printf("%15s  %12s  %12s  %12s \n", "CD", "MKDIR", "RMDIR", "DELETE");
    printf("\nChuc ban thanh cong!^^\n\n");
}

void doUnknown()
{
    puts("Lenh khong duoc ho tro\nGo lenh help de duoc tro giup");
}

void doQuit()
{
	printf("Chuong trinh ket thuc\n");
    bQuit = true;
} //done
void doPass(char* cmd_argv[], int cmd_argc)
{
    if(cmd_argc == 2)
    {
        send_2_message(cmd_argv[0], cmd_argv[1]);
    }
    else
        {
            printf("Tham so khong hop le!\n");
            return;
        }
    int tmp = recv_ftp_response();
    if (tmp==0){
        is_logon = true;
    }
}

void doDis(char* cmd_argv[], int cmd_argc)
{
    if(cmd_argc == 1)
    {
        if(is_connected()==false)
        {
            printf("Chua ket noi den server!\n");
            return;
        }
        char msg[] = "QUIT";
        send_1_message(msg);
        recv_ftp_response();
        //b_connected = false;
        is_logon = false;
    }
    else
        {
            printf("Tham so khong hop le!\n");
        }
}

void doUser(char* cmd_argv[], int cmd_argc)
{
    if(cmd_argc == 2)
    {
        // kiem tra ket noi.
        if(!is_connected())
        {
            printf("Chua ket noi toi server!\n");
            return;
        }
        if(is_logon){
            char* msg[1];
            msg[0]="quit";
        //    doDis(msg,1);
            is_logon=false;
        }
        // gui ban tin
        send_2_message(cmd_argv[0], cmd_argv[1]);
        int tmp = recv_ftp_response();
        if (tmp==-1){
            return;
        }
        printf("Nhap mat khau: ");
        char cmdBuf[256];
        readCmd(cmdBuf,256);
        char* msg[2];
        msg[0]="pass";
        msg[1]=cmdBuf;
        doPass(msg,2);
    }
    else
    {
        printf("Nhap tham so chua dung!\n");
    }
}
//done


void doOpen(char* cmd_argv[], int cmd_argc)
{
    if(cmd_argc == 3)
    {
        connect_server(cmd_argv[1], cmd_argv[2]);
        server_address = cmd_argv[1];

        int tmp = recv_ftp_response();
        if (tmp==-1){
            return;
        }
        is_logon = false;
        printf("Nhap ten User: ");
        char cmdBuf[256];
        readCmd(cmdBuf,256);
        char* msg[2];
        msg[0]="user";
        msg[1]=cmdBuf;
        doUser(msg,2);
    }else{
        printf("Tham so khong hop le!\n");
    }
}
//
// ham tao moi mot folder
void doMkd(char* cmd_argv[], int cmd_argc)
{
    if(cmd_argc == 2)
    {
        if(is_connected()==false)
        {
            printf("Chua ket noi den server!\n");
            return;
        }
        send_2_message("mkd",cmd_argv[1]);
        recv_ftp_response();
    }
    else
        {
            printf("Tham so khong hop le!\n");
        }
}
//ham xoa folder
void doRmd(char* cmd_argv[], int cmd_argc)
{
    if(cmd_argc == 2)
    {
        if(is_connected()==false)
        {
            printf("Chua ket noi den server!\n");
            return;
        }
        send_2_message("rmd", cmd_argv[1]);
        recv_ftp_response();
    }
    else
        {
            printf("Tham so khong hop le!\n");
        }
}

void doCwd(char* cmd_argv[], int cmd_argc)
{
    if(cmd_argc == 2)
    {
        if(is_connected()== false)
        {
            printf("Chua ket noi toi Server!\n");
            return;
        }
        send_2_message("cwd", cmd_argv[1]);
        recv_ftp_response();
    }else{
        printf("Tham so khong hop le!\n");
    }
}
void doPwd(char* cmd_argv[], int cmd_argc)
{
    if(cmd_argc == 1)
    {
        if(is_connected()== false)
        {
            printf("Chua ket noi toi Server!\n");
            return;
        }
        send_1_message("pwd");
        recv_ftp_response();
    }else{
        printf("Tham so khong hop le!\n");
    }
}

// ham download file tu server
void doRetr(char* cmd_argv[], int cmd_argc)
{
    if(cmd_argc == 2)
    {
        if(is_connected()== false)
        {
            printf("Chua ket noi toi Server!\n");
            return;
        }
        send_EPSV();


        send_2_message("retr",cmd_argv[1]);
        recv_ftp_response();
    }
    else{
        printf("Tham so khong hop le!\n");
    }
}
//
void doStor(char* cmd_argv[], int cmd_argc)
{
    if(cmd_argc==2)
    {
        send_2_message(cmd_argv[0], cmd_argv[1]);
        recv_ftp_response();
    }
    else{
        printf("Tham so khong hop le!\n");
    }
}
//
void doList(char* cmd_argv[], int cmd_argc)
{
    if(cmd_argc==1)
    {
        send_EPSV();
        if (!data_connection){
            return;
        }
        send_1_message("nlst");
        recv_ftp_response();
    }else{
        printf("Tham so khong hop le!\n");
    }
}
//
void doDele(char* cmd_argv[], int cmd_argc)
{
    if(cmd_argc == 2)
    {
        if(is_connected()==false)
        {
            printf("Chua ket noi den server!\n");
            return;
        }
        send_2_message(cmd_argv[0], cmd_argv[1]);
        recv_ftp_response();
    }
    else
        {
            printf("Tham so khong hop le!\n");
        }
}
//

void doCmd(cmd_id id, char * cmd_argv[], int cmd_argc)
{
    switch (id)
    {
        case help: doHelp(); break; //done
        case cls: ClearScreen();break; //done
        case open: doOpen(cmd_argv, cmd_argc);break; //done
        case user: doUser(cmd_argv, cmd_argc);break; //done
        //case pass: doPass(cmd_argv, cmd_argc);break;
        //case disconnect: doDis(cmd_argv, cmd_argc);break; //done
        case cd: doCwd(cmd_argv, cmd_argc);break; //done
        case pwd: doPwd(cmd_argv, cmd_argc);break; //done
        case mkdir: doMkd(cmd_argv, cmd_argc);break;//done
        case rmdir: doRmd(cmd_argv, cmd_argc);break;//done
        case retr: doRetr(cmd_argv, cmd_argc);break;
        case stor: doStor(cmd_argv, cmd_argc);break;
        case ls: doList(cmd_argv, cmd_argc);break;
        case dele: doDele(cmd_argv, cmd_argc);break; //done
        case quit: doQuit(); break; //done
        case noop: break;
        default: doUnknown();break;
    }
}


void run()
{
    char cmdBuf[256];
    char* cmd_ArgArray[10];
    int cmd_ArgCount;
    cmd_id cid;
    bQuit = false;
	puts(GREETING);
	printf("- open <hostname> <port>    ket noi toi FTP Server (cong mac dinh: 21)\n");
    printf("- quit                      thoat khoi chuong trinh FTP Client\n");
    printf("- help                      tro giup \n");
    printf("- cls                       xoa man hinh \n\n");
    while (!bQuit) // chu trinh chinh - MAIN LOOP
    {
        // hien thi dau nhac lenh
        showCmdPrompt();
        // nhap lenh
        readCmd(cmdBuf, 256);
        // phan tich lenh
        cid = parseCmd(cmdBuf, cmd_ArgArray, cmd_ArgCount);
        // thuc hien lenh va hien thi ket qua
        doCmd(cid, cmd_ArgArray, cmd_ArgCount);
    }
}

void run_client()
{
	startWS();

	run();

	endWS();
}
