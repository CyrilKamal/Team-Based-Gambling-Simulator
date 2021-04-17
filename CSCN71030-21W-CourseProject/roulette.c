#include "roulette.h"
#include "rouletteMenus.h"

int roulette(int balance)		// main game body
{
	int choice = 0, cont = 0;
	bool game = true;
	BET* bets = (BET*)calloc(MAXBETS, sizeof(BET));

	if (bets == NULL)
	{
		printf("Error. Memory not allocated. Exiting program...\n");
		exit(EXIT_FAILURE);
	}

	welcomeMenu();
	
	while(game)
	{
		rouletteMenu();
		if (scanf("%d", &choice) != 1)
		{
			printf("Error getting input.\n\n");
			continue;
		}

		switch (choice)
		{
		case 1:
			if (bets[0].amount != 0)
			{
				balance = playRoulette(bets, balance);	// starts the game
				free(bets);
				bets = (BET*)calloc(MAXBETS, sizeof(BET));

				printf("\nNew round\n");
			}
			else
				printf("You have made no bets! Please add at least one before playing.\n");
			break;
		case 2:
			balance = addBet(bets, balance);	// adds bets
			break;
		case 3:
			balance = removeBet(bets, balance);	// removes bets from existing array
			break;
		case 4:
			currentBets(bets);	// displays the current bets the user has made
			break;
		case 5:
			payoutTable();	// shows the payout multipliers if the user wins
			break;
		case 6:
			balance = clearBets(bets, balance);	// clears any bets in the array and return that money to user
			free(bets);
			game = false;
			break;
		default:
			printf("Invalid input. Please try again.\n");
		}
	}

	printf("Thank you for playing Roulette!\n");
	printf("Returning to main menu...\n");
	return balance;	// return to main and update current balance
}

int addBet(BET bets[], int balance)	// add bets, minimum MINPRICE per bet, up to MAXBETS allowed at a time
{
	int choice = 0, updatedBalance = balance;
	bool confirm = false;

	BET* unsaved = (BET*)calloc(MAXBETS, sizeof(BET));	// creates temporary array for use within this session
	if (unsaved == NULL)
	{
		printf("Error. Memory not allocated. Exiting program...\n");
		exit(EXIT_FAILURE);
	}


	if (bets[MAXBETS-1].amount != 0)	// checks if the last array element is already filled
	{
		printf("Maximum amount of bets reached. Returning to menu...\n");
		free(unsaved);
		return balance;
	}

	while (!confirm)
	{
		addBetMenu();

		if (scanf("%d", &choice) != 1)
		{
			printf("Error getting input. Returning to previous menu.\n\n");
			return balance;
		}

		switch (choice)
		{
		case 1:		// add a bet
			addToTemp(bets, unsaved);
			break;
		case 2:		// look at current bets
			currentBets(bets);
			break;
		case 3:		// look at unsaved bets
			currentBets(unsaved);
			break;
		case 4:		// cancel adding
			free(unsaved);
			return balance;
		case 5:		// save and return
			balance = addTempToSaved(bets, unsaved, balance);
			free(unsaved);
			confirm = true;
			break;
		default:
			printf("Invalid input. Please try again.\n");
		}
	}
	return balance;
}

