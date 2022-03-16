#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"

#define TRUE 1
#define FALSE 0



int main(){
    char* command; // represent the current command input by input_command function
    while (TRUE){
        print_prompt();
        command = input_command(command);
        if (strcmp(exitC, command) == FALSE){ // strcmp return a non-zero integer if the strings dont match and zero if they do
            free(command);
            exit(0);
        }

        if (str_cmp(echoC, 4, command, 4) == TRUE){
            for (size_t i = 5; i < strlen(command); ++i)
                printf("%c", command[i]);
        }


        if (command != NULL)
            free(command);

    }
}

