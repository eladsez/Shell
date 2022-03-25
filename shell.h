#ifndef _SHELL_
#define _SHELL_

#define TRUE 1
#define FALSE 0
#define STDOUT_FD 1
#define TEMP_STDOUT_FD 500
#define SERVER_PORT 5550
#define SERVER_IP_ADDRESS "127.0.0.1" 
#define ENTER_KEY 0x0A

int client_sock;
int in_server;

/*
Function from util.c file
*/
void print_prompt();
int str_cmp(char* str1, size_t len1, char* str2, size_t len2);
size_t find_space(char* paths);
int count_space(char* str);
void parse_spaces(char* str,char** splited);

/*
Function from command_helper.c file
*/
char* input_command();
void print_dir(char* dir_path, int* options);
void copy_file(char* from, char* to);
void exec(char* command);
void tcp_client();
void close_tcp_client();

#endif