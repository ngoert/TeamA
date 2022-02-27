#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
/*
#include "Scoreboard.h"
#include "play.h"
#include "playerInfo.h"
*/
#include "checkWord.h"
#define MAX 80
#define PORT 8081
#define SA struct sockaddr
   
// Function designed for chat between client and server.
void func(int connf)
{
    char buffer[MAX];
    int a;
    // infinite loop for chat
    for (;;) {
        bzero(buffer, MAX);
   
        // read the message from client and copy it in buffer
        read(connf, buffer, sizeof(buffer));
        // print buffer which contains the client contents
        printf("Message from client: %s\t Message to client : ", buffer);
        bzero(buffer, MAX);
        a = 0;
        // copy server message in the buffer
        while ((buffer[a++] = getchar()) != '\n')
            ;
   
        // and send that buffer to client
        write(connf, buffer, sizeof(buffer));
   
        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buffer, 4) == 0) {
            printf("Server is now exiting...\n");
            break;
        }
    }
}
   
// Driver function
int main()
{
	char * temp = malloc(256);
    char input[256] = "input_01.txt";
    char* scramble = getScramble(input);
	printf("%s\n", input);
	printf("Letters: %s\n", scramble);
	scanf("%s", temp);
    printf("%d\n", isValid(temp, input));
    
    int sockf, connf, len;
    struct sockaddr_in servaddr, cli;
	
    // socket create and verification
    sockf = socket(AF_INET, SOCK_STREAM, 0);
    if (sockf == -1) {
        printf("Failed to create socket...\n");
        exit(0);
    }
    else
        printf("Successfully created Socket!\n");
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    // Binding newly created socket to given IP and verification
    if ((bind(sockf, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket failed to bind...\n");
        exit(0);
    }
    else
        printf("Successfully binded socket..\n");
   
    // Now server is ready to listen and verification
    if ((listen(sockf, 5)) != 0) {
        printf("Failed to listen...\n");
        exit(0);
    }
    else
        printf("Server successfully listening!\n");
    len = sizeof(cli);
   
    // Accept the data packet from client and verification
    connf = accept(sockf, (SA*)&cli, &len);
    if (connf < 0) {
        printf("Failed to accept server...\n");
        exit(0);
    }
    else
        printf("Succesfully accepted the client!\n");
   
    // Function for chatting between client and server
    func(connf);
   
    // After chatting close the socket
    close(sockf);
}

