addi $v0, $zero, 7
syscall
mov.d $f2, $f0

mul.d $f4, $f2, $f2

addi $v0, $zero, 3
mov.d $f12, $f4
syscall