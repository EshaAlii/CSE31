.data 

str1: .asciiz "Please enter a number: " #Ask user for a number
str2: .asciiz "Sum of even numbers is: " #Tell user the even sum
str3: .asciiz "Sum of odd numbers is: " #Tell user the odd sum
newline: .asciiz "\n" #print out a newline
evensum: .word 0 #make our evensum start at 0
oddsum:	.word 0 #make our oddsum start at 0

.text
main:	la $t4, evensum
	lw $t4, 0($t4)
	
	#Load our OddSum
	la $t5, oddsum
	lw $t5, 0($t5)
	
	#Jump to our while loop
	j While

While: 	li $v0, 4 #We ask the user for a number via string
	la $a0, str1 
	syscall
	
	#We get the user input
	li $v0, 5 
	syscall 
	
	#Move user input into register $t0
	move $t0, $v0
	
	beq $t0, $zero, End #when they finally enter zero we go to End
	
	#if our number is even...
	sll $t2, $t0, 31 
	beq $t2, $zero, Even #if true we go to Even

    	#if our number is odd
   	bne $t2, $zero, Odd #if false we go to Odd
   	
Even: 	add $t4, $t4, $t0 #calculate evensum
    	j While

Odd: 	add $t5, $t5, $t0 #calculate oddsum
    	j While

End: 	li $v0, 4 # print a new line
	la $a0, newline 
	syscall

	li $v0, 4 #print out evensum via string
	la $a0, str2 
	syscall
	
	#Put our evensum out
	addi $a0, $t4, 0
	li $v0, 1
	syscall		
	
	#We print out a newline
	li $v0, 4
	la $a0, newline 
	syscall

	#Print out our oddsum via string
	li $v0, 4 
	la $a0, str3
	syscall	

    #Put our oddsum out
    addi $a0, $t5, 0
	li $v0, 1
	syscall

	li $v0, 10 #End our program
	syscall	