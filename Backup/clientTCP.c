#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444

int main(){

	int clientSock, ret;
	struct sockaddr_in serverAddr;
	char buff[1024];

	clientSock = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSock < 0){
		printf("Connection error...\n");
		exit(1);
	}
	printf("Succesfully created Client Socket!\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("Connection error...\n");
		exit(1);
	}
	printf("Succesfully connected to Server!\n");

	while(1){
		//printf("Client says: \t");
		if(recv(clientSock, buff, 1024, 0) < 0){
			printf("Could not receive data due to error\n");
		}else{
			printf("%s\n", buff);
		}
		fgets(&buff[0], sizeof(buff), stdin);
		send(clientSock, buff, strlen(buff)+1, 0);

		if(strcmp(buff, "3\n") == 0){
			close(clientSock);
			printf("Successfully disconnected from server!\n");
			exit(1);
		}

	}

	return 0;
}
