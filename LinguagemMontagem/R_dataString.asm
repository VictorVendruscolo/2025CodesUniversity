.data
	.asciiz "MIPS\n" 
.text

	lui $t1, 0x1001
	ori $t1, $t1, 0x0000
	add $a0, $zero, $t1
	addi $v0, $zero, 4
	syscall