#include "mainMenu.h"
#include "slots.h"
#include "roulette.h"

int main(int argc, char* argv[]) {
	int balanceStr, balance, choice = 0;
	balance = balanceStr = atoi(argv[1]);

	printf("Welcome to the Casino!\n");
	printf("Your balance is: $%d\n", balance);
	printf("We offer Blackjack, Roulette, and Slots\n\n");


	while (choice != 5)
	{
		mainMenuChoices();

		if (balance > 0)
		{
			if (scanf("%d", &choice) != 1)
			{
				printf("Error getting input.\n\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			printf("You've gone bankrupt.\n");
			choice = 5;
		}

		switch (choice)
		{
		case 1:
			balance = blackjack(balance);
			break;
		case 2:
			balance = roulette(balance);
			break;
		case 3:
			balance = slots(balance);
			break;
		case 4:
			printf("\nCurrent Balance: $%d\n\n", balance);
			break;
		case 5:
			printf("\nYour final balance is $%d\n", balance);
			printf("Thank you for playing!\n\n");

			toFile(balance, balanceStr);
			exit(EXIT_SUCCESS);
			break;
		default:
			printf("Invalid input. Please try again.\n\n");
		}
	}
	return 0;
}
