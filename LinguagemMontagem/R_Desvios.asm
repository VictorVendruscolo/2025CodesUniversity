#ler um número 

addi $v0, $zero, 5
syscall
add $s0, $zero, $v0

#se < 10, imprime 1
slti $t1, $s0, 10
beq $t1, $zero, FIM

addi $v0, $zero, 1
addi $a0, $zero, 1
syscall


#se >= 10 termina

FIM: