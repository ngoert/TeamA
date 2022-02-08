#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

//Function designed for chatting between client and server
//Rename to chatting or connection or TCP
void func(int connfd){
	int n;
	char buff[MAX];
	
	//infinite loop for chat.
	for (;;) {
		bzero(buff, MAX);
		
		//read the message from client and copy it in buffer.
		read(connfd, buff, sizeof(buff));
		//print buffer which contains the client contents
		printf("From client: %s|t To client : ", buff);
		bzero(buff, MAX);
		n = 0;
		//Copy server message in the buffer
		while ((buff[n++] = getchar()) != '\n');
		
		//Sends that buffer to client
		write(connfd, buff, sizeof(buff));
		
		//If msg contains "Exit" then server exit and chat ended.
		if (strncmp("exit", buff, 4) == 0){
			printf("Server Exit\n");
			break;
		}
	}
}

//Driver function? First we must verify every thing and all the steps to establish the TCP
void main(){
	int sockfd, confd, len;
	struct sockaddr_in servaddr, cli;
	//Socket create and verification, opens it to allow a TCP server or digital connection.
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd == -1){
		print("Socket creation failed\n");
		exit(0);
	} else {
		printf("Socket successfully created\n");
		bzero(&servaddr, sizeof(servaddr));
	}
	
	//Assigns an IP and PORT, what does this mean?
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	
	//Binding newly created socket to given IP and verification
	if((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0){
		printf("Socket bind failed\n");
		exit(0);
	} else {
		printf("Socket successfully binded\n");
	}
	
	//Now server is ready to listen and verification
	if((listen(sockfd, 5)) != 0){
		printf("Listen failed\n");
		exit(0);
	} else {
		printf("Server listening\n");
	}
	
	len = sizeof(cli);
	
	//Accept the data packet from client and verify. Communicates with the client with the data packets.
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0){
		printf("Server accept failed\n");
		exit(0);
	} else {
		printf("Server accept the client\n");
	}
	
	//Function for chatting between client and server
	func(connfd);
	
	//After chatting close the socket. Why?
	close(sockfd);
	
}
