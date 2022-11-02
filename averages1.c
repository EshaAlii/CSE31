#include <stdio.h>

int main() {

    // Initialize our variables
    int number; // The user entered numbers placed in an array
    int temp;
    int count = 2; // We use this to properly print out anything past the 3rd entry
    int check; // We use this as a place holder to get the last digit of our number
    int sum = 0; // The sum of our digits
    float even_sum = 0; // The sum of even numbers
    float odd_sum = 0; // The sum of odd numbers
    float even_avg; // Our even average
    float odd_avg; // Our odd average
    int evenc = 0; // Keeps track of all the even digit sums
    int oddc = 0; // Keeps track of all the odd digit sums

    // We ask the user for the first number
    printf("Enter the 1st number: ");
    scanf("%d", &number);

    // If the first number is zero, we tell the user that there is no average to compute
    if (number == 0){
        printf("There is no average to compute.\n");
        return 0;
    }

    while (number != 0){

        // Set temp equal to number, since we don't want to actually manipulate our inputs
        temp = number;
        while(temp != 0){
            check = temp%10; // We use check as a place holder to get the last digit of our number
            sum = check+sum; // We then add the individual digit to an empty variable Sum
            temp = temp/10; // Then we divide by 10 and go through the entire loop again, until there are no digits left
        }

        // If the sum of our digits is even... 
        if (sum%2 == 0){
            // We store the number as part of an even sum and increment our even counter...
            even_sum = (even_sum+number);
            evenc++;
        }
        // Otherwise if it is odd...
        if (sum%2 == 1){
            // We store it as part of an odd sum and increment our odd counter...
            odd_sum = (odd_sum+number);
            oddc++;
        }

        sum = 0; // We reset our sum so it can be put through the while loop as a cleared variable once more

        // If the count is 2, we will print second number and increment our counter
        if (count == 2){
            printf("Enter the 2nd number: ");
            scanf("%d", &number);
            count++;
        }

        // Else if our count is 3, we will print our third number and increment our counter
        else if (count == 3){
            printf("Enter the 3rd number: ");
            scanf("%d", &number);
            count++;
        }

        // Else if its greater than 3...
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

        // If our even count is greater than 0 (we have numbers with sum of even digits)...
        if (evenc > 0){
            // We will calculate and print our even avg
            even_avg = even_sum/evenc;
            printf("The even avg is: %.2f \n", even_avg);
        }
        // And if our odd count is greater than 0 (we have numbers with sum of odd digits)...
        if (oddc > 0){
            // We will calculate and print our odd avg
            odd_avg = odd_sum/oddc;
            printf("The odd avg is: %.2f \n", odd_avg);
        }
   
    return 0;
}