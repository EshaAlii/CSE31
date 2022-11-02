#include <stdio.h>

int main() {

    // Initialize our variables
    int number; // Number of repititions
    int typo; // The repition we want our typo
    int i = 1; // Printer modifier

    // We ask user for the number of repitions
    printf("Enter the number of repetitions for the punishment phrase: ");
    scanf("%d", &number);

    // If number is less than or equal to 0, its invalid
    while (number <= 0){
        printf("You entered an invalid value for the number of repetitions!\n");
        printf("Enter the number of repetitions for the punishment phrase: ");
        scanf("%d", &number);
    }

    // We ask user for the typo
    printf("Enter the line where you wish to introduce the typo: ");
    scanf("%d", &typo);

    // If typo is less than or equal to 0 or greater than our number, its invalid
    while (typo <= 0 || typo > number){
        printf("You entered an invalid value for the typo placement\n");
        printf("Enter the line where you wish to introduce the typo: ");
        scanf("%d", &typo);
    }

    // We then print the statements and typo with a while loop
    while (i <= number){
        // If the modifier is equal to our typo, we print it out
        if (i == typo){
            printf("Cading in C is fun end intreseting!\n");
        }
        // Otherwise we print out our generic statement
        else{
            printf("Coding in C is fun and interesting!\n");
        }

        // And we iterate our modifier so our loop reaches an end
        i++;
    }

    // End Program
	return 0;
}