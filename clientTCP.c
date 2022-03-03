/* Author: Virginia Crews
   Group A
   email: virginia.crews@okstate.edu
   3/2/2022


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444 //port that connects the client and server

int main(){

	int clientSock, ret; //variables for client socket
	struct sockaddr_in serverAddr; 
	char buff[1024];

	clientSock = socket(AF_INET, SOCK_STREAM, 0); //defining the socket and its parameters
	if(clientSock < 0){ //condition for when client socket failed connection
		printf("Connection error...\n");
		exit(1);
	} //else the user will receive a message that the client socket has been created
	printf("Succesfully created Client Socket!\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //local address since this is being done on local machine

	ret = connect(clientSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)); //creates connect command, pointer to server address
	if(ret < 0){
		printf("Connection error...\n"); //if ret val = 0 then connection is empty, it fails
		exit(1);
	} 
	printf("Succesfully connected to Server!\n"); //else connection is successful to server from client

	while(1){
		//printf("Client says: \t"); ----Can uncomment to prove communication works
		if(recv(clientSock, buff, 1024, 0) < 0){
			printf("Could not receive data due to error\n"); //if communication fails between server and client
		}else{
			printf("%s\n", buff);
		}
		fgets(&buff[0], sizeof(buff), stdin);
		send(clientSock, buff, strlen(buff)+1, 0);

		if(strcmp(buff, "3\n") == 0){ //checks whether the user wants to exit
			close(clientSock);
			printf("Successfully disconnected from server!\n");
			exit(1);
		}

	}

	return 0;
}
