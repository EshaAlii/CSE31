.data 

orig: .space 100	# In terms of bytes (25 elements * 4 bytes each)
sorted: .space 100

str0: .asciiz "Enter the number of assignments (between 1 and 25): "
str1: .asciiz "Enter score: "
str2: .asciiz "Original scores: "
str3: .asciiz "Sorted scores (in descending order): "
str4: .asciiz "Enter the number of (lowest) scores to drop: "
str5: .asciiz "Average (rounded down) with dropped scores removed: "
space: .asciiz " "
newline: .asciiz "\n"

.text 

# This is the main program.
# It first asks user to enter the number of assignments.
# It then asks user to input the scores, one at a time.
# It then calls selSort to perform selection sort.
# It then calls printArray twice to print out contents of the original and sorted scores.
# It then asks user to enter the number of (lowest) scores to drop.
# It then calls calcSum on the sorted array with the adjusted length (to account for dropped scores).
# It then prints out average score with the specified number of (lowest) scores dropped from the calculation.
main: 
	addi $sp, $sp -4
	sw $ra, 0($sp)
	li $v0, 4 
	la $a0, str0 
	syscall 
	li $v0, 5	# Read the number of scores from user
	syscall
	move $s0, $v0	# $s0 = numScores
	move $t0, $0
	la $s1, orig	# $s1 = orig
	la $s2, sorted	# $s2 = sorted
loop_in:
	li $v0, 4 
	la $a0, str1 
	syscall 
	sll $t1, $t0, 2
	add $t1, $t1, $s1
	li $v0, 5	# Read elements from user
	syscall
	sw $v0, 0($t1)
	addi $t0, $t0, 1
	bne $t0, $s0, loop_in
	
	move $a0, $s0
	jal selSort	# Call selSort to perform selection sort in original array
	
	li $v0, 4 
	la $a0, str2 
	syscall
	move $a0, $s1	# More efficient than la $a0, orig
	move $a1, $s0
	jal printArray	# Print original scores
	li $v0, 4 
	la $a0, str3 
	syscall 
	move $a0, $s2	# More efficient than la $a0, sorted
	jal printArray	# Print sorted scores
	
	li $v0, 4 
	la $a0, str4 
	syscall 
	li $v0, 5	# Read the number of (lowest) scores to drop
	syscall
	move $a1, $v0
	sub $a1, $s0, $a1	# numScores - drop
	move $a0, $s2	
	jal calcSum	# Call calcSum to RECURSIVELY compute the sum of scores that are not dropped
	
	# Your code here to compute average and print it
	
	# Print out the string that will
	la $a0, str5
	addi $v0, $zero, 4
	syscall
	
	# Check if a1 (our dropped number) == 0
	addi $t0, $t0, 0
	slt $t1, $a1, $t0
	beq $t1, $zero, Zero
	
	# Otherwise we will divide our added up array by our dropped scord 
	div $v1, $a1
	mflo $a0
	
	# And print out the resulting value
	addi $v0, $zero, 1
	syscall
	
	# We will then end the program
	j EndProgram
	
	# If it is print out 0
	Zero:	add $a0, $zero, $zero
		addi $v0, $zero, 1
		syscall
	
	# We will then end the program
	EndProgram:
		lw $ra, 0($sp)
		addi $sp, $sp, 4
		li $v0, 10
		syscall
		
	
# printList takes in an array and its size as arguments. 
# It prints all the elements in one line with a newline at the end.
printArray:
	# Your implementation of printList here	
	
	addi $sp, $sp, -8 #incorporate space into our stack
	sw $a0, 0($sp)		
	
	addi $t0, $zero, 0 # set our counter to 0 (for the for loop)
	add $t1, $zero, $a0 # set our index to 0
	
	printArrayLoop:
		addi $v0, $zero, 1 # print each individual array index
		lw $a0, 0($t1) 	# load each value of the array into a temp register
		syscall
		
		la $a0, space # print out our space between each index
		addi $v0, $zero, 4
		syscall
		
		addi $t1, $t1, 4 # increment our indexing (done by 4 bytes)
		addi $t0, $t0, 1 # increment our counter (done by 1 number)
	
		bne $t0, $a1, printArrayLoop # if value != size we keep going
		
		la $a0, newline # print out a newline for our array 
		syscall
		
		lw $a0 0($sp) # restore stack pointer
		addi $sp, $sp, 4
		jr $ra # jump back
	
