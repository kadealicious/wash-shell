#ifndef COMMANDS_H_
#define COMMANDS_H_

#define MAX_COMMAND_LENGTH	100
#define MAX_ARGS		10

void WashExit();
void WashEcho(char *tokens[MAX_ARGS]);
void WashPwd();
void WashCd(char* path);
void WashSetPath(char* path);
void WashHelp();

#endif
