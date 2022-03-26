#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<sys/wait.h>
#include <errno.h>

#include "shell.h"

/*
This function get a command from sdtin in a dynamic way and retrieve it to the main program (the main free it all)
*/
char *input_command() {
    size_t size_lim = 2; // the initial limit size   
    char *command = malloc(sizeof(char) * size_lim);
    if (command == NULL) {
        perror("malloc ERROR");
        exit(1);
    }
    char c = (char) getchar();
    size_t com_len = 0; // the actual command size
    while (c != ENTER_KEY) {
        command[com_len++] = c;

        if (com_len == size_lim) { // if the actual size meet the limitation increase by allocate *2
            command = realloc(command, sizeof(char) * (size_lim *= 2));
            if (command == NULL) {
                perror("realloc ERROR");
                exit(1);
            }
        }

        c = (char) getchar();
    }
    command[com_len++] = '\0';

    command = realloc(command, sizeof(char) * com_len); // shrink the command to his original size

    if (command == NULL) {
        perror("realloc ERROR");
        exit(1);
    }

    return command;
}


void print_dir(char *dir_path, int *options) {
    DIR *folder = opendir(dir_path); //pointer that acts as the directory handler through function
    if (folder == NULL) {
        perror("opendir ERROR");
        exit(1);
    }
    struct dirent *entry; // struct that contains information about a specific entry read from a directory 
    while ((entry = readdir(folder))) // while entry is not null print the entry name
        printf("%s  ", entry->d_name);

    closedir(folder);
}


void copy_file(char *from, char *to) {
    FILE *origin = fopen(from, "r");
    FILE *copy = fopen(to, "w");

    if (origin == NULL || copy == NULL) {
        perror("ERROR open files");
        exit(1);
    }

    while (!feof(origin))
        fputc(fgetc(origin), copy);

    fclose(origin);
    fclose(copy);
}

void tcp_client() {
    if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("%d ERROR create socket\n", errno);
        exit(1);
    }
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY; // the address assigned is 0.0.0.0

    if (connect(client_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        printf("%d ERROR to connect the server\n", errno);
        exit(1);
    }
}

void close_tcp_client() {
    if (client_sock != -1) {
        close(client_sock);
        client_sock = -1;
    }
}


void exec_no_pipe(char *command) {
    unsigned int buff_size = count_chars(command, ' ') + 2;
    char *splited_exec[buff_size];
    parse_str(command, splited_exec, " ");
    splited_exec[buff_size - 1] = NULL;
    int pid = fork();
    if (pid < 0) {
        printf("%d ERROR with exec fork", errno);
        exit(1);
    } else if (pid == 0)
        execvp(splited_exec[0], splited_exec);
    else {
        wait(NULL);
    }

}


void pipe_exec(char *command) {
    unsigned int buff_size = count_chars(command, ' ') + 2;
    char *splited_exec[buff_size];
    parse_str(command, splited_exec, " ");
    splited_exec[buff_size - 1] = NULL;
    execvp(splited_exec[0], splited_exec);
}


int rec_pipe(char *commands[], int size) {
    if (size == 0) {
        int pipe1[2];

        if (pipe(pipe1) == -1) {
            printf("%d ERROR with pipe creation", errno);
        }
        int pid = fork();
        if (pid < 0) {
            printf("%d ERROR with exec fork", errno);
            exit(1);

        } else if (pid == 0) {
            // input from stdin (already done)
            // output to pipe1
            dup2(pipe1[1], 1);
            close(pipe1[0]);
            close(pipe1[1]);
            pipe_exec(commands[0]);
        } else {
            wait(NULL);
            close(pipe1[1]);
            return pipe1[0];
        }
    } else {
        int pipe1 = rec_pipe(commands, size - 1);
        int pipe2[2];
        if (pipe(pipe2) == -1) {
            printf("%d ERROR with pipe creation", errno);
        }
        int pid = fork();
        if (pid < 0) {
            printf("%d ERROR with exec fork", errno);
            exit(1);
        } else if (pid == 0) {
            // input from pipe1
            dup2(pipe1, 0);
            // output to pipe2
            dup2(pipe2[1], 1);
            // close fds
            close(pipe1);
            close(pipe2[0]);
            close(pipe2[1]);
            pipe_exec(commands[size]);
        } else {
            wait(NULL);
            close(pipe1);
            close(pipe2[1]);
            return pipe2[0];
        }
    }
    return -1;
}


void pipe_control(char *command) {
    int comm_size = count_chars(command, '|') + 1;

    if (comm_size - 1 == 0) {
        exec_no_pipe(command);
        return;
    }
    char *commands[comm_size];
    parse_str(command, commands, "|");
    int pipe = rec_pipe(commands, comm_size - 2);
    int pid = fork();
    if (pid < 0) {
        printf("%d ERROR with exec fork", errno);
        exit(1);
    } else if (pid == 0) {
        // input from pipe2
        dup2(pipe, 0);
        // output to stdout (already done)
        // close fds
        close(pipe);
        pipe_exec(commands[comm_size - 1]);
    } else {
        wait(NULL);
        close(pipe);
    }
}