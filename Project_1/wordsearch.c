#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;

// x and y will serve as our coordinate system to navigate our matrix
// x is initialized at -1 since we want it to work with our if statements, where any number involved will be larger than -1
int x = -1;

// y is initilized at 0 since we want to start at the first line in our search for the correct first letter
int y = 0;

// CAN BE A LOCAL VARIABLE
// Key is utilized to keep track of where we are in our word
int key = 0;

// Main function, DO NOT MODIFY 

// Main function to run our code, can't modify
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

// printPuzzle to print our char puzzle matrix
void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...

    // Double for loop to print our puzzle matrix
    for (int i = 0; i < bSize; i++){
		for (int j = 0; j < bSize; j++){
			printf("%c ", *(*(arr+i)+j));
		}
		printf("\n");
	}
	printf("\n");
    
}

// printAnswer to print our int answer matrix
void printAnswer(int** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...

    // Tell the user we found the word
    printf("Word Found!\n");

    // Tell the user we are printing the search path
    printf("Printing the search path: \n");

    // Double for loop to print out our search path matrix
    for (int i = 0; i < bSize; i++){
		for (int j = 0; j < bSize; j++){

            // Print out each index of our matrix
			printf("%d", *(*(arr+i)+j));

            // Set our space variable equal to our matrix
            int space = *(*(arr+i)+j);

            // Counter variable to count the number of spaces
            int counter = 0;

            // If the variable in our matrix is greater than 10 (aka its 24) 
            if (space >= 10){
                
                // We increase our counter variable while decrementing our copied array at that index
                while (space != 0){
                    space = space/10;
                    counter++;
                }

                // And account for spacing based on counter
                for (int r = 0; r < (7 - counter +1); r++){
                    printf(" ");
                }
            }

            // Otherwise we output 7 spaces
            else{
                printf("       ");
            }


		}
		printf("\n");
	}
	printf("\n");
    
}

// UpCase capitalizes our word
char* UpCase(char *letter){

    // Char pointer that goes over every letter in our word
    char *p;

    // Result array which we initialize to be the length of our word + null pointer
    char *result;
    result = (char*) malloc(strlen(letter)+1);

    // We copy our word into our result array
    strcpy(result, letter);

    // From the beginning to end of result we check every letter
    for (p = result; *p != '\0';p++){

        // If the letter is undercase (between a and z)
        if (*p >= 'a' && *p <= 'z'){

            // We turn it into an uppercase letter
            *p += 'A' - 'a';
        }
    }

    // And return our resulting word
    return result;
}

