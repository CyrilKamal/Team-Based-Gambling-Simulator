#include "BlackJack.h"


int shuffle(int cards[])
{

	int t;
	int i;
	int deck[52];
	for (i = 0; i < 52; i++)
		deck[i] = (i / 13 + 3) * 100 + i % 13 + 1;

	srand(time(NULL));
	for (i = 0; i < 52; i++)
	{
		do
		{
			t = rand() % 52;
		} while (deck[t] == 0);
		cards[i] = deck[t];
		deck[t] = 0;
	}

	return 0;
}

int convert_faces(int a)
{
	if ((a % 100 == 11) || (a % 100 == 12) || (a % 100 == 13)) return (a / 100) * 100 + 10;
	else return a;
}

void card_display(int num)
{
	char fl;
	int po_num;

	fl = num / 100;
	po_num = num % 100;
	switch (po_num)
	{
	case 1:
	{
		printf("*******\n");
		printf("*     *\n");
		printf("* %c   *\n", fl);
		printf("*   A *\n");
		printf("*     *\n");
		printf("*******\n");
		break;
	}
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	{
		printf("*******\n");
		printf("*     *\n");
		printf("* %c   *\n", fl);
		printf("*  %2d *\n", po_num);
		printf("*     *\n");
		printf("*******\n");
		break;
	}
	case 11:
	{
		printf("*******\n");
		printf("*     *\n");
		printf("* %c   *\n", fl);
		printf("*   J *\n");
		printf("*     *\n");
		printf("*******\n");
		break;
	}
	case 12:
	{
		printf("*******\n");
		printf("*     *\n");
		printf("* %c   *\n", fl);
		printf("*   Q *\n");
		printf("*     *\n");
		printf("*******\n");
		break;
	}
	case 13:
	{
		printf("*******\n");
		printf("*     *\n");
		printf("* %c   *\n", fl);
		printf("*   K *\n");
		printf("*     *\n");
		printf("*******\n");
		break;
	}

	}
}

