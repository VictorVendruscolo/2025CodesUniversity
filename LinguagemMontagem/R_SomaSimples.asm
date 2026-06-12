#ler dois números inteiros do usuário -> syscall 5

addi $v0, $zero, 5
syscall 
add $s0, $zero, $v0

addi $v0, $zero, 5
syscall 
add $s1, $zero, $v0

#somar os dois números 

add $t0, $s1, $s0

#imprimir a soma -> syscall 1


addi $v0, $zero, 1
add $a0, $zero, $t0 
syscall

#feedback: 
	#problemas com syscall de print integer -> help
	#problema com variável que guarda leitura integer -> help
	