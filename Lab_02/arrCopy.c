#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Function that prints out our array
void printArr(int *a, int size, char *name){

    // First print out the name of the array
	printf("%s", name);

    // Then the rest of the message
    printf(" array's contents:");

    // We use a for loop to print out each element of the array
    for (int i = 0; i < size; i++){
        printf(" %d", *(a+i));
    }

    // We then print a newline
    printf("\n");
}

// Function that copies our array and outputs it backward
int *arrCopy(int *a, int size){

    // Create a Reverse array that we will output
    int *reverse;
    reverse = (int*) malloc(size * sizeof(int));

    // Our rise variable 
    int rise;

    // Going through our temp array and placing in our original array in reverse
    for (int i = size-1; i >= 0; --i){

        // Make our rise varaible go backward through the original array
        rise = *(a+i); //rise = a[1]

        // Set our reverse array equal to the rise variable at the original array's index
        *(reverse + size - i - 1) = rise;
        
    }
    
    // Return our reversed array
    return reverse;
}

int main(){
    // Initialize our variables
    int n;
    int *arr;
    int *arr_copy;
    int i;

    // Ask user for the size of our array
    printf("Enter the size of array you wish to create: ");
    scanf("%d", &n);
    
    // Dynamically create an int array of n items
    arr = (int *) malloc (n*sizeof(int));
    
    // Ask user to input contents of our array
    for (int i = 0; i < n; i++){
        printf("Enter array element #%d", i+1);
        printf(": ");
        scanf("%d", (arr+i));
    }
    
/*************** YOU MUST NOT MAKE CHANGES BEYOND THIS LINE! ***********/
	
	//Print original array
    printArr(arr, n, "Original");

	//Copy array with contents in reverse order
    arr_copy = arrCopy(arr, n);

	//Print new array
    printArr(arr_copy, n, "Copied");

    printf("\n");
    
    return 0;
}