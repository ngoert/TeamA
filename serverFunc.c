#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "playGame.h"
#define MAX 1024
#define PORT 8081
#define SA struct sockaddr

void func(int connf)
{
	char firstName[40];
	char lastName[40];
	char country[40];
	char playerInfo[120];
    char buffer[MAX];
    int a;
    // infinite loop for chat
    for (;;) {
        bzero(buffer, MAX);
   
        // read the message from client and copy it in buffer
        // read(connf, buffer, sizeof(buffer));
        //print buffer which contains the client contents
        //printf("Message from client: %s\t Message to client : ", buffer);
        bzero(buffer, MAX);
        a = 0;
        // copy server message in the buffer
        // while ((buffer[a++] = getchar()) != '\n');
        strcpy(buffer, "Welcome to main!" 
           "\n1. Single-Player Mode"
           "\n2. Multi-Player Mode"
           "\n3. Exit\n"
           "\nEnter: ");
   
        // and send that buffer to client
        write(connf, buffer, strlen(buffer)+1);
        read(connf, buffer, strlen(buffer)+1);

		
        if(buffer[0] == '1'){
			strcpy(buffer, "Single-Player Mode\n"
			"Player info enter first name: ");
			write(connf, buffer, sizeof(buffer));
			read(connf, buffer, strlen(buffer)+1);
			strcpy(firstName, buffer);
			//strcat(playerInfo, "First Name: ");
			//strcat(playerInfo, firstName);
			strcpy(buffer, "Enter last name: ");
			write(connf, buffer, sizeof(buffer));
			read(connf, buffer, strlen(buffer)+1);
			strcpy(lastName, buffer);
			//strcat(playerInfo, "Last Name: ");
			//strcat(playerInfo, lastName);
			strcpy(buffer, "Enter country: ");
			write(connf, buffer, sizeof(buffer));
			read(connf, buffer, strlen(buffer)+1);
			strcpy(country, buffer);
			//strcat(playerInfo, "Country: ");
			//strcat(playerInfo, country);
		 
			//strcat(playerInfo, "\n");
			//strcpy(buffer, playerInfo);
		
			firstName[strlen(firstName)-1] = '\0';
			lastName[strlen(lastName)-1] = '\0';
			country[strlen(country)-1] = '\0';
		
			printf("End of player info\n");
		
			playGame(connf, firstName, lastName, country);
        }
        else if (buffer[0] == '2'){
        	strcpy(buffer, "Multi-Player Mode");
        	write(connf, buffer, sizeof(buffer));
            //multiPlayerMode();
        }
        
        else if (buffer[0] == '3'){
        	strcpy(buffer, "Server is now exiting...\n"
        			"Goodbye\n");
            	write(connf, buffer, strlen(buffer)+1);
            break;
        }
		
    }
}