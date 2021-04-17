#include "mainMenu.h"

void mainMenuChoices()
{
	printf("Please type in the number label of the task you would like to do\n");
	printf("1 -> Blackjack\n");
	printf("2 -> Roulette\n");
	printf("3 -> Slots\n");
	printf("4 -> Current Balance\n");
	printf("5 -> Exit Game\n");
}

void toFile(int balance, int start)
{
	// save starting balance and ending balance to file
	FILE* fp;

	fp = fopen("GameHistory.txt", "a");		// creates file if it does not exist

	if (fp == NULL)
	{
		printf("Error opening file.\n\n");
		exit(EXIT_FAILURE);
	}

	fprintf(fp, "Starting Balance: $%d\n", start);
	fprintf(fp, "Ending Balance: $%d\n\n", balance);

	fclose(fp);
	return;
}