# selSort takes in the number of scores as argument. 
# It performs SELECTION sort in descending order and populates the sorted array
selSort:
	# Your implementation of selSort here
	
	add $t0, $s1, $zero # save first number of orig array in temp
	add $t1, $s2, $zero # save first number of sort array in temp
	
	add $t2, $zero, $zero # i variable
	
	ForArray:
		beq $t2, $a0, SortArr # for i = 0 to length
		
		lw $t4, 0($t0) # load our orig array
		sw $t4, 0($t1) # save that orig array into sorted array
		
		addi $t0, $t0, 4 # we then increment our orig array
		addi $t1, $t1, 4 # we then increment our sorted array
		
		addi $t2, $t2, 1 # i++
		
		j ForArray #continue loop
		
	SortArr:
		addi $t5, $a0, -1 # size - 1
		add $t2, $zero, $zero # i variable
		
		Outer:
			
			beq $t2, $t5, Finish # for i = 0 to length - 1
			
			addi $t4, $t2, 0 # maxIndex = i
			
			addi $t3, $t2, 0 # j = i
			
			Inner:
				addi $t3, $t3, 1 # j = i + 1 / j++
				
				beq $t3, $a0, OuterTwo # for j = i + 1 to length
				
				# sorted[j] address
				addi $t1, $zero, 4 
				mult $t3, $t1
				mflo $t1
				add $t1, $t1, $s2
				
				# sorted[maxIndex] address
				addi $t0, $zero, 4
				mult $t4, $t0
				mflo $t0
				add $t0, $t0, $s2
				
				lw $t1, 0($t1) #sorted[j] value
				lw $t0, 0($t0) # sorted[maxIndex] value
				
				slt $t0, $t0, $t1 # If sorted[j] > sorted[maxIndex]
				beq $t0, $zero, Inner # Jump to Inner and rerun the loop
				
				add $t4, $t3, $zero  # set Maxindex = j
				
				
				j Inner # Jump back to the inner loop
				
		OuterTwo:
			# sorted[i] address
			addi $t1, $zero, 4
			mult $t2, $t1
			mflo $t1
			add $t1, $t1, $s2
		
			# sorted[maxIndex] address
			addi $t0, $zero, 4
			mult $t4, $t0
			mflo $t0
			add $t0, $t0, $s2	
			
			# load temp registers = sorted[MaxIndex] and sorted[i]
			lw $t6, 0($t0) 
			lw $t7, 0($t1) 
			
			# save temp registers = sorted[MaxIndex] and sorted[i]
			sw $t7, 0($t0) # temp = sorted[MaxIndex]
			sw $t6, 0($t1) # sorted[MaxIndex] = sorted[i]
			
			# sorted[i] = temp
			addi $t2, $t2, 1

			# Then rerun the outer loop until it reaches length-1
			j Outer
	
	Finish:
	
	# Jump back to main program
	jr $ra
	
	
# calcSum takes in an array and its size as arguments.
# It RECURSIVELY computes and returns the sum of elements in the array.
# Note: you MUST NOT use iterative approach in this function.
calcSum:
	# Your implementation of calcSum here
	# a1 = dropped length
	# a0 = address of sorted
	
	# Account for space on the stack + save dropped length + save register address
	addi $sp, $sp, -8
	sw $ra, 4($sp)
	sw $a1, 0($sp)
	
	# Call on calcSum2
	jal calcSum2
	
	# Restore register address + dropped length
	lw $ra, 4($sp)
	lw $a1, 0($sp)
	
	# Jump back to main program
	jr $ra
	
	calcSum2:
		# Account for space on stack + save register address
		addi $sp, $sp, -4
		sw $ra, 0($sp)
		
		slt $t0, $zero, $a1 # if a1 < zero
		bne $t0, $zero, Recursive # if t0 = 0 go to recursive
	
		EndRecur:
			# Restore register address + stack
			lw $ra, 0($sp)
			addi $sp, $sp, 4
			
			# Jump back to main program
			jr $ra
	
	
		Recursive:
			# Account for space on stack + save dropped length 
			addi $sp, $sp, -4
			sw $a1, 0($sp)
			
			# dropped length - 1
			addi $a1, $a1, -1
			
			# Recursively call calcSum2 or calcSum(arr, len-1)
			jal calcSum2
			
			# Restore length and stack
			lw $a1, 0($sp)
			addi $sp, $sp, 4
			
			# dropped length - 1
			addi $a1, $a1, -1
		
			# sorted [len-1]
			addi $t0, $zero, 4
			mult $a1, $t0
			mflo $a1
			add $a1, $a1, $s2
		
			# We load current value of a1 into a1
			lw $a1, 0($a1)
			
			# We then save that value into v1 (our totalsum variable) and add onto it while we do recursion
			add $v1, $v1, $a1
			
			# End the recursion
			j EndRecur
		
