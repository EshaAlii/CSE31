#include <stdio.h>
#include <stdlib.h>
// #include <malloc.h>

void printArray(int** arr, int n){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			printf("%d ", *(*(arr+i)+j));
		}
		printf("\n");
	}
	printf("\n");
}

int main() {
	int i = 0, j = 0, n = 5;
	int **arr = (int**)malloc(n * sizeof(int*));

	// (3) Add your code to complete allocating and initializing the 2-D array here. The content should be all 0.
	
	for (i = 0; i < n; i++){
		// We initialize the i portion of our array so it truly becomes a matrix
		*(arr+i) = (int*)malloc(n*sizeof(int));
		for (j = 0; j < n; j++){
			// We then create a grid by first dereferencing the array of i and then the array of j
			*(*(arr+i)+j) = 0;
		}
	}


    // This will print out your array
	printArray(arr, n);

    // (6) Add your code to make arr a diagonal matrix
    for (i = 0; i < n; i++){
		*(*(arr+i)+i) = i+1;
	}
	
	// (7) Call printArray to print array
	printArray(arr, n);
    
	return 0;
}

// void printArray(int ** array, int size) {
//     // (5) Implement your printArr here:

// }
