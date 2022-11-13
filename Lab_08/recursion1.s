.data

# User prompt
str1: .asciiz "Please enter an number: "

.text

# Main Function
main: 	addi $sp, $sp, -4	# Move stack pointer
	
	# Input prompt from user
	la $a0, str1
	addi $v0, $zero, 4
	syscall
	
	# Get user input
	addi $v0, $zero, 5
	syscall
	move $a0, $v0
	
	# Do recursion(x)	
	jal recursion
	
	# Print out our returned value
	move $a0, $v1
	move $v1, $v0
	addi $v0, $zero, 1
	syscall
	
	# End Program
	j end


# Implementing recursion
recursion: addi $sp, $sp, -12	# Push stack frame

	# Create space for register address and our variable m
	sw $ra, 8($sp)
	sw $a0, 4($sp)
	
	# See if m == 1. If not, go to not_minus_one 
	addi $t0, $zero, -1
	bne $t0, $a0, not_minus_one
	
	# If it is add 3 to our return output
	addi $v1, $v1, 3
	
	# Jump to end our recursion
	j end_recur
		
not_minus_one:
	# Make a temp register = -2
	addi $t1, $zero, -2
	
	# Check if userinput < -2. If it is go to lt_2
	slt $t2, $a0, $t1 
	bne $t2, $zero, lt_2
	
	# Otherwise check if userinput is = -2. If it is go to et_2
	beq $t1, $a0, et_2
	
	# Otherwise we go to redo
	j redo
	
	# Jump to end our recursion
	j end_recur		

lt_2: 	addi $v1, $v1, 2 # Add 2 to our return output
	
	# Jump to end our recursion
	j end_recur
	
et_2: 	addi $v1, $v1, 1 # Add 1 to our return output
	
	# Jump to end our recursion
	j end_recur

redo: 	sw $a0, 4($sp) # Save the value of m
	
	# Do (m - 3)
	addi $a0, $a0, -3
	
	# Call recursion(m - 3)
	jal recursion
	
	# Reload m
	lw $a0, 4($sp)

	# Do (m - 2)
	addi $a0, $a0, -2
	
	# Call recursion(m - 2)
	jal recursion
	
	# Reload m
	lw $a0, 4($sp) 
	
	# Add our other recursion values + m
	add $v1, $v1, $a0
	
	# Jump to end our recursion
	j end_recur
		

# End of recursion function	
end_recur: 
	# Load our register address value
	lw $ra, 8($sp)

	# Pop stack grame
	addi $sp, $sp, 12

	# Jump to the register address
	jr $ra

# End the program
end:	addi $sp, $sp, 4	
	li $v0, 10 
	syscall