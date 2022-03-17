#ifndef _SHELL_
#define _SHELL_

char exitC[] = "EXIT";
char echoC[] = "ECHO";
char dirC[] = "DIR";
char cdC[] = "CD";
char tcpC[] = "TCP PORT";
char copyC[] = "COPY";
char deleteC[] = "DELETE";


/*
function from util.c file
*/
void print_prompt();
int str_cmp(char* str1, size_t len1, char* str2, size_t len2);
size_t find_space(char* paths);

/*
function from command_helper.c file
*/
char* input_command();
void print_dir(char* dir_path, int* options);
void copy_file(char* from, char* to);

#endif