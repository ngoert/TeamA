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

	int sockf, ret;
	 struct sockaddr_in serverAddr;

	int newSock;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	char buff[1024];
	pid_t childpid;

	sockf = socket(AF_INET, SOCK_STREAM, 0);
	if(sockf < 0){
		printf("Connection error...\n");
		exit(1);
	}
	printf("Successfully created Server Socket!\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockf, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("Binding error...\n");
		exit(1);
	}
	printf("Trying to bind to port \n");

	if(listen(sockf, 10) == 0){
		printf("Listening...\n");
	}else{
		printf("Unsuccessful in binding...\n");
	}


	while(1){
		newSock = accept(sockf, (struct sockaddr*)&newAddr, &addr_size);
		if(newSock < 0){
			exit(1);
		}
		printf("Successfully accepted connection from... %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

		if((childpid = fork()) == 0){
			close(sockf);

			while(1){
				int size = recv(newSock, buff, 1024, 0);
				buff[size] = '\0';
				if(strcmp(buff, ":exit") == 0){
					printf("Successfully Disconnected from... %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
					break;
				}else{
					//printf("Client: %s\n", buff);
					//send(newSock, buff, strlen(buff), 0);
					//bzero(buff, sizeof(buff));
				}
			}
		}

	}

	close(newSock);


	return 0; 
	}
