#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "slots.h"

void spinSlot(int arr[MAXSLOTSIZE][MAXSLOTSIZE])
{
	srand(time(NULL));
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int n;
			n = rand() % 9;
			arr[i][j] = n;
		}
	}
}

void printSlot(int arr[MAXSLOTSIZE][MAXSLOTSIZE]) {
	printf("----------Slot----------");
	for (int i = 0; i < 3; i++)
	{
		printf("\n");
		for (int j = 0; j < 3; j++) {
			printf("%d", arr[i][j]);
		}
	}
	
}

int checkMatch(int arr[MAXSLOTSIZE][MAXSLOTSIZE], int symbol) {
	if (arr[0][0] == arr[0][1] && arr[0][1] == arr[0][2] && arr[0][0] == symbol)
		return 1;
	else if (arr[1][0] == arr[1][1] && arr[1][2] && arr[1][0] == symbol)
		return 1;
	else if (arr[2][0] == arr[2][1] && arr[2][1] == arr[2][2] && arr[2][0] == symbol)
		return 1;
	else if (arr[0][0] == arr[1][0] && arr[1][0] == arr[2][0] && arr[0][0] == symbol)
		return 1;
	else if (arr[0][1] == arr[1][1] && arr[1][1] == arr[2][1] && arr[0][1] == symbol)
		return 1;
	else if (arr[0][2] == arr[1][2] && arr[1][2] == arr[2][2] && arr[0][2] == symbol)
		return 1;
	else if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2] && arr[0][0] == symbol)
		return 1;
	else if (arr[0][3] == arr[1][1] && arr[1][1] == arr[3][0] && arr[0][3] == symbol)
		return 1;
	else
		return 0;
}

