#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 5550
#define SERVER_IP_ADDRESS "127.0.0.1" // TODO: replace the INADDR_ANY in line 24 with this define


int client_sock;

void client_connect(){
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

void server_stdout(char* output){
    int out_len = strlen(output) + 1; // == sizeof() because char is one byte
    int bytes = send(client_sock, output, out_len, 0);
    if (bytes == -1){
        perror("ERROR with send output to server\n");
        exit(1);
    }
    else if (bytes == 0){
	    perror("ERROR seems like the server closed the TCP connection\n");
    }
    else if (out_len > bytes){
	    printf("sent only %d bytes from the required %d\n", bytes, out_len);
    }
}


int main(){
    client_connect();
    server_stdout("blablabla");
}
