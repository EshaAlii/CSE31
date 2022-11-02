
#include <stdio.h>
#include <stdlib.h>

int main() {
	// Creating our variables
	int num;
	int *ptr;
	int **handle;

	// Initialization + Pointer operations
	num = 14;
	ptr = (int *)malloc(2 * sizeof(int));
	*ptr = num;
	handle = (int **)malloc(1 * sizeof(int *));
	*handle = ptr;

	// Print out the addresses
	printf("%p \n", &num);
	printf("%p \n", &(*ptr));
	printf("%p \n", &(**handle));

	// End program
	return 0;
} 

