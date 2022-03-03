#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NAME "/mq_idk_queue"
typedef struct {
	char msg[1024];
} Message;

int main(){
	struct mq_attr attr = {
		.mq_flags = 0,
		.mq_maxmsg = 10,
		.mq_curmsgs = 0,
		.mq_msgsize = sizeof(Message)
	};
	
	mqd_t queue = mq_open(NAME, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR, &attr);
	
	Message msgStruct;
	mq_receive(queue, (char *)&msgStruct, sizeof(msgStruct), NULL);
	printf("%s\n", msgStruct.msg);
	getchar();
	
}