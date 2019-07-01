#ifndef _FTP_CLIENT
#define _FTP_CLIENT

bool connect_server(char* host, char* service);
bool is_connected();

int send_1_message(char msg[]);
int send_2_message(char msg1[], char msg2[]);

int recv_ftp_response();
int recv_epsv();

const char GREETING[] = "Welcome to FTP Client 1.0\nCopyright by Group2_60PM2 (Group2.60PM2@gmail.com)\n";
const char PROMPT[] = "FTP.Client> ";
const char SPACE[]= " ";
// dinh nghia id cua lenh
//
enum cmd_id {help = 0, open, cls, user, pass, dir, mkdir, rmdir, cd, retr, stor, dele, ls, pwd, quit, noop, unknown};

const char* CMD_NAME[] = {"help", "open", "cls", "user", "pass", "dir", "mkdir", "rmdir", "cd", "retr", "stor", "dele", "ls", "pwd", "quit"};
const cmd_id CMD_ID[] = {help, open, cls, user, pass, dir, mkdir, rmdir, cd, retr, stor, dele, ls, pwd, quit};
bool bQuit;


#endif // _FTP_CLIENT
