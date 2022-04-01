/**
 * This file implement a basic tcp server
 */
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h> 

#define SERVER_PORT 3490
#define SERVER_IP_ADDRESS "127.0.0.1" // TODO: replace the INADDR_ANY in line 24 with this define
#define TRUE 1


int main(){
    int server_sock = socket(AF_INET , SOCK_STREAM , 0);
    if (server_sock == -1){
        printf("%d ERROR to create server socket\n", errno);
        return 1;
    }

    // // Reuse the address if the server socket on was closed
	// // and remains for 45 seconds in TIME-WAIT state till the final removal.
    int enableReuse = 1;
    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &enableReuse, sizeof(int)) < 0){
         printf("%d ERROR setsockopt failed\n", errno);
         close(server_sock);
         return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);

    if (bind(server_sock, (struct sockaddr *)&server_addr , sizeof(server_addr)) == -1){
        printf("%d ERROR Bind failed\n", errno);
        close(server_sock);
        return 1;
    }

    if (listen(server_sock, 1) == -1){
	    printf("%d ERROR listen failed\n", errno);
        close(server_sock);
        return -1;
    }

    printf("waiting for a client to connect...\n");

    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    socklen_t client_addr_len = sizeof(client_addr);
    int client_sock = -1;

    while(TRUE){/// handle client connection
        if ((client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len)) == -1){
            printf("%d ERROR accept client failed\n", errno);
            close(server_sock);
            return 1;
        }
        if (fork() == 0) // the child procces will handle the client in the second while(TRUE) loop
            break;
    }

    printf("client connect!\n");

    while(TRUE){/// handle client
        char buff[5120] = {0};
        int bytes = recv(client_sock, buff, sizeof(buff), 0);
        if (bytes < 0){
            printf("%d ERROR client recv", errno);
            close(client_sock);
            close(server_sock);
            return 1;
        }
         else if (bytes == 0){
            printf("seems like the one of the clients has disconnect\n");
            close(client_sock);
            return 0;
        }
        else{
            printf("%s\n", buff);
        }
    }
}