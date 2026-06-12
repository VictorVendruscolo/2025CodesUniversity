add $s0, $zero, $zero
addi $s1, $zero, 4
add $s3, $zero, $zero

INICIO:

	beq $s0, $s1, FIM
	
	addi $v0, $zero, 5
	syscall
	add $s2, $zero, $v0
	
	add $s3, $s3, $s2
	
	addi $s0, $s0, 1
	j INICIO
FIM:

	add $a0, $zero, $s3
	addi $v0, $zero, 1
	syscall