// WordFinder is our function to search for other letter in the array (its a recursive function that incorporates backtracing)
void wordFinder(char* word, char** arr, int** printable, int* x_coord, int* y_coord){

    // i and j variables for for loops
    int i;
    int j;

    // If we find the word we reach the end of our string
    if (*(word + key) == '\0'){
        // We tell the program to return
		return;
	}

    // Otherwise if we can't find the word at all...
    else if (key == 0){
        // We make the first index of printable -1 and return the program
		(*(*printable)) = -1;
		return;
	}

    // If neither of the statements were triggered we continue with wordFinder
    /* Essentially due to the way the pointers work in conjuction with the matrix... 
        Trying to access letters outside of our matrix will result in a segmentation fault
        For this reason we have come up with 3 scenarios to account for that
    */

    // Scenario 1: Top of the Puzzle
    if (*(y_coord + key - 1) == 0){

        /*  
            This will be explained here but remains true throughout all 3 scenarios:
            If our coordinate (x,y) has a non-negative number, its because we found that coordinate before.
            Therefore meaning we need to check again from where we last left off.
            Essentially we want to start our i at a different index based on our previous one.
        */ 
        if (*(y_coord + key) != -1){
			i = *(y_coord + key);
		}
        
        // Otherwise we will start at the same index as our current letter 
        else{
			i = *(y_coord + key - 1);
		}

        // i was set in our previous if-else statment, and it goes up until one line below our current letter
        for (i; i <= *(y_coord + key -1) + 1; i++){

            // We then check the immediate left and immediate right of our letter (Also utilized in all 3 statements)
            for (j = *(x_coord + key -1) -1; j <= *(x_coord + key - 1) +1; j++){

                /* 
				   The if statement is utilized throughout all 3 cases and will be explained once:
				   We essentially want to check the following three things:
				   1. If the current letter being looked at in the matrix equal to the current letter in our word array
                   2. Is the letter we are looking at NOT the same one we used to start looking? (ex: avoid looking at same letter as previous)
				   3. If the letter we are looking at NOT one we looked at before? (ex: "r" at coordinate 3,2)
				   
				   If all 3 are true, then we found our next letter.
                   Otherwise, we move on to our next Scenrio/Edgecase
				*/

                if ( *(*(arr + i) + j) == *(word + key) && !(*(x_coord + key) >= j && *(y_coord + key) >= i) && !(*(x_coord + key -1) == j && *(y_coord + key -1) == i)){

                    // Since we found our letter, we will move on to the next one
                    key++;

                    // If our printable array is empty at that coordinate
                    if (*(*(printable+i)+j) == 0){

                        // We set our printable equal to our key
                        *(*(printable + i) + j) = (key);
                    }

                    // Otherwise there is already a number at that coordinate...
                    else{

                        // We multiply our printable array at that index by 10, to move our value over by 1 to the left
                        *(*(printable + i) + j) = *(*(printable + i) + j) * 10;

                        // And then add our key in that coordinate
                        *(*(printable + i) + j) = *(*(printable + i) + j) + (key);

                        // Ex: 2*10 = 20 + 4 = 24
                    }

                    // We then update our x and y coordinates to our current coordinates
                    *(y_coord + key -1) = i;
                    *(x_coord + key -1) = j;

                    // We then recursively call the function once more with our now changed x and y coords to find the next letter
					wordFinder(word, arr, printable, x_coord, y_coord);

                    // And if this is where the first iteration of the function finds the word, lets end the function
					return;
                }
            }
        }
        // However, if the letter wasn't found...

        // We decrement our key variable
        key--;

        // Backtrace our printable array by dividing by 10 (ex: 24/10 = 2, and 2/10 = 0)
        *(*(printable + *(y_coord + key)) + *(x_coord + key)) = *(*(printable + *(y_coord + key)) + *(x_coord + key)) / 10;

        // Intended to reset our numbers that is 1 ahead of us to -1 since it dont want to store usless numbers (for the origin case)
        *(y_coord + key + 1) = -1;
		*(x_coord + key + 1) = -1;

        // And then search for the next letter by calling the function recursively again
		wordFinder(word, arr, printable, x_coord, y_coord);

        // And if this is where the first iteration of the function finds the word, lets end the function
		return;
    }

    // Scenario 2: Bottom of the Puzzle. 
    else if(*(y_coord + key -1) == bSize -1){

        // Explained in Scenario 1
        if (*(y_coord + key) != -1){
			i = *(y_coord + key);
		}

		else{
			i = *(y_coord + key - 1) -1;
		}

        // i was set in our previous if-else statment, and it goes up until our current letter
        for (i; i <= *(y_coord + key -1); i++){
            
            // Explained in Scenario 1
            for (j = *(x_coord + key -1) -1; j <= *(x_coord + key -1) +1; j++){

                // Explained in Scenario 1
                if ( *(*(arr + i) + j) == *(word + key) && !(*(x_coord + key) >= j && *(y_coord + key) >= i) && !(*(x_coord + key -1) == j && *(y_coord + key -1) == i)){
                    
                    // Since we found our letter, we will move on to the next one
                    key++;

                    // If our printable array is empty at that coordinate
                    if (*(*(printable+i)+j) == 0){

                        // We set our printable equal to our key
                        *(*(printable + i) + j) = (key);
                    }

                    // Otherwise
                    else{

                        // We multiply our printable array at that index by 10, to move our value over by 1 to the left
                        *(*(printable + i) + j) = *(*(printable + i) + j) * 10;

                        // And then add our key in that coordinate
                        *(*(printable + i) + j) = *(*(printable + i) + j) + (key);
                    }

                    // We then update our x and y coordinates to our current coordinates
                    *(y_coord + key -1) = i;
                    *(x_coord + key -1)= j;

                    // We then recursively call the function once more with our now changed x and y coords to find the next letter
					wordFinder(word, arr, printable, x_coord, y_coord);

                    // And if this is where the first iteration of the function finds the word, lets end the function
					return;
                }
            }

        }

        // However, if the letter wasn't found...

        // We decrement our key variable
        key--;

        // Backtrace our printable array
		*(*(printable + *(y_coord + key)) + *(x_coord + key)) = *(*(printable + *(y_coord + key)) + *(x_coord + key)) / 10;

        // Intended to reset our numbers that is 1 ahead of us to -1
		*(y_coord + key + 1) = -1;
		*(x_coord + key + 1) = -1;

        // We then recursively call the function once more with our now changed x and y coords to find the next letter
		wordFinder(word, arr, printable, x_coord, y_coord);

        // And if this is where the first iteration of the function finds the word, lets end the function
		return;
    }
        

    // Scenario 3: Middle of Puzzle
    else{
        
        // Explained in Scenario 1
        if (*(y_coord + key) != -1){
			i = *(y_coord + key);
		}

        // Otherwise we will start at the same index as our current letter 
		else{
			i = *(y_coord + key - 1) -1;
		}
		
        // i was set in our previous if-else statment, and it goes up until one line below our current letter
        for (i; i <= *(y_coord + key -1) +1; i++){

            // Explained in Scenario 1
            for (j = *(x_coord + key -1) -1; j <= *(x_coord + key -1) +1; j++){
                
                // Explained in Scenario 1
                if ( *(*(arr + i) + j) == *(word + key) && !(*(x_coord + key) >= j && *(y_coord + key) >= i) &&  !(*(x_coord + key -1) == j && *(y_coord + key -1) == i)){
                    
                    // Since we found our letter, we will move on to the next one
                    key++;

                    // If our printable array is empty at that coordinate
                    if (*(*(printable+i)+j) == 0){

                        // We set our printable equal to our key
                        *(*(printable + i) + j) = (key);
                    }

                    // Otherwise
                    else{

                        // We multiply our printable array at that index by 10, to move our value over by 1 to the left
                        *(*(printable + i) + j) = *(*(printable + i) + j) * 10;

                        // And then add our key in that coordinate
                        *(*(printable + i) + j) = *(*(printable + i) + j) + (key);
                    }

                    // We then update our x and y coordinates to our current coordinates
                    *(y_coord + key -1) = i;
                    *(x_coord + key -1) = j;

                    // We then recursively call the function once more with our now changed x and y coords to find the next letter
					wordFinder(word, arr, printable, x_coord, y_coord);

                    // And if this is where the first iteration of the function finds the word, lets end the function
					return;

                }
            }

        }
        // However, if the letter wasn't found...

        // We decrement our key variable
        key--;

        // Backtrace our printable array
		*(*(printable + *(y_coord + key)) + *(x_coord + key)) = *(*(printable + *(y_coord + key)) + *(x_coord + key)) / 10;

        // Intended to reset our numbers that is 1 ahead of us to -1
		*(y_coord + key + 1) = -1;
		*(x_coord + key + 1) = -1;

        // We then recursively call the function once more with our now changed x and y coords to find the next letter
		wordFinder(word, arr, printable, x_coord, y_coord);

        // And if this is where the first iteration of the function finds the word, lets end the function
		return;

    }

}

