#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shell.h"


int main(){
    char* command; // represent the current command input by input_command function
    in_server = FALSE;
    client_sock = 0;
    while (TRUE){

        print_prompt();
        command = input_command();

        if (!strcmp("EXIT", command)){ // strcmp return a non-zero integer if the strings dont match and zero if they do
            free(command);
            exit(0);
        }

        else if (str_cmp("ECHO", 4, command, 4)){
            for (size_t i = 5; i < strlen(command); ++i)
                printf("%c", command[i]);
            printf("\n");
        }

        else if (str_cmp("DIR", 3, command, 3)){
            print_dir(".", NULL);
            printf("\n");
        }

        else if (str_cmp("CD", 2, command, 2)){
            if (chdir((command + 3)) != 0){
                perror("chdir ERROR");
                exit(1);
            }
        }

        else if (str_cmp("DELETE", 6, command, 6)){
            if (unlink((command + 7)) != 0){
                perror("unlink ERROR");
                exit(1);
            }
        }

        else if (!strcmp("TCP PORT", command)){
            in_server = TRUE;
            tcp_client();
            dup2(STDOUT_FD, TEMP_STDOUT_FD);
            dup2(client_sock, STDOUT_FD);
        }

        else if (str_cmp("LOCAL", 4, command, 4)){
            in_server = FALSE;
            close_tcp_client();
            dup2(TEMP_STDOUT_FD, STDOUT_FD);
        }

        else if (str_cmp("COPY", 4, command, 4)){
            size_t space = find_space(command + 5) + 5;
            if (space == -1) continue; // in case there is no two paths
            command[space] = '\0';
            copy_file(command + 5, command + space + 1);
        }

        else{
//            system(command);
            pipe_control(command);
        }

        if (command != NULL)
            free(command);

    }
}

