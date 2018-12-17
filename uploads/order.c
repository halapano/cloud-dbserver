#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>

/*
 * The ABC Mail Order Grocery sells arithockes for $2.05 per pounds, beets for $1.15 per pounds, and 
 * carrots for $1.09 per pounds. It gives a 5% discount for orders of $100 pr more prior to adding 
 * shipping costs. It charges $6.50 shipping and handing for any order of 5 pounds or under, $14.00 
 * shipping and handing for orders over 5 pounds and under 20 pounds, and $14 plus $0.50 per pounds 
 * for shipments of 20 pounds or more.  
 */ 

void display_home();
char get_char();
char get_item(); 
float get_pounds();
float get_item_per_pounds(char a);
float get_ship_cost(float a);
float get_extra_ship(float pounds);
float cal_price(float a, float b, float c);
void order_comfirm();
int main() { 

	char item;//, itemName[20]; 
	float pounds, itemPP, itemShip, price, extShip; 
	//bool state = false; 
	
	display_home();
	
	item = get_item(); 

	printf("\nFor how many pounds(no more than 3000): \n"); 

	pounds = get_pounds();
	
	printf("\n"); 

	itemPP = get_item_per_pounds(item); 

	itemShip = get_ship_cost(pounds); 

	extShip = get_extra_ship(pounds);

	price = cal_price(pounds, itemPP, itemShip);

	printf("---------------------------------------\n");
	printf("Your order detail:\n");
	printf("---------------------------------------\n");
	printf("Item name: %c\n", item);
	printf("Pounds: %.2f\n", pounds);
	printf("Item Cost: %.2f\n", itemPP * pounds);
	printf("Basic Shipping Cost: %.2f\n", itemShip);
	printf("Extra Shipping and handing Cost: %.2f\n", extShip);
	printf("---------------------------------------\n");
	printf("Total: %.2f\n", price);
	printf("\n");
	printf("Comfirm(Y/N)\n");

	while (getchar() != '\n') continue; // Skip the rest of input line.

	order_comfirm();

	return 0;

}

void order_comfirm() {

	char cmf;

	while ((cmf = get_char()) != 'q') { // error: cmf = scanf("%c", &cmf)...

		cmf = toupper(cmf);

		printf("\n");

		switch (cmf) {

			case 'Y':  printf("Order comfired.\n");
		
				printf("Item deliver shortly.\n");

				break;

			case 'N': printf("Order canceled.\n");
		
				printf("Transation denied.\n");

				break;

			default: printf("System only recognize y, Y, n and N.\n");

				printf("Please try again:\n");

				continue;
		}

		break;

	}


}

float cal_price(float a, float b, float c) {

	const float ExtShipCost = 0.50;

	float sum = 0.00;

	if (b != 0.00 && c != 0.00) {

		if (a <= 20 && a > 0) sum = a * b + c;

		else sum = a * b + c + (a - 20) * ExtShipCost; // More than 20 pounds.

	} else {

		printf("Error(s) occured. Transtion denied.\n");
		printf("Please try again.\n");

	}

	return sum;

}

float get_extra_ship(float pounds) {

	float extShip = 0.00;

	if (pounds > 20.00) extShip = (pounds - 20.00) * 0.50;

	return extShip;

}

// We may not be able to use get_char() function in get_item() and get_pounds().
// As in these two function, they should display error input if nessesary.
char get_item() {

	char input, ch;
	int state;

	state = scanf("%c", &input);

	input = tolower(input);

	while (state != 1 || (input != 'a' && input != 'b' && input != 'c'))  {

		putchar(input);

		while ((ch = getchar()) != '\n') putchar(ch);

		printf(" are not valid inputs.\n");
		printf("System only reconginzes a, b or c.\n");
		printf("Please try again:\n");

		scanf("%c", &input);

		input = tolower(input);

	}

	return input;

}

float get_pounds() {

	const float limit = 3000.00;

	float input = 0.00;
	char ch;

	while ((scanf("%f", &input)) != 1 || input > limit || input <= 0.00) {

		while ((ch = getchar()) != '\n') putchar(ch);

		printf(" Invalid input.\n");
		printf("System only reconginzes integeric input that no more than 3000.00.\n");
		printf("Please try again:\n");
		printf("For how many pounds: \n");

	}

	return input;

}

float get_item_per_pounds(char a) {

	const float APP = 2.05; 
	const float BPP = 1.15; 
	const float CPP = 1.09; 	

	float itemPerPounds = 0.00;

	if (isalpha(a)) {

		switch (a) {

			case 'a': itemPerPounds = APP;

				break;

			case 'b': itemPerPounds = BPP;

				break;

			case 'c': itemPerPounds = CPP;

				break;

		}
	
	} else {

		printf("Invalid Access: Cannot get item\n");

	}

	return itemPerPounds;

}

float get_ship_cost(float a) {

	const float SHIPCOST_1 = 6.50; 
	const float SHIPCOST_2 = 14.00;  

	float shipCost = 0.00;

	if (sizeof(a) == 4) {
 
		// I was trying to use [isdigit()] to identify the type of float.
		// But it didn't work. float is not digit. sizeof function is better.

		if (a > 0.00 && a <= 5.00) shipCost = SHIPCOST_1;

		else shipCost = SHIPCOST_2;

	} else {

		printf("Invalid Access: Cannot get the number of pounds.\n");

	}

	return shipCost;

}

// This a method to get the first character and skip the rest of the input.!!
char get_char() {

	char ch;

	ch = getchar();

	while (getchar() != '\n') continue;

	return ch;

}

// This method is to display message and some choices for user.
// Just make the main() function more clean and simple.
void display_home() {

	printf("Please finish the order\n"); 
	printf("We have 3 items for choosing:\n"); 
	printf("[a --- Arithchokes($2.05 per pound)]\n"); 
	printf("[b --- Beets($1.15 per pounds)]\n"); 
	printf("[c --- Carrots($1.09 per pounds)]\n"); 
	printf("\n"); 
	printf("Item: "); 

}	
