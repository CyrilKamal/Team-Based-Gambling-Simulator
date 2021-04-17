#pragma once

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define _CRT_SECURE_NO_WARNINGS

//Fucntion prototypes
int shuffle(int cards[]);
int convert_faces(int a);
void card_display(int num);
int blackjack(int balance);
int play(int balance);
int main(int argc, char* argv[]);
int bet(int balance);