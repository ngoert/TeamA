#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "serverFunc.h"
#include "checkWord.h"
#include "scoreBoard.h"

#define INPUTOUTNAME "/mq_InputOut_queue"
#define DICTOUTNAME "/mq_DictionaryOut_queue"
#define INPUTINNAME "/mq_InputIn_queue"
#define DICTINNAME "/mq_DictionaryIn_queue"
#define SCOREINNAME "/mq_ScoreboardIn_queue"

#define PORT 4444

int main(){
	
	pid_t checkInput = fork();
	if (!checkInput) { // Check input process
		
		// Input struct
		
		typedef struct {
			char input[256];
			char word[256];
		} InputMessage;
		
		// Output struct
		
		typedef struct {
			int valid;
		} OutputMessage;
		
		// Input struct attributes
		
		struct mq_attr inAttr = {
			.mq_flags = 0,
			.mq_maxmsg = 3,
			.mq_curmsgs = 0,
			.mq_msgsize = sizeof(InputMessage)
		};
		
		// Output struct attributes
		
		struct mq_attr outAttr = {
			.mq_flags = 0,
			.mq_maxmsg = 3,
			.mq_curmsgs = 0,
			.mq_msgsize = sizeof(OutputMessage)
		};
		
		while(1){ // always checking
		
			// Receive input
		
			mqd_t inQueue = mq_open(INPUTINNAME, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR, &inAttr);
			InputMessage inputMsgStruct;
			mq_receive(inQueue, (char *)&inputMsgStruct, sizeof(inputMsgStruct), NULL);
			mqd_t outQueue = mq_open(INPUTOUTNAME, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR ,&outAttr);
			OutputMessage outputMsgStruct;
			
			// Check
			
			outputMsgStruct.valid = isInInput(inputMsgStruct.input, inputMsgStruct.word);

			// Send output
			
			mq_send(outQueue, (char *)&outputMsgStruct, sizeof(outputMsgStruct), 0);
		}
		
		exit(0);
	}
	pid_t checkDictionary = fork();
	if (!checkDictionary) { // Check dictionary process
		
		// Input Struct
		typedef struct {
			char input[256];
			char word[256];
		} InputMessage;
		
		// Output struct
		
		typedef struct {
			int valid;
		} OutputMessage;
		
		// Input attributes
		
		struct mq_attr inAttr = {
			.mq_flags = 0,
			.mq_maxmsg = 3,
			.mq_curmsgs = 0,
			.mq_msgsize = sizeof(InputMessage)
		};
		
		// Output attributes
		
		struct mq_attr outAttr = {
			.mq_flags = 0,
			.mq_maxmsg = 3,
			.mq_curmsgs = 0,
			.mq_msgsize = sizeof(OutputMessage)
		};
		
		while(1){ // Checks
		
		// Receives input
		
			mqd_t inQueue = mq_open(DICTINNAME, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR, &inAttr);
			InputMessage inputMsgStruct;
			mq_receive(inQueue, (char *)&inputMsgStruct, sizeof(inputMsgStruct), NULL);
			mqd_t outQueue = mq_open(DICTOUTNAME, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR ,&outAttr);
			OutputMessage outputMsgStruct;
		
		// Checks
		
			outputMsgStruct.valid = isInDictionary(inputMsgStruct.word, inputMsgStruct.input);

		// Sends output
		
			mq_send(outQueue, (char *)&outputMsgStruct, sizeof(outputMsgStruct), 0);
		}
		
		exit(0);
	}
	pid_t scoreboard = fork();
	if (!scoreboard) { //Scoreboard process
	
		// Scoreboard struct
		
		typedef struct {
			int isMultiPlayer;
			char first[256];
			char last[256];
			char country[256];
			int score;
			int words;
			int added;
			char result[256];
		} InputMessage;
		
		// Scoreboard attributes
		
		struct mq_attr inAttr = {
			.mq_flags = 0,
			.mq_maxmsg = 3,
			.mq_curmsgs = 0,
			.mq_msgsize = sizeof(InputMessage)
		};
		
		while(1){ // Loops
		
			// Gets input
		
			mqd_t inQueue = mq_open(SCOREINNAME, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR, &inAttr);
			InputMessage inputMsgStruct;
			mq_receive(inQueue, (char *)&inputMsgStruct, sizeof(inputMsgStruct), NULL);
		
			// Creates scoreboard if none is available
		
			createScoreBoard(inputMsgStruct.isMultiPlayer);
		
			// Insert score
		
			if (inputMsgStruct.isMultiPlayer) {
				insertMultiPlayer(inputMsgStruct.first,  inputMsgStruct.last,  inputMsgStruct.country,  inputMsgStruct.score,  inputMsgStruct.result,  inputMsgStruct.words,  inputMsgStruct.added);
			} else {
				insertSinglePlayer(inputMsgStruct.first,  inputMsgStruct.last,  inputMsgStruct.country,  inputMsgStruct.score,  inputMsgStruct.words,  inputMsgStruct.added);
			}
		}
	
		
		exit(0);
	}
	
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
	printf("Trying to bind to port \n");
	if(ret < 0){
		printf("Binding error...\n");
		exit(1);
	}
	
	if(listen(sockf, 10) == 0){
		printf("Listening...\n");
	}else{
		printf("Listen Error\n");
	}


	while(1){
		newSock = accept(sockf, (struct sockaddr*)&newAddr, &addr_size);
		if(newSock < 0){
			printf("Unsuccessful in accepting...\n");
			exit(1);
		}
		printf("Successfully accepted connection from... %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

		if((childpid = fork()) == 0){
			close(sockf);
			func(newSock);
			exit(0);
		}

	}

	close(newSock);


	return 0; 
	}
