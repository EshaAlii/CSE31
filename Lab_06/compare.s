.data
n:      .word 25
str1: .asciiz "Less than\n"
str2: .asciiz "Less than or equal to\n" 
str3: .asciiz "Greater than\n"
str4: .asciiz "Greater than or equal to\n"
str5: .asciiz "Enter a number: \n"

.text

main: li $v0, 4 #code 4 == print string
	la $a0, str5 # $a0 == address of the string
	syscall #ask OS to preform this for us	
	
	li $v0, 5 #Ask for user input
	syscall #ask OS to do this for us
	
	move $t0, $v0 #Move user input into register $t0
	
	la $t3, n #load our n value into $t3
	lw $t3, 0($t3) #load out $t3
	
	slt $t4, $t0, $t3 #compare if user input is less than our n value aka if userinput < n
	bne $t4, $zero, LessThan #if true we go to LessThan
	
	slt $t6, $t3, $t0 #compare if user input is greater than our n value aka if userinput > n
	beq $t6, $zero, GreaterThanOrEq #checks if its equal to n as well
	
	slt $t7, $t0, $t3 #compare if user input is less than our n value aka if userinput < n
	beq $t7, $zero, LessThanOrEq #checks if its equal to n as well
	
	slt $t5, $t3, $t0 #compare if user input is greater than our n value aka if userinput > n
	bne $t5, $zero, GreaterThan #if true we go to GreaterThan
	
LessThan: li $v0, 4 #code 4 == print string
	la $a0, str1 # $a0 == address of the string
	syscall #ask OS to preform this for us	
	j End
	
GreaterThanOrEq: li $v0, 4 #code 4 == print string
	la $a0, str4 # $a0 == address of the string
	syscall #ask OS to preform this for us	
	j End
	
LessThanOrEq: li $v0, 4 #code 4 == print string
	la $a0, str2 # $a0 == address of the string
	syscall #ask OS to preform this for us	
	j End
	
	
 GreaterThan: li $v0, 4 #code 4 == print string
	la $a0, str3 # $a0 == address of the string
	syscall #ask OS to preform this for us
	j End
	
End: li $v0, 10 #End our program
	syscall	

	
