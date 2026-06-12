addi $v0, $zero, 5
syscall
add $t0, $zero, $v0

addi $t1, $zero, 4
mult $t0, $t1
mflo $a0

addi $v0, $zero, 9
syscall 
add  $s0, $zero, $v0

addi $s1, $zero, 7
addi $s2, $zero, 14
sw $s1, 0($s0)
sw $s2, 4($s0)
