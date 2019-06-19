#ifndef _CLIENT_H_
#define _CLIENT_H_
#include <winsock2.h>

#define CMD_MAX_LEN 20
#define CMD_MAX_NUM 15
#define CMD_MAX_ARG_NUM 16
#define BUF_LEN 256

#define CMD_NOOP_ID  CMD_MAX_NUM +1
#define CMD_UNKNOWN_ID  CMD_MAX_NUM
#define CMD_QUIT_ID CMD_MAX_NUM + 3

typedef void (*DO_CMD_FUNC)(char*[], int);

void setCmdPrompt(const char* prompt);
void addCmd(const char* name, DO_CMD_FUNC f);
void clearScreen();
void showCmdPrompt();
void readCmd(char* cmd_buf, int buflen);
//int parseCmd(char *cmd_buf, char * cmd_argv[], int& cmd_argc);
void run_client();

#endif
