#include <stdio.h>

int main() {
	int i;
	int four_ints[4];
	char* four_c;

	for(i = 0; i < 4; i++)
        four_ints[i] = 2;

	printf("%x\n", four_ints[0]);
	
    four_c = (char*)four_ints;

	for(i = 0; i < 4; i++)
        four_c[i] = 'A' + i; // ASCII value of 'A' is 65 or 0x41 in Hex.
    
    // Add your code for the exercises here:

	// Print out first and second indeces of our four_ints array
	printf("%x\n", four_ints[0]);
	printf("%x\n", four_ints[1]);

	// Print out the values of our four_ints array
	for (i = 0; i < 4; i++){
		printf("%x", four_ints[i]);
	}

	// Print a new line
	printf("\n");

	// Print out the values of our four_c array
	for (i = 0; i < 4; i++){
		printf("%x", four_c[i]);
	}

	// Print a new line
	printf("\n");

	// Print out the values and addresses for our four_ints array
	for (i = 0; i < 4; i++){
		printf("Values: %x\n Addresses: %p \n", four_ints[i], &four_ints[i]);
	}

	// Print out the values and addresses for our four_c array
	for (i = 0; i < 4; i++){
		printf("Values: %x\n Addresses: %p \n", four_c[i], &four_c[i]);
	}

	// Extra printing for understanding
	printf("%p\n", &four_ints[0]);
	printf("%p\n", &four_c[0]);
	printf("%p\n", &four_c[1]);
	printf("%p\n", &four_ints[1]);

	return 0;
}