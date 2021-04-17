#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "slots.h"
#define _CRT_SECURE_NO_WARNINGS


int slotFunctions(int bal) {
	int slot[MAXSLOTSIZE][MAXSLOTSIZE];
	int bet;
	printf("Hello and welcome to slots, please input your bet for the slot! \n");
	scanf_s("%lf", &bet);
	printf("\n");

	if (bet>bal)
	{
		printf("You cant bet more than your balance!\n");
	}
	else
	{
		bal = bal - bet;
		spinSlot(slot);
		printSlot(slot);
		if (checkMatch(slot, 1) == 1) {
			printf("Congratulations you have doubled your bet with the 1 symbol!\n");
			bal = bal + bet * 3;
			printf("New balance is now %lf\n", bal);
		}
		else if (checkMatch(slot, 2)) {
			printf("Congratulations you have doubled your bet with the 2 symbol!\n");
			bal = bal + bet * 3;
			printf("New balance is now %lf\n", bal);
		}
		else if (checkMatch(slot, 3)) {
			printf("Congratulations you have tripled your bet with the 3 symbol!\n");
			bal = bal + bet * 4;
			printf("New balance is now %lf\n", bal);
		}
		else if (checkMatch(slot, 4)) {
			printf("Congratulations you have tripled your bet with the 4 symbol!\n");
			bal = bal + bet * 4;
			printf("New balance is now %lf\n", bal);
		}
		else if (checkMatch(slot, 5)) {
			printf("Congratulations you have quadrupled your bet with the 5 symbol!\n");
			bal = bal + bet * 5;
			printf("New balance is now %lf\n", bal);
		}
		else if (checkMatch(slot, 6)) {
			printf("Congratulations you have quadrupled your bet with the 6 symbol!\n");
			bal = bal + bet * 5;
			printf("New balance is now %lf\n", bal);
		}
		else if (checkMatch(slot, 7)) {
			printf("Congratulations you have quintupled your bet with the 7 symbol!\n");
			bal = bal + bet * 6;
			printf("New balance is now %lf\n", bal);
		}
		else if (checkMatch(slot, 8)) {
			printf("Congratulations you have quintupled your bet with the 8 symbol!\n");
			bal = bal + bet * 6;
			printf("New balance is now %lf\n", bal);
		}
		else if (checkMatch(slot, 9)) {
			printf("Congratulations you have gotten 100x on your bet with the 9 symbol!\n");
			bal = bal + bet * 101;
			printf("New balance is now %lf\n", bal);
		}
		else
		{
			printf("\n");
			printf("You have not gotten a matching reel, you have gotten a 0x\n");
		}

	}
	return bal;
}