#include <stdio.h>

int main() {   
    // Initialize our Variables
    int number; // User Entry for the program
    int count = 2; // Keeps track of the numbers so we can print them properly
    int temp; // Our temp variable
    int sum = 0; // The sum of our digits
    int last = 0; // Gets the last digit of our numbers
    float even_sum = 0; // The sum of our numbers with even digits
    float odd_sum = 0; // The sum of our numbers with odd digits
    int evenc = 0; // Keeps track of the amount of numbers with even digits
    int oddc = 0; // Keeps track of the amount of numbers with odd digits
    float even_avg; // The average of the numbers with even digits
    float odd_avg; // The average of the numbers with odd digits


    // We ask user for the first number
    printf("Enter the 1st number: ");
    scanf("%d", &number);

    // If the first number is 0, we'll immedietly say there isn't an average to compute
    if (number == 0){
        printf("There is no average to compute. \n");
    }

    // Otherwise...
    else{

        // While the number is not zero
        while (number != 0){

            // We assign temp = number so we don't change the value of our inputs
            temp = number;

            // Now while temp isn't zero...
            while (temp != 0){
                last = temp%10; // Use last to get the last digit of our number
                sum = last + sum; // We then add up the digits to our sum variable
                temp = temp/10; // And then we divide by ten to run the loop again, until no digits are left
            }

            // If the sum of our digits is even...
            if (sum%2 == 0){
                // We add it to our even sum and to increment our even counter...
                even_sum = number+even_sum;
                evenc++;
            }
            // But if the sum of our digits is odd...
            else{
                // We add it to our odd sum and to increment our odd counter...
                odd_sum = number+odd_sum;
                oddc++;
            }  

            // We then "reset" our sum value since we want to run it through the nested while loop as a cleared variable
            sum = 0; 

            // If the count is 2...
            if (count == 2){
                // We will ask the user for a second number and increment our counter...
                printf("Enter the 2nd number: ");
                scanf("%d", &number);
                count++;
            }

            // Else if the count is 3...
            else if (count == 3){
                // We will ask the user for a third number and increment our counter...
                printf("Enter the 3rd number: ");
                scanf("%d", &number);
                count++;
            }

            // Else if the count is greater than 3...
            else if (count > 3){
                // If the number has 11, 12, or 13 as its last digits or just any number that is 4 or greater, then we add "th" to it
                if (count%100 == 11 || count%100 == 12 || count%100 == 13 || count %10 == 4 ||count %10 == 5 || count %10 == 6 || count %10 == 7 || count %10 == 8 || count %10 == 9 || count %10 == 0 ){
                    printf("Enter the ");
                    printf("%d", count);
                    printf("th number: ");
                    scanf("%d", &number);
                    count++;
                }
                // Otherwise if the count has only 1 as its last digit we'll make it the "st" number
                else if(count%10 == 1){
                    printf("Enter the ");
                    printf("%d", count);
                    printf("st number: ");
                    scanf("%d", &number);
                    count++;
                }
                // Otherwise if the count has only 2 as its last digit we'll make it the "nd" number
                else if(count%10 == 2){
                    printf("Enter the ");
                    printf("%d", count);
                    printf("nd number: ");
                    scanf("%d", &number);
                    count++;
                }
                // Otherwise if the count has only 3 as its last digit we'll make it the "rd" number
                else if(count%10 == 3){
                    printf("Enter the ");
                    printf("%d", count);
                    printf("rd number: ");
                    scanf("%d", &number);
                    count++;
                }
            }
        }
    }
    
    // If evenc is greater than 0 (we at least have 1 number with an even sum of digits)
    if (evenc > 0){
        // We calculate and print our even average
        even_avg = even_sum/evenc;
        printf("Average of inputs whose digits sum up to an even number: %.2f \n", even_avg);
    }
    
    // If oddc is greater than 0 (we at least have 1 number with and odd sum of digits)
    if (oddc > 0){
        // We calculate and print our odd average
        odd_avg = odd_sum/oddc;
        printf("Average of inputs whose digits sum up to an odd number: %.2f \n", odd_avg);
    }
    
    // End program
    return 0;
}