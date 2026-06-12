#leia numero inteiro

addi $v0, $zero, 5
syscall
add $s1, $zero, $v0

#divide o numero por 3

addi $t0, $zero, 3
div $s1, $t0

#imprime quociente n/3

mflo $t1
addi $v0, $zero, 1
add $a0, $zero, $t1
syscall

#imprime resto n % 3

mfhi $t0
addi $v0, $zero, 1
add $a0, $zero, $t0
syscall


