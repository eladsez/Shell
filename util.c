#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0


void print_prompt(){
    char cwd[PATH_MAX]; // PATH_MAX taken from limits.h 
   if (getcwd(cwd, sizeof(cwd)) != NULL){
       printf("\033[1;35m");
       printf("user@myshell");
       printf("\033[1;36m");
       printf(":~%s$ ", cwd);
       printf("\033[0;37m");
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
