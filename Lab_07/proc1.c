#include <stdio.h>
#include <stdlib.h>

// Sum function
int Sum(int m, int n){
    // Create a sum variable
    int sum;

    // Set that equal to the sum of m + n
    sum = m + n;

    // Return our sum variable
    return sum;
}

// Driver Code
int main(){
    // m variable
    int m = 10;

    // n variable
    int n = 5;
    
    // Output statement
    printf("%d \n", Sum(m, n));

    // End Program
    return 0;
}