int blackjack(int balance)
{
	int i;
	int psum = 0;
	int dsum = 0;
	int pcards[5] = { 0 };
	int dcards[5] = { 0 };
	int cards[52];
	char d;
	int bet;
	bool game = true;
	

		printf("\nWelcome to !!BLACKJACK!!\n"
			"Please enter the amount you want to bet.\n");
		printf("Once you've entered your amount press [ENTER] to continue.\nOr enter '0' to return to the main menu.\n");
		if (scanf_s("%d", &bet) != 1)
		{
			printf("Error getting input.\n\n");
			exit(EXIT_FAILURE);
		}

		if (bet == 0)	// returns to main.c if bet amount is 0
		{
			printf("\nReturning to main menu...\n\n");
			return balance;
		}

		//shuffle the cards
		shuffle(cards);

		//give the card outputs
		pcards[0] = cards[0];
		pcards[1] = cards[1];
		dcards[0] = cards[2];
		dcards[1] = cards[3];

		//the two players cards
		printf("One of the dealer's cards:\n");
		card_display(dcards[0]);
		printf("\n");
		printf("Your cards:\n");
		card_display(pcards[0]);
		card_display(pcards[1]);


		i = 0;
		for (i = 0; i < 2; i++)
		{
			if (pcards[i] % 100 == 1)
			{
				printf("Choose a value for the card %d, input [y] for 11 or [n] for 1 :\n", i + 1);
				do {
				if	(scanf_s("%c", &d) != 1)
				{
					printf("Error getting input.\n\n");
					exit(EXIT_FAILURE);
				}
				} while (d != 'y' && d != 'n');

				if (d == 'y')
				{
					printf("You've chosen to value the Ace at 11.\n");
					psum = psum + 11;
				}
				else if (d == 'n')
				{
					printf("You've chosen to value the Ace at 1.\n");
					psum = psum + 1;
				}
			}
			else if (convert_faces(pcards[i]) % 100 == 10) psum = psum + 10;
			else psum = psum + pcards[i] % 100;

			if (psum > 21)																				///////////////
			{
				printf("You got a bust with %d points\n\n", psum);
				printf("The dealer wins! Better luck next time:(\n");

				return balance - bet;
			}
			else if (psum == 21)																		///////////////
			{
				printf("You are currently at: %d points\n\n", psum);
				printf("CONGRATULATIONS! You win 2x your bet!\n");
				return balance + bet * 2;
			}
		}
		printf("You are currently at: %d points\n\n", psum);

		//whether player get another cards
		i = 0;
		for (i = 0; i < 3; i++)
		{
			char j = 'n';

			printf("Would you like to hit or stand? Input [y] to hit or [n] to stand:\n");
			do {
				if (scanf_s("%c", &j) != 1)
				{
					printf("Error getting input.\n\n");
					exit(EXIT_FAILURE);
				}

			} while (j != 'y' && j != 'n');

			if (j == 'y')
			{
				printf("You've got another card now.\n");
				pcards[i + 2] = cards[i + 4];
				printf("Your card %d is:\n", i + 3);
				card_display(pcards[i + 2]);

				if (pcards[i + 2] % 100 == 1)
				{
					printf("Choose A value of the card %d, input [y] for 11 or [n] for 1:\n", i + 3);
					do {
						if (scanf_s("%c", &d) != 1)
						{
							printf("Error getting input.\n\n");
							exit(EXIT_FAILURE);
						}

					} while (d != 'y' && d != 'n');
					if (d == 'y')
					{
						printf("You've chosen value 11 for card A.\n");
						psum = psum + 11;
					}
					else if (d == 'n')
					{
						printf("You've chosen value 1 for card A.\n");
						psum = psum + 1;
					}
				}
				else if (convert_faces(pcards[i + 2]) % 100 == 10) psum = psum + 10;
				else psum = psum + pcards[i + 2] % 100;

				if (psum > 21)
				{
					printf("You got a bust with %d points\n\n", psum);
					printf("The dealer wins! Better luck next time:(\n");
					return balance - bet;
				}
				else if (psum == 21)          /////////////
				{
					printf("You are currently at: %d points\n\n", psum);
					printf("CONGRATULATIONS! You win x2 your bet!\n");
					return balance + bet * 2;
				}
				else printf("You are currently at: %d points\n\n", psum);
			}
			else
			{
				printf("You are currently at: %d points\n\n", psum);
				break;
			}
		}
		if (i == 3)
		{
			printf("YAY you win! Since the sum of your 5 cards are less than 21, lucky you!\n");
			return balance + bet * 2;
		}

		//the 2 cards of the dealer

		printf("Dealer's cards:\n");
		card_display(dcards[0]);
		card_display(dcards[1]);

		if (dcards[0] % 100 + dcards[1] % 100 == 2)
		{
			dsum = 12; //two A cards
			printf("The dealer is currently at: %d points\n\n", dsum);
		}
		else if ((convert_faces(dcards[0])) % 100 + (convert_faces(dcards[1])) % 100 == 1)
		{
			dsum = 21;
			printf("The dealer is currently at: %d points\n\n", dsum);
			printf("The dealer wins! Better luck next time:(\n");
			return balance - bet;
		}
		else if (dcards[0] % 100 == 1 || dcards[1] % 100 == 1)
		{
			dsum = (dcards[0] + dcards[1]) % 100 + (rand() % 2) * 10;
			printf("The dealer is currently at: %d points\n\n", dsum);
		}
		else
		{
			dsum = (convert_faces(dcards[0])) % 100 + (convert_faces(dcards[1])) % 100;
			printf("The dealer is currently at: %d points\n\n", dsum);
		}

		//whether dealer gets another card until dsum>16
		for (i = 0; i < 3 && dsum < 17; i++)
		{
			dcards[i + 2] = cards[i + 7];
			printf("Dealer's card %d is:\n", i + 3);
			card_display(dcards[i + 2]);

			if (dcards[i + 2] % 100 == 1)
			{
				if (dsum + 11 <= 21)
				{
					printf("The dealer has chosen the Ace as 11\n");
					dsum = dsum + 11;
					printf("The dealer is currently at: %d points\n\n", dsum);
				}
				else
				{
					printf("The dealer has chosen the Ace as 1\n");
					dsum = dsum + 1;
					printf("The dealer is currently at: %d points\n\n", dsum);
				}
			}
			else
			{
				dsum = dsum + convert_faces(dcards[i + 2]) % 100;
				printf("The dealer is currently at: %d points\n\n", dsum);
			}
		}
		if (i == 3)
		{
			printf("Dealer wins! Since the sum of its 5 cards is less than 21! Super lucky!\n");
			return balance - bet;
		}

		//when dealer's sum is 
		if (dsum > 21 || psum > dsum)
		{
			printf("CONGRATULATIONS! You win x2 your bet!\n");
			return balance + bet * 2;
		}
		else if (psum == dsum)
		{
			printf("Yikes, you and the dealer got the same score, so close!\n");
			return balance - bet;
		}
		else if (psum < dsum)
		{
			printf("The dealer wins! Better luck next time :)\n");
			return balance - bet;
		}

	return balance;
}


int play(int balance)
{
	char again;
	bool game = true;

	while (game)
	{
		balance = blackjack(balance);
		printf("\nYour current balance: %d\n", balance);
		printf("\nWould you like to continue playing? Input [y] or [n]:\n");
		do
		{
			if (scanf_s("%c", &again) != 1)
			{
				printf("Error getting input.\n\n");
				exit(EXIT_FAILURE);
			}

		} while (again != 'y' && again != 'n');

		if (again == 'y')
		{
			printf("\nOK, let's keep on going!\n\n");
		}
		else
			game = false;
	}
	return balance;
}


int bet(int balance) 
{
	printf("\n\nPlease enter the amount you want to bet:");
	scanf_s("%d", &bet);

	if (bet > balance) //If player tries to bet more money than player has
	{
		printf("\nYou cannot bet more money than you currently have.");
		printf("\nTry again: ");
		scanf_s("%d", &bet);
		return bet;
	}
	else return bet;
}



