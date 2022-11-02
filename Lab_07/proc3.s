.data
x: .word 1
y: .word 2
z: .word 3
str1: .asciiz "p + q: "		# Tell user the sum of p and q
newline: .asciiz "\n"		# Create  a newline

.text

MAIN:	la $t0, x		# load address of x
	lw $s0, 0($t0)		# save x into s0
	la $t0, y		# load address of y
	lw $s1, 0($t0)		# save y into s1
	la $t0, z		# load address of z
	lw $s2, 0($t0)		# save z into s2
	
	add $a0, $zero, $s0	# Set a0 as input argument for FOO
	add $a1, $zero, $s1	# Set a1 as input argument for FOO
	add $a2, $zero, $s2	# Set a2 as input argument for FOO
	jal FOO
	
	add $s2, $s1, $s0    	# z = y + x
    	add $s2, $s2, $s2     	# z = z + z
    	add $a0, $s2, $v1    	# z = z + foo(x,y,z)
    	
    	addi $v0, $zero, 1	# print out our result
        syscall	

	j END
	
	
FOO:	addi $sp, $sp -36 	# account for space on stack
	sw $ra, 4($sp)		# save ra as stack pointer
	sw $s0, 12($sp)		# save s0 as stack pointer
	sw $s1, 16($sp)		# save s1 as stack pointer
	sw $s2, 20($sp)		# save s2 as stack pointer
	
	sw $a0, 24($sp)		# save a0
	sw $a1, 28($sp)		# save a1
	sw $a2, 32($sp)		# save a2
	
	add $a0, $s0, $s2	# input arguments for BAR pt 1
	add $a1, $s1, $s2	
	add $a2, $s0, $s1	
	
	jal BAR			# go to BAR
	
	lw $s0, 0($t0)		# s0 = temp reg
	add $t0, $v0, $zero	# p = BAR
	
	lw $s0, 12($sp)		#restore s0
	
	sub $a0, $s0, $s2	# input arguments for BAR pt 2
	sub $a1, $s1, $s0	
	add $a2, $s1, $s1	
	
	jal BAR			# go to BAR
	
	add $s1, $v0, $zero	# q = BAR
	add $v0, $t0, $s1	# p+q
	add $v1, $v0, $zero	# Store p+q into v1
	
	li $v0, 4 		#print out our string "p+q"
	la $a0, str1
	syscall
	
	li $v0, 1		# print out p+q
   	move $a0, $v1
    	syscall
    
	li $v0, 4 		#print out our string
	la $a0, newline
	syscall
	
	lw $s1, 16($sp)		# restore our s1
	lw $ra, 4($sp)		# restore our return address
	addi $sp, $sp 36	# restore stack
	jr $ra			# jump back to MAIN
	
BAR: 	sub $v0, $a1, $a0	# b - a
	sllv $v0, $v0, $a2	# sllv c
	jr $ra

END:	li $v0, 10 #End our program
	syscall		
