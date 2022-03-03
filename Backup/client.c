#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAX 1028
#define PORT 8081
#define SA struct sockaddr

void func(int sockf)
{
    char buffer[MAX];
    int a;
	
	bzero(buffer, sizeof(buffer));
    read(sockf, buffer, sizeof(buffer));
	printf("%s", buffer);
    for (;;) {
		
        bzero(buffer, sizeof(buffer));
        a = 0;
        while ((buffer[a++] = getchar()) != '\n')
            ;
        write(sockf, buffer, sizeof(buffer));
		bzero(buffer, sizeof(buffer));
        read(sockf, buffer, sizeof(buffer));
		printf("%s", buffer);
    }
}
   
int main()
{
    int sockf, connfd;
    struct sockaddr_in servaddr, cli;
   
    // socket create and verification
    sockf = socket(AF_INET, SOCK_STREAM, 0);
    if (sockf == -1) {
        printf("Failed to connect to socket...\n");
        exit(0);
    }
    else
        printf("Successfully created socket..\n");
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
   
    // connect the client socket to server socket
    if (connect(sockf, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Failed to connect with server...\n");
        exit(0);
    }
    else
        printf("Successfully connected to server!\n");
   
    // function for chat with server
    func(sockf);
   
    // function to close the socket
    close(sockf);
}
	