void addToTemp(BET bets[], BET unsaved[])	// only adds ONE bet, then return to previous menu
{
	int choice = 0, bet = 0, price = 0;

	for (int i = 0; i < MAXBETS; i++)
	{
		if (bets[i].amount == 0 && unsaved[i].amount == 0)
		{
			bool confirm = false;
			createBetMenu();

			if (scanf("%d", &choice) != 1)
			{
				printf("Error getting input. Returning to previous menu.\n\n");
				return;
			}

			switch (choice)
			{
			case 1:		// single
				while (!confirm)
				{
					printf("Enter the number you wish to bet on:\n");
					if (scanf("%d", &bet) != 1)
					{
						printf("Error getting input. Returning to previous menu.\n\n");
						return;
					}
					if (bet < 0 || bet > 36)
						printf("Invalid number entered. Please try again.\n");
					else
					{
						if (checkSingleBet(bets, unsaved, bet))	// checks if the bet already exists
						{
							printf("Enter the amount you want to bet. Minimum $%d.\nType 0 to cancel adding.\n", MINPRICE);
							while (price <= MINPRICE)
							{
								if (scanf("%d", &price) != 1)
								{
									printf("Error getting input. Returning to previous menu.\n\n");
									return;
								}
								if (price == 0)
								{
									printf("Returning to previous menu...\n\n");
									return;
								}
								else if (price < MINPRICE)		// checks if user put too little money in
									printf("Amount is too little! Please try again.\n");
							}

							unsaved[i] = createBet(findColour(bet), bet, price);	// adds the bet to the temporary array
							confirm = true;
							return;
						}
						else
							printf("Bet already exists. Please try again.\n\n");
					}
				}
				break;
			case 2:		// colour
				while (!confirm)
				{
					colourBetMenu();

					if (scanf("%d", &bet) != 1)
					{
						printf("Error getting input. Returning to previous menu.\n\n");
						return;
					}

					switch (bet)
					{
					case 1:		// bet on red
						price = getUserPrice(bets, unsaved, "Red(Group)");

						if (price != 1)
						{
							unsaved[i] = createBet("Red(Group)", -1, price);	// adds the bet to the temporary array
							confirm = true;
							return;
						}
						break;
					case 2:		// bet on black
						price = getUserPrice(bets, unsaved, "Black(Group)");

						if (price != 1)
						{
							unsaved[i] = createBet("Black(Group)", -1, price);	// adds the bet to the temporary array
							confirm = true;
							return;
						}
						break;
					case 3:
						printf("Returning to previous menu...\n\n");
						return;
					default:
						printf("Invalid number entered. Please try again.\n");
					}
				}
				break;
			case 3:		// even odd
				while (!confirm)
				{
					evenOddMenu();

					if (scanf("%d", &bet) != 1)
					{
						printf("Error getting input. Returning to previous menu.\n\n");
						return;
					}

					switch (bet)
					{
					case 1:		// even
						price = getUserPrice(bets, unsaved, "Even");

						if (price != 1)
						{
							unsaved[i] = createBet("Odd", -1, price);	// adds the bet to the temporary array
							confirm = true;
							return;
						}
						break;
					case 2:		// odd
						price = getUserPrice(bets, unsaved, "Odd");

						if (price != 1)
						{
							unsaved[i] = createBet("Odd", -1, price);	// adds the bet to the temporary array
							confirm = true;
							return;
						}
						break;
					case 3:
						printf("Returning to previous menu...\n\n");
						return;
					default:
						printf("Invalid number entered. Please try again.\n");
					}

				}
				break;
			case 4:		// range
				while (!confirm)
				{
					rangeBetMenu();

					if (scanf("%d", &bet) != 1)
					{
						printf("Error getting input. Returning to previous menu.\n\n");
						return;
					}

					switch (bet)
					{
					case 1:		// 1 - 12
						price = getUserPrice(bets, unsaved, "Range(1-12)");

						if (price != 1)
						{
							unsaved[i] = createBet("Range(1-12)", -1, price);	// adds the bet to the temporary array
							confirm = true;
							return;
						}
						break;
					case 2:		// 13 - 24
						price = getUserPrice(bets, unsaved, "Range(13-24)");

						if (price != 1)
						{
							unsaved[i] = createBet("Range(13-24)", -1, price);	// adds the bet to the temporary array
							confirm = true;
							return;
						}
						break;
					case 3:		// 25 - 36
						price = getUserPrice(bets, unsaved, "Range(25-26)");

						if (price != 1)
						{
							unsaved[i] = createBet("Range(25-26)", -1, price);	// adds the bet to the temporary array
							confirm = true;
							return;
						}
						break;
					case 4:		// 1 - 18
						price = getUserPrice(bets, unsaved, "Range(1-18)");

						if (price != 1)
						{
							unsaved[i] = createBet("Range(1-18)", -1, price);	// adds the bet to the temporary array
							confirm = true;
							return;
						}
						break;
					case 5:		// 18 - 36
						price = getUserPrice(bets, unsaved, "Range(19-36)");

						if (price != 1)
						{
							unsaved[i] = createBet("Range(19-36)", -1, price);	// adds the bet to the temporary array
							confirm = true;
							return;
						}
						break;
					case 6:
						printf("Returning to previous menu...\n");
						return;
					default:
						printf("Invalid number entered. Please try again.\n");
					}
				}
				break;
			case 5:
				return;
			default:
				printf("Invalid input. Please try again.\n");
			}
		}
	}
	printf("\nReached the maximum amount of bets. Please save any unsaved bets.\n");
	return;
}

