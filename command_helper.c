#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

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