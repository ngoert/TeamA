#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "Scoreboard.h"
#include "playGame.h"
#define MAX 1028
#define PORT 8081
#define SA struct sockaddr
   
   char firstName[40];
   char lastName[40];
   char country[40];
   char playerInfo[120];
   
// Function designed for chat between client and server.
void func(int connf)
{
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
        write(connf, buffer, sizeof(buffer));
        read(connf, buffer, sizeof(buffer));
        
        if(buffer[0] == '1'){
		strcpy(buffer, "Single-Player Mode\n"
		"Player info enter first name: \n");
		write(connf, buffer, sizeof(buffer));
		
		 read(connf, buffer, sizeof(buffer));
		 strcpy(firstName, buffer);
		 strcat(playerInfo, "First Name: ");
		 strcat(playerInfo, firstName);
		 strcpy(buffer, "Enter last name: \n");
		 write(connf, buffer, sizeof(buffer));
		 
		 read(connf, buffer, sizeof(buffer));
		 strcpy(lastName, buffer);
		 strcat(playerInfo, "Last Name: ");
		 strcat(playerInfo, lastName);
		 strcpy(buffer, "Enter country: \n");
		 write(connf, buffer, sizeof(buffer));
		 
		 read(connf, buffer, sizeof(buffer));
		 strcpy(country, buffer);
		 strcat(playerInfo, "Country: ");
		 strcat(playerInfo, country);
		 
		strcat(playerInfo, "\n");
		strcpy(buffer, playerInfo);
		
		playGame(connf);
		
        }
        else if (buffer[0] == '2'){
        	strcpy(buffer, "Multi-Player Mode");
        	write(connf, buffer, sizeof(buffer));
            //multiPlayerMode();
        }
        
        else {
        	strcpy(buffer, "Server is now exiting...\n"
        			"Goodbye\n");
            	write(connf, buffer, sizeof(buffer));
            break;
        }
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
    int sockf, connf, len;
    struct sockaddr_in servaddr, cli;
	
	// TEMPORARY FUCNTION CALLS FOR TESTING AND SHOWCASE
	// START OF TEMPORARY FUNCTION CALLS
	createScoreBoard(0);
    createScoreBoard(1);
    insertSinglePlayer("John", "Doe", "Russia", 10, 1, 2);
    insertMultiPlayer("Billy", "Stan", "Vietnam", 12, "Win", 5, 11);
    insertSinglePlayer("Jack", "Ball", "USA", 12, 4, 5);
    insertSinglePlayer("Jill", "Lilly", "Egypt", 8, 2, 3);
    insertMultiPlayer("Nicky", "Matt", "USA", 14, "Lose", 11, 21);
    insertSinglePlayer("Diane", "Peter", "China", 11, 10, 12);
    insertMultiPlayer("Alex", "Brax", "Russia", 15, "Win", 12, 12);
    insertMultiPlayer("Ron", "Moore", "Egypt", 13, "Lose", 16, 15);
    insertSinglePlayer("Kyle", "Ricky", "Japan", 9, 14, 17);
    insertMultiPlayer("Cass", "Sam", "Mexico", 10, "Lose", 21, 51);
    insertSinglePlayer("Rick", "Joe", "Canada", 1, 21, 31);
    insertMultiPlayer("Randy", "Sally", "China", 1, "Win", 18, 16);
    insertSinglePlayer("Bob", "Marley", "Mexico", 13, 41, 51);
    insertMultiPlayer("Hanzo", "Carol", "Japan", 111, "Lose", 91, 71);
	//play();
    // END OF TEMPORARY FUNCTION CALLS
	
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
    //Put getPlayerInfo() into play()
   
    // After chatting close the socket
    close(sockf);
}

