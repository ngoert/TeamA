#include <stdio.h>

int play(){
    char start;
    printf("Welcome to main!" 
           "\n1. Single-Player Mode"
           "\n2. Multi-Player Mode"
           "\n3. Exit\n"
           "\nEnter:\n");  // RESTART MAIN
        scanf(" %c", &start);
        if(start == '1') {
			//TODO
            //singlePlayerMode();
        }
        else if (start == '2') {
			//TODO
            //multiPlayerMode();
        }
        
        else {
            printf("\nGoodBye\n");
        }
    
}
