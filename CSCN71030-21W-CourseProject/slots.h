#pragma once
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAXSLOTSIZE 3

void spinSlot(int arr[MAXSLOTSIZE][MAXSLOTSIZE]);
void printSlot(int arr[MAXSLOTSIZE][MAXSLOTSIZE]);
//void exit();
int checkMatch(int arr[MAXSLOTSIZE][MAXSLOTSIZE], int symbol);
int slots(int bal);