#ifndef _SHELL_
#define _SHELL_

#define TRUE 1
#define FALSE 0
#define STDOUT_FD 1
#define TEMP_STDOUT_FD 888
#define SERVER_PORT 5550
#define SERVER_IP_ADDRESS "127.0.0.1"
#define ENTER_KEY 0x0A

int client_sock;
int in_server;

/*
Function from util.c file
*/
void print_prompt();

int str_cmp(char *str1, size_t len1, char *str2, size_t len2);

size_t find_space(char *paths);

int count_chars(char *str, char to_count);

void parse_str(char *str, char **splited, char *parse_by);

/*
Function from command_helper.c file
*/
char *input_command();

void print_dir(char *dir_path, int *options);

void copy_file(char *from, char *to);

void exec_no_pipe(char *command);

void pipe_control(char *command);

void tcp_client();

void close_tcp_client();

#endif