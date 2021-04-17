#include "rouletteMenus.h"
#include "roulette.h"


void rouletteMenu()		// menu choices
{
	printf("\n1 -> Play Roulette\n");
	printf("2 -> Add Bet\n");
	printf("3 -> Remove Bet\n");
	printf("4 -> View Current Bets\n");
	printf("5 -> View Payout Table\n");
	printf("6 -> Save and Exit\n\n");
}

void welcomeMenu()
{
	printf("\nWelcome to Roulette!\n");
	printf("Please enter the number label of the task you would like to do.\n");
	printf("Note: There is a maximum of %d bets you can make each round.\n", MAXBETS);
	printf("Minimum $%d per bet!\n", MINPRICE);
}

void payoutTable()		// displays the payout if you win
{
	printf("\nINSIDE\n");
	printf("Single number 35:1\n\n");
	printf("OUTSIDE\n");
	printf("Red 1:1\nBlack 1:1\nEven 1:1\nOdd 1:1\nFirst dozen (1-12) 2:1\nSecond dozen (13-24) 2:1\nThird dozen (25-36) 2:1\nFirst half (1-18) 1:1\nSecond half (19-36) 1:1\n");
}

void addBetMenu()
{
	printf("\n1 -> Add a bet\n");
	printf("2 -> View current bets\n");
	printf("3 -> View unsaved bets\n");
	printf("4 -> Cancel adding bets\n");
	printf("5 -> Save bets and return to menu\n");
}

void createBetMenu()
{
	printf("\nWhat type of bet do you want?\n");
	printf("1 -> Single\n");
	printf("2 -> Colour\n");
	printf("3 -> Even or Odd\n");
	printf("4 -> Range\n");
	printf("5 -> Cancel adding\n");
}

void colourBetMenu()
{
	printf("\nWhat colour do you want to bet on?\n");
	printf("1 -> Red\n");
	printf("2 -> Black\n");
	printf("3 -> Cancel\n");
}

void evenOddMenu()
{
	printf("\nWhat do you want to bet on?\n");
	printf("1 -> Even\n");
	printf("2 -> Odd\n");
	printf("3 -> Cancel bet\n");
}

void rangeBetMenu()
{
	printf("\nWhat range of numbers do you want to bet on?\n");
	printf("1 -> First dozen (1 - 12)\n");
	printf("2 -> Second dozen (13 - 24)\n");
	printf("3 -> Third dozen (25 - 36)\n");
	printf("4 -> First half (1 - 18)\n");
	printf("5 -> Second half (19 - 36)\n");
	printf("6 -> Cancel bet\n");
}