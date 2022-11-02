		.data
x:		.word 5
y:		.word 10
m:		.word 15
b:		.word 2

		.text
MAIN:	la $t0, x
		lw $s0, 0($t0)		# s0 = x
		la $t0, y
		lw $s1, 0($t0)		# s1 = y
		
		# Prepare to call sum(x)
		add $a0, $zero, $s0	# Set a0 as input argument for SUM
		jal SUM
		add $t0, $s1, $s0
		add $s1, $t0, $v0
		addi $a0, $s1, 0 
		li $v0, 1		 
		syscall	
		j END

		
SUM: addi $sp, $sp -8	#account for space on stack
		sw $ra, 4($sp)		# Save ra as stack pointer
		sw $s0, 0($sp)          # Save s0 as stack pointer
		la $t0, m		# load m
		lw $s0, 0($t0)		# save s0 = m
		sw $a0, 12($sp)		# save a0
		add $a0, $s0, $a0	# Update a0 as new argument for SUB
		jal SUB			# Call SUB
		lw $a0, 12($sp)		# restore a0
		lw $s0, 0($sp)		# restore m
		add $v0, $a0, $v0	# add v0 + a0 + SUB
		lw $ra, 4($sp)		# restore our return address
		addi $sp, $sp 8		# restore stack
		jr $ra			# jump back to main
		
SUB:	la $t0, b
		addi $sp, $sp -4
		sw $s0, 0($sp)		# Backup s0 from SUM
		lw $s0, 0($t0)		# s0 = b
		sub $v0, $a0, $s0
		lw $s0, 0($sp)		# Restore s0 from SUM
		addi $sp, $sp 4
		jr $ra

		
END:
