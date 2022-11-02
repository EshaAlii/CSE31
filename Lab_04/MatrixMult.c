
#include <stdio.h>
#include <stdlib.h>
// #include <malloc.h>

int** matMult(int **a, int **b, int size) {
	// (4) Implement your matrix multiplication here. You will need to create a new matrix to store the product.
	
	// Create a new array called matnew that will be equal to the product of matA and matB
	int **matnew = (int**)malloc(size * sizeof(int*));

	// Fill our matnew array with 0's
	for (int i = 0; i < size; i++){
		*(matnew+i) = (int*)malloc(size*sizeof(int));
		for (int j = 0; j < size; j++){
			*(*(matnew+i)+j) = 0;
		}
	}

	// Create a triple for loop to keep i and j stationary...
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			// k will traverse the matrix, allowing us to properly multiply each index...
			for (int k = 0; k < size; k++){
				// We set our matnew equal to matA's row multiplied by matB's column and then add it to itself.
				*(*(matnew+i)+j) = *(*(a+i)+k) * *(*(b+k)+j) + *(*(matnew+i)+j);
			}
		}
	}

	// We return matnew
	return matnew;

}

void printArray(int **arr, int n) {
	// (2) Implement your printArray function here
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			printf("%d ", *(*(arr+i)+j));
		}
		printf("\n");
	}
	printf("\n");
}

int main() {
	int n = 5;
	int **matA, **matB, **matC;

	// (1) Define 2 (n x n) arrays (matrices).

	// Initialize our arrays
	matA = (int**)malloc(n * sizeof(int*));
	matB = (int**)malloc(n * sizeof(int*));
	matC = (int**)malloc(n * sizeof(int*));

	// We fill matA with a number
	for (int i = 0; i < n; i++){
		*(matA + i) = (int*)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++){
			*(*(matA+i)+j) = 5;
		}
	}

	// We fill matB with a number
	for (int i = 0; i < n; i++){
		*(matB + i) = (int*)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++){
			*(*(matB+i)+j) = 2;
		}
	}

	// (3) Call printArray to print out the 2 arrays here.

	// We print our two arrays that will be multiplied
	printArray(matA, n);
	printArray(matB, n);
	
	// (5) Call matMult to multiply the 2 arrays here.

	// We set matC equal to the product of matA and matB
	matC = matMult(matA, matB, n);
	
	// (6) Call printArray to print out resulting array here.

	// We then print matC
	printArray(matC, n);

    return 0;
}