// searchPuzzle is our function to search our puzzle for a word
void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...

    // Capitalize the letters in our word
    word = UpCase(word);

    // Declare our i and j variables 
    int i;
    int j;

    // Intialize our Printable matrix which will be the same size as our puzzle matrix
    int **printable = (int**)malloc(bSize*sizeof(int*));
    
    // Fill our Printable matrix with 0's
    for (i = 0; i < bSize; i++){
        *(printable+i) = (int*)malloc(bSize*sizeof(int));
        for (j = 0; j < bSize; j++){
            *(*(printable+i)+j) = 0;
        }
    }

    // Size of the word
    int word_size = strlen(word);

    // Create our x and y coords as arrays to keep track of where we are for each letter
    int *x_coord = (int*)malloc(word_size*sizeof(int));
    int *y_coord = (int*)malloc(word_size*sizeof(int));

    // Initalize them to be -1, cause otherwise it causes a seg error later in the code
    for (i = 0; i < word_size; i++){
		*(x_coord + i) = -1;
		*(y_coord + i) = -1;
	}

    // We then search for the first letter of the word

    // i = y purely for recursive purposes
    // we want searchPuzzle to begin from this y, in other words our last "First letter of the word"
    for (i = y; i < bSize; i++){
        for (j = 0; j < bSize; j++){

            // If our word is equal to our current array index AND 
            // If our letter found is a different y and has a greater x than our previous letter we want to trigger our if statment
            if ( *(*(arr + i) + j) == *(word + key) && !(i == y && x >= j)){
                
                // Incrementing key will allow us to move on to the next letter
                key++;

                // Set that current counter equal to our printable matrix at that index
                *(*(printable + i) + j) = (key);

                // Set our global x and y equal to our i and j to store the location of our current "first letter"
                // We do this to avoid checking same first letter twice (if we use recursion)
                x = j;
                y = i;

                // Break the for loop
                break;
            }

        }

        // If our current index has a value we break out of the secondary for loop
        // Aka if we already found our first letter we want to stop looking for it   
        if (key != 0){
            break;
        }
    }

    // However if we couldn't find the first letter at all in our first run we know the word doesn't exist...
    if (key == 0){
        // So...we do the following:
        // Free our printable array
        for (int i = 0; i < bSize; i++){
			free(*(printable + i));
		}
        
        // Free our coordinate pairs
        free(x_coord);
        free(y_coord);

        // Tell the user the word cannot be found
        printf("Word not found!\n");

        // Return the function
        return;
    }

    // For the remaining letters we want our x_coord and y_coord to be equal to our global x and y coordinates
    *(x_coord) = x;
	*(y_coord) = y;
    
    // WordFinder Function
    // We call this to try to find the word
    // If it cant it'll set the first index of our printable matrix to -1, otherwise we will print out our printable matrix
    wordFinder(word, arr, printable, x_coord, y_coord);
    
    // If our printable array doesn't have -1 in its first index...(aka the word was found)
    if ((*(*printable)) != -1){

        // And to print our printable array
		printAnswer(printable);

        // We then free our printable array
        for (int i = 0; i < bSize; i++){
			free(*(printable + i));
		}

        // And free our x and y coord for when we navigate the array
		free(x_coord);
		free(y_coord);
    }
    else{

        // We then free our printable array
        for (int i = 0; i < bSize; i++){
			free(*(printable + i));
		}

        // And free our x and y coord for when we navigate the array
		free(x_coord);
		free(y_coord);

        // And we recursively search for the word again
        searchPuzzle(arr, word);
    }
    
}
