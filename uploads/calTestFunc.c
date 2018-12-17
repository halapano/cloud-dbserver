/* calTestFunc.c - give the function defination for calTest.c */

#include<stdio.h>
#include "calTest.h"

/* This function is defined for calculating given two values and return a max one */
int calMaxOne(int x,
		int y)
{
	return (x > y) ? x : y;
}

/* This function is defined for outputing a given number of character on the screen */
void fillChar(int numSpace,
		char ch,
		char newline)
{
	int time = 0;

	while (time != numSpace) {
		putchar(ch);
		time++;

	}

	if (newline == 'y')
		printf("\n");

}
