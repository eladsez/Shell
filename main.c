#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shell.h"

#define TRUE 1
#define FALSE 0



int main(){
    char* command; // represent the current command input by input_command function
    while (TRUE){

        print_prompt();
        command = input_command(command);

        if (!strcmp(exitC, command)){ // strcmp return a non-zero integer if the strings dont match and zero if they do
            free(command);
            exit(0);
        }

        else if (str_cmp(echoC, 4, command, 4)){
            for (size_t i = 5; i < strlen(command); ++i)
                printf("%c", command[i]);
            printf("\n");
        }

        else if (str_cmp(dirC, 3, command, 3)){
            print_dir(".", NULL);
            printf("\n");
        }

        else if (str_cmp(cdC, 2, command, 2)){
            if (chdir((command + 3)) != 0){
                perror("chdir ERROR");
                exit(1);
            }
        }

        else if (str_cmp(deleteC, 6, command, 6)){
            if (unlink((command + 7)) != 0){
                perror("unlink ERROR");
                exit(1);
            }
        }

        else if (str_cmp(tcpC, 8, command, 8)){
            // TODO
        }

        else
            system(command);

        if (command != NULL)
            free(command);

    }
}

