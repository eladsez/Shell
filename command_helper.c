#include <stdlib.h>
#include <stdio.h>

#define ENTER_KEY 0x0A


/*
This function get a command from sdtin in a dynamic way and retrive it to the main program (the main free it all)
*/
char* input_command() {
    size_t size_lim = 2; // the initial limit size   
    char* command = malloc(sizeof(char) * size_lim);
    if (command == NULL){
        perror("malloc ERROR");
        exit(1);
    }
    char c = getchar();
    size_t com_len = 0; // the actual command size
    while (c != ENTER_KEY){
        command[com_len++] = c;

        if(com_len == size_lim){ // if the actual size meet the limitaion increase the allocate *2 
            command = realloc(command, sizeof(char) * (size_lim *= 2));
            if (command == NULL){
                perror("realloc ERROR");
                exit(1);
            }
        }

        c = getchar();
    }
    command[com_len++]='\0';

    command = realloc(command, sizeof(char) * com_len);
    
    if (command == NULL){
        perror("realloc ERROR");
        exit(1);
    }

    return command;
}