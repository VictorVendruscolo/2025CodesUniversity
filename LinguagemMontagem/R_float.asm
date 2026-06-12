addi $v0, $zero, 6
syscall
mov.s $f1, $f0

addi $v0, $zero, 6
syscall
mov.s $f2, $f0

add.s $f3, $f1, $f2

addi $v0, $zero, 2
mov.s $f12, $f3
syscall