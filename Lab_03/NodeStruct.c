
#include <stdio.h>
#include <stdlib.h>
// #include <malloc.h>

// Struct to create a Node
struct Node {
    int iValue;
    float fValue;
    struct Node *next;
};

int main() {
    // Initialize our variables
    struct Node *head = (struct Node*) malloc(sizeof(struct Node));
    head->iValue = 5;
    head->fValue = 3.14;

	// Print out addresses
    printf("%d \n", head->iValue); // Int value of head
    printf("%f \n", head->fValue); // Float value of head
    printf("%p \n", &(*head)); // Address of head
    printf("%p \n", &(head->iValue)); // Address of iValue
    printf("%p \n", &(head->fValue)); // Address of fValue
    printf("%p \n", &(head->next)); // Address of next
	
    
    // End Program
	return 0;
}