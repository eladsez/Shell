#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"

void print_prompt(){
    char cwd[PATH_MAX]; // PATH_MAX taken from limits.h
    FILE* copy_stdout;

    if (in_server){
        copy_stdout = fdopen(TEMP_STDOUT_FD, "w");
    }
    else{
        copy_stdout = stdout;
    }
 
   if (getcwd(cwd, sizeof(cwd)) != NULL){
       fprintf(copy_stdout, "\033[1;35m");
       if (in_server)
           fprintf(copy_stdout, "user@server");
       else
           fprintf(copy_stdout, "user@myshell"); 
       fprintf(copy_stdout, "\033[1;36m");
       fprintf(copy_stdout, ":~%s$ ", cwd);
       fprintf(copy_stdout, "\033[0;37m");
   } 

   else{
       perror("cwd ERROR");
       exit(1);
    }
}


int str_cmp(char* str1, size_t len1, char* str2, size_t len2){
    if (len1 != len2)
        return FALSE;

    for (size_t i = 0; i < len1; ++i){
        if (str1[i] != str2[i])
            return FALSE;
    }
    return TRUE;
}

size_t find_space(char* paths){
    for (size_t i = 0; i < strlen(paths); ++i){
        if (paths[i] == ' ')
            return i;
    }

    return -1;
}

int count_space(char* str){
    int count = 0;
    for (int i =0; i < strlen(str); ++i){
        if (str[i] == ' ')
            ++count;
    }
    return count;
}

void parse_spaces(char** str, char*** splited){
    int index = 0;
    char* temp;
    temp = strtok(*str, " ");

    while (temp != NULL){
        (*splited)[index++] = temp;
        temp = strtok(NULL, " ");
    }
}
