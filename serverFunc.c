//Cooper Tush
//Group A
//cooper.tush@okstate.edu
//March 2nd, 2022

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

/*
After the server connects to the client the server sends them this menu that ask if they want to play in single-player, multiplayer, or to just quit the game. Also saves all the player's information just in case.
*/

void func(int connf)
{
	int a;
	char buffer[MAX];	//Size of buffer
	char firstName[40];	//Size of First Name
	char lastName[40];	//Size of Last Name
	char country[40];	//Size of Country

    // infinite loop for chat
    for (;;) {
        bzero(buffer, MAX);
        
        //print buffer which contains the client contents
        bzero(buffer, MAX);
        a = 0;
        
        // copy server message in the buffer
        strcpy(buffer, "Welcome to main!" 
           "\n1. Single-Player Mode"
           "\n2. Multi-Player Mode"
           "\n3. Exit\n"
           "\nEnter: ");
   
        // and send that buffer to client
        write(connf, buffer, strlen(buffer)+1);
        // read the message from client and copy it in buffer
        read(connf, buffer, strlen(buffer)+1);

	//Starts Single-Player
        if(buffer[0] == '1'){
			strcpy(buffer, "Single-Player Mode\n"
			"Player info enter first name: ");
			
			//Takes First Name
			write(connf, buffer, sizeof(buffer));
			read(connf, buffer, strlen(buffer)+1);
			strcpy(firstName, buffer);
			
			//Take Last Name
			strcpy(buffer, "Enter last name: ");
			write(connf, buffer, sizeof(buffer));
			read(connf, buffer, strlen(buffer)+1);
			strcpy(lastName, buffer);
			
			//Takes Country
			strcpy(buffer, "Enter country: ");
			write(connf, buffer, sizeof(buffer));
			read(connf, buffer, strlen(buffer)+1);
			strcpy(country, buffer);
		
			firstName[strlen(firstName)-1] = '\0';
			lastName[strlen(lastName)-1] = '\0';
			country[strlen(country)-1] = '\0';
		
			printf("End of player info\n");
			
			//Starts Single-Player Mode
			playGame(connf, firstName, lastName, country);
        }
        //Multiplayer when client inputs 2
        else if (buffer[0] == '2'){
        	strcpy(buffer, "Multi-Player Mode");
        	write(connf, buffer, sizeof(buffer));
            //Goes into Multiplayer Mode
            //multiPlayerMode();
        }
        
        //Quits when client inputs 3
        else if (buffer[0] == '3'){
        	strcpy(buffer, "Server is now exiting...\n"
        			"Goodbye\n");
            	write(connf, buffer, strlen(buffer)+1);
            break;
        }
		
    }
}
