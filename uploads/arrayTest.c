#include<stdio.h>

#define MAXSIZE 10

int * plusArray(int currentSize, int array[]);
int main() {

	int count, size, arr[MAXSIZE];

	size = MAXSIZE;

	// The only way to calculate the length is like below.
	for (count = 0; count < size ; count++) {
		arr[count] = count;
		printf("element %d: %d\n",count, arr[count]);
	}

	printf("Do you want to add capacity to that array(y or n)\n");

	while (getchar() == 'y') {
		
		plusArray(size, arr);

		size = size + MAXSIZE;

		while (getchar() != '\n')
			break;
	}

	printf("done,\n");

	return 0;

}

// Defined function to extend the length of a given array
// and print each single element on the screen
int *plusArray(int currentSize,
		int array[]) {
	int temp[currentSize + MAXSIZE];

	for (int i = 0; i <currentSize; i++){
		temp[i] = array[i];
		printf("element %d: %d\n", i, temp[i]);

	}

	return *temp;
}
