The server/client works by first compiling and running the server file.
The user should use the command gcc server.c and press enter.
Then enter ./a.out and these two commands should allow the server to begin to search for connection to the port.
The server then is waiting on port 8081 for a client to connect.
So then the user should compile the client file using the same commands specified early with the exception of changing server.c to client.c.
Then it will search the ports and connect to port 8081. Once the sockets are binded, and the connection is successful the client is prompted to enter text that will be sent to the server.
This particular function is just to demonstrate that the server/client connection works. The server should then receive this text and be prompted to enter text that will be sent to the client.

Main Menu and Player information: 
The main-menu program contains input from the user and displaying a list of options, the user indicates their choice.
The input is a single keystroke. The player information is a struct which allows the use of char and int to be together.
These data types are represented by ‘player’. The use of two for loops to print out a table with firstName, lastName, and country.

createScoreBoard function works by attempting to read the corresponding score file,
and if it’s not there, it opens it in write mode to create it and puts in the headers.
2 appendScoreBoard functions take in the information in the parameters,
then opens the file in append mode and writes the information formatted correctly.
The insertScoreBoard function opens the corresponding scoreboard file, then saves the headers,
then reads each player until it has read all the players.
It then loops through the players to see if the player to be inserted has a higher score.
It also checks to see if the scoreboard has 5 players recorded.
If the player has a higher score and there are less than 5 players,
all the players get shifted down and the player is inserted. If there are already 5 players, then the last player gets removed.
If the player to be inserted isn’t higher than any of the scores and there are less than 5 players, they get appended to the end of the scoreboard.
If there are already 5 players, then the player to be inserted doesn’t get inserted.

When you input an integer into Timer(),
it will countdown from that number and represent them as seconds within the function until it ends when the number reaches zero.


compile server:
gcc -o server scoreBoard.c playGame.c substring.c checkWord.c serverTCP.c serverFunc.

Compile Client:
gcc -o client clientTCP.c

Run server frist:
./server

Run Clients second:
./client