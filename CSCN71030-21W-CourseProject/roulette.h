#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAXSTR 15
#define MAXBETS 5
#define MINPRICE 5

// structures
typedef struct bet
{
	char betType[MAXSTR];	// single, red, black, green, , etc. check payout table
	int location; // location of where the bet is, from 0-36, -1 if the bet is a group bet
	int amount;	// amount of money
}BET;

static int RED[] = { 1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36 };
static int BLACK[] = { 2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35 };
static int GREEN[] = { 0 };


// working functions
int roulette(int);
int addBet(BET[], int);
BET createBet(char*, int, int);
void addToTemp(BET[], BET[]);
bool checkSingleBet(BET[], BET[], int);
bool checkBetType(BET[], BET[], char*);
int addTempToSaved(BET[], BET[], int);
int getUserPrice(BET[], BET[], char*);
char* findColour(int);
char* findGroupColour(int);

int removeBet(BET[], int);
void reorderBets(BET[]);
void shiftBetsLeft(BET[], int);

void currentBets(BET[]);
int clearBets(BET[], int);

int playRoulette(BET[], int);
int payout(int, int, char*);
int spinBall();