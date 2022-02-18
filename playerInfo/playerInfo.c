int getPlayerInfo() {
    struct getPlayers {
char firstName[40];
char lastName[40];
char country[40];
}player[100];

    int numOfPlayers;
    printf("Enter # of players: ");
    scanf("%d", &numOfPlayers);
    printf("Enter player info as firstName, lastName, and country:\n");
    for(int i = 0; i < numOfPlayers; i++)
    {
        scanf("%s %s %s",player[i].firstName,player[i].lastName,player[i].country);
    }
    printf("\nfirstName:\tlastName:\tcountry:\n");
    for(int i = 0; i < numOfPlayers; i++)
    {
        printf("%s\t\t%s\t\t%s\n",player[i].firstName,player[i].lastName,player[i].country);
    }
}
