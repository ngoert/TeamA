#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

//Enter a integer for Timer() for the number of seconds to countdown from.
int Timer(int counter){
	while(counter != 0){
		counter--;
		sleep(1);
	}	
}

int main(){
	Timer(10);
}
