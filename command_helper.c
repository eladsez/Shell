#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h> 

#include "shell.h"

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

    command = realloc(command, sizeof(char) * com_len); // shrink the command to his original size
    
    if (command == NULL){
        perror("realloc ERROR");
        exit(1);
    }

    return command;
}


void print_dir(char* dir_path, int* options){
    DIR *folder = opendir(dir_path); //pointer that acts as the directory handler through function
    if(folder == NULL){
        perror("opendir ERROR");
        exit(1);
    }
    struct dirent *entry; // struct that contains information about a specific entry read from a directory 
    while( (entry=readdir(folder)) ) // while entry is not null print the entry name
        printf("%s  ", entry->d_name);
    
    closedir(folder);
}


void copy_file(char* from, char* to){
    FILE *origin= fopen(from, "r");
    FILE *copy = fopen(to, "w");

    if (origin == NULL || copy == NULL){
        perror("ERROR open files");
        exit(1);
    }

    while(!feof(origin))
        fputc(fgetc(origin), copy);
    
    fclose(origin);
    fclose(copy);
}

void tcp_client(){
    // if (client_sock != -1) return;
    if((client_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("%d ERROR create socket\n", errno);
        exit(1);
    }
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY; // the address assigned is 0.0.0.0

    if (connect(client_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
	   printf("%d ERROR to connect the server\n", errno);
       exit(1);
    }
}

void close_tcp_client(){
    if (client_sock != -1){
        close(client_sock);
        client_sock = -1;
    }
}


void exec(char* command){
    unsigned int buff_size = count_space(command);
    char *splited_exec[buff_size + 2];
    parse_spaces(command, splited_exec);
    for (int i = 0; i < buff_size + 2; ++i){
        printf("%s\n", splited_exec[i]);
    }

}