bool checkSingleBet(BET bets[], BET unsaved[], int bet)		// checks if the bet number matches any of those in the current and unsaved arrays
{
	for (int i = 0; i < MAXBETS; i++)
	{
		if (bet == 0)
		{
			if (strcmp(bets[i].betType, "Green") == 0 || strcmp(unsaved[i].betType, "Green") == 0)
				return false;
		}	
		else if (bets[i].location == bet || unsaved[i].location == bet)
			return false;
	}
	return true;	// no match
}

bool checkBetType(BET bets[], BET unsaved[], char* type)	// checks if the type of bet has already been made
{
	for (int i = 0; i < MAXBETS; i++)
	{
		if (strcmp(bets[i].betType, type) == 0 || strcmp(unsaved[i].betType, type) == 0)
			return false;
	}
	return true;	// no match
}

BET createBet(char* betType, int location, int amount)
{
	BET b;
	strncpy(b.betType, betType, MAXSTR);
	b.location = location;
	b.amount = amount;

	return b;
}

int addTempToSaved(BET bets[], BET unsaved[], int balance)		// combines the unsaved array to the user's current bets
{
	for (int i = 0; i < MAXBETS; i++)
	{
		if (bets[i].amount == 0 && unsaved[i].amount != 0)
		{
			bets[i] = createBet(unsaved[i].betType, unsaved[i].location, unsaved[i].amount);

			balance = balance - unsaved[i].amount;
		}
	}
	return balance;
}

int getUserPrice(BET bets[], BET unsaved[], char* lookFor)	// gets user input for what bet they would like (group)
{
	int price = 0;

	if (checkBetType(bets, unsaved, lookFor))
	{
		printf("Enter the amount you want to bet. Minimum $%d.\nType 0 to cancel adding.\n", MINPRICE);
		while (price <= MINPRICE)
		{
			if (scanf("%d", &price) != 1)
			{
				printf("Error getting input. Returning to previous menu.\n\n");
				return;
			}
			if (price == 0)
			{
				printf("Returning to previous menu...\n\n");
				return 1;;
			}
			else if (price < MINPRICE)		// checks if user put too little money in
				printf("Amount is too little! Please try again.\n");
		}
		return price;
	}
	else
		printf("Bet already exists. Please try again.\n\n");
	return 1;
}

char* findColour(int bet)	// 18 is found by the length of the BLACK and RED arrays
{
	if (bet == GREEN[0])
		return "Green";

	for (int i = 0; i < 18; i++)
	{
		if (bet == BLACK[i])
			return "Black(Single)";
		else if (bet == RED[i])
			return "Red(Single)";
	}
}

char* findGroupColour(int bet)	// 18 is found by the length of the BLACK and RED arrays
{
	for (int i = 0; i < 18; i++)
	{
		if (bet == BLACK[i])
			return "Black(Group)";
		else if (bet == RED[i])
			return "Red(Group)";
	}
	return "N/A";	// for the case if the colour is green
}

int removeBet(BET bets[], int balance)	// delete existing bets
{
	int choice = 0;
	bool confirm = false;
	currentBets(bets);

	if (bets[0].amount == 0)		// checks if the array is empty
	{
		printf("\nThere are no bets to remove. Returning to menu...\n");
		return balance;
	}

	while (!confirm)
	{
		printf("\nWhich bet do you want to remove?\n");
		printf("Type 0 to cancel.\n");

		if (scanf("%d", &choice) != 1)
		{
			printf("Error getting input. Returning to previous menu.\n\n");
			return balance;
		}

		if (choice == 0)
		{
			printf("Removing bet cancelled.\n");
			return balance;
		}

		if (bets[choice - 1].amount == 0)
			printf("Bet does not exist. Please try again.");
		else
		{
			balance = balance + bets[choice - 1].amount;	// adds subtracted balance back
			bets[choice - 1] = createBet("", -1, 0);	// sets bet to default values
			confirm = true;
			printf("Bet successfully removed.\n");
		}
	}

	reorderBets(bets);	// reorders the bets so empty ones are last
	printf("Returning to previous menu...\n\n");
	return balance;
}

void reorderBets(BET bets[])
{
	BET hold;

	for (int i = 0; i < MAXBETS; i++)
	{
		if (bets[i].amount == 0)
		{
			hold = bets[i];
			shiftBetsLeft(bets, i);

			bets[MAXBETS - 1] = hold;		// places empty struct at the end of array
		}
	}
}

void shiftBetsLeft(BET bets[], int hold) // shifts array 1 spot to the left
{
	for (int i = hold; i < MAXBETS; i++)
	{
		bets[i] = bets[i + 1];
	}
}

void currentBets(BET bets[])		// view the current bets in the array that is passed
{
	int check = 0;

	for (int i = 0; i < MAXBETS; i++)	// checks if the entire array is empty
	{
		if (bets[i].amount != 0)
			check++;
	}

	if (check == 0)
	{
		printf("\nThere are no current bets.\n\n");
		return;
	}

	for (int i = 1; i < MAXBETS + 1; i++)
	{
		if (bets[i - 1].amount != 0 && bets[i - 1].betType != "")
		{
			if (strcmp(bets[i - 1].betType, "Red(Single)") == 0 || strcmp(bets[i - 1].betType, "Black(Single)") == 0)
			{
				printf("\n%d. %s\n%d\n$%d\n", i, bets[i - 1].betType, bets[i - 1].location, bets[i - 1].amount);	// for single bets
			}
			else
				printf("\n%d. %s\n$%d\n", i, bets[i - 1].betType, bets[i - 1].amount);	// for grouped bets
		}
	}
	return;
}

int clearBets(BET bets[], int balance)		// clears the bets in the array and return money to user, used WHEN they want to exit
{
	for (int i = 0; i < MAXBETS; i++)
	{
		if (bets[i].amount != 0)
		{
			balance = balance + bets[i].amount;
		}
	}
	return balance;
}

int playRoulette(BET bets[], int balance)	// determines the amount of money the user wins based on where the ball lands
{
	int ball = spinBall(), won = 0;;

	for (int i = 0; i < MAXBETS; i++)
	{
		if (bets[i].amount != 0)
		{
			if (bets[i].location == ball)	// checks for single numbers
			{
				balance = balance + payout(35, bets[i].amount, bets[i].betType);
				won++;
			}

			if (strcmp(bets[i].betType, findGroupColour(ball)) == 0)		// checks for red/black
			{
				balance = balance + payout(1, bets[i].amount, bets[i].betType);
				won++;
			}

			if (strcmp(bets[i].betType, "Range(1-12)") == 0 && 1 <= ball <= 12)	// checks number ranges - dozens
			{
				balance = balance + payout(2, bets[i].amount, bets[i].betType);
				won++;
			}
			else if (strcmp(bets[i].betType, "Range(13-24)") == 0 && 13 <= ball <= 24)
			{
				balance = balance + payout(2, bets[i].amount, bets[i].betType);
				won++;
			}
			else if (strcmp(bets[i].betType, "Range(25-36)") == 0 && 25 <= ball <= 36)
			{
				balance = balance + payout(2, bets[i].amount, bets[i].betType);
				won++;
			}

			if (strcmp(bets[i].betType, "Range(1-18)") == 0 && 1 <= ball <= 18)	// checks number ranges - halves
			{
				balance = balance + payout(1, bets[i].amount, bets[i].betType);
				won++;
			}
			else if (strcmp(bets[i].betType, "Range(19-24)") == 0 && 19 <= ball <= 24)
			{
				balance = balance + payout(1, bets[i].amount, bets[i].betType);
				won++;
			}


			if (strcmp(bets[i].betType, "Even") == 0 && (ball % 2) == 0)	// checks even or odd
			{
				balance = balance + payout(1, bets[i].amount, bets[i].betType);
				won++;
			}
			else if (strcmp(bets[i].betType, "Odd") == 0 && (ball % 2) != 0)
			{
				balance = balance + payout(1, bets[i].amount, bets[i].betType);
				won++;
			}
		}
	}

	if (won == 0)
		printf("Sorry! None of your bets won.\n");

	return balance;
}

int payout(int multiplier, int betAmount, char* type)	// multiplies the bet amount by the payout
{
	int winnings = multiplier * betAmount;

	printf("%s\nYou've won $%d!\n", type, winnings);

	return winnings;
}


int spinBall()		// uses rand() to 'spin' the roulette ball
{
	srand(time(0));	// seed

	int ball = rand() % 36;

	return ball;
}
