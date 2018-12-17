#include<stdio.h>

int main()
{
	int * pi;
	int val = 5;

	pi = &val;

	printf("%d\n", *pi);
	printf("%x\n", pi);
	printf("%x\n", &val);

	return 0;
}
