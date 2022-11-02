#include <stdio.h> 
 
int main() { 
    int x, y, *px, *py; 
    int arr[10] = {1,2,3,4,5,6,7,8,9,10}; 
    
    x = 11;
    y = 12;

    // Print the values of x, y, and arr[0]
    printf("x: %d \n", x);
    printf("y: %d \n", y);
    printf("arr[0]: %d \n", arr[0]);

    // Print the addresses of x and y
    printf("Address of x: %p \n", &x);
    printf("Address of y: %p \n", &y);

    // Making px and py point to x and y instead.
    px = &x;
    py = &y;

    // Print out the value of px and py
    printf("Value of px: %p \n", px);
    printf("Value of py: %p \n", py);

    // Print out the Address of px and py
    printf("Address of px: %p \n", &px);
    printf("Address of py: %p \n", &py);

    // Outputting contents of the array as a pointer
    printf("The array has the following numbers:");
    for (int i = 0; i < 10; i++){
        printf(" %d", *(arr+i));
    }
    printf("\n");

    // Outputting the first element's address of an array
    printf("This is arr[0]'s address: %p \n", &arr[0]);
    printf("This is also arr[0]'s address: %p \n", arr);

    return 0; 
} 