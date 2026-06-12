.data
    espaco: .asciiz " "

.text
    # FASE 1 E 2: Dicionário e Alocação Dinâmica
    # Ler n
    addi $v0, $zero, 5
    syscall
    add $s0, $zero, $v0        # $s0 = n

    # Alocar array V no Heap
    addi $v0, $zero, 9
    addi $t0, $zero, 4
    mul  $a0, $s0, $t0         # n * 4 bytes
    syscall
    add $s1, $zero, $v0        # $s1 = Endereço base de V

    # Laço para LEITURA (O "leia V")
    add $s4, $zero, $s1        # ptr = V
    add $s3, $zero, $zero      # i = 0
FOR_LEITURA_B:
    slt $t0, $s3, $s0
    beq $t0, $zero, FIM_LEITURA_B
    addi $v0, $zero, 5
    syscall
    sw $v0, 0($s4)             # *ptr = valor lido
    addi $s3, $s3, 1           # i++
    addi $s4, $s4, 4           # ptr++
    j FOR_LEITURA_B
FIM_LEITURA_B:

    # FASE 3 E 4: Máquina de Repetição e Miolo do Bubble Sort
    add $s2, $zero, $zero      # Inicializa laço externo: j = 0

FOR_J:
    slt $t0, $s2, $s0          # j < n
    beq $t0, $zero, FIM_FOR_J

    # Inicializa laço interno
    add $s4, $zero, $s1        # ptr = V
    add $s3, $zero, $zero      # i = 0

    # Lógica preventiva: limite do laço interno = n - 1
    addi $t7, $s0, -1

FOR_I:
    slt $t0, $s3, $t7          # i < n - 1
    beq $t0, $zero, FIM_FOR_I

    # Miolo: if (*ptr > *(ptr+1))
    lw $t1, 0($s4)             # $t1 = *ptr (Atual)
    lw $t2, 4($s4)             # $t2 = *(ptr+1) (Próximo)

    # Inversão para Branch: Se próximo < atual, significa atual > próximo (trocamos!)
    # Então testamos o contrário: se NÃO for menor, ou seja, estão em ordem, pulamos a troca.
    slt $t3, $t2, $t1          # $t3 = 1 se ($t2 < $t1) -> Ocorre a troca!
    beq $t3, $zero, PULA_TROCA

    # Swap (A mágica do cruzamento de registradores, sem variável 'aux'!)
    sw $t2, 0($s4)             # Salva o próximo na posição atual
    sw $t1, 4($s4)             # Salva o atual na posição da frente

PULA_TROCA:
    addi $s3, $s3, 1           # i++
    addi $s4, $s4, 4           # ptr++ (avança endereço 4 bytes)
    j FOR_I
    
FIM_FOR_I:
    addi $s2, $s2, 1           # j++
    j FOR_J
FIM_FOR_J:

    # FASE 5: Impressão do Array Ordenado
    add $s4, $zero, $s1        # ptr = V
    add $s3, $zero, $zero      # i = 0
FOR_PRINT:
    slt $t0, $s3, $s0
    beq $t0, $zero, FIM_PRINT

    # Imprime número atual
    lw $a0, 0($s4)
    addi $v0, $zero, 1
    syscall

    # Imprime Espaço
    addi $v0, $zero, 4
    lui $a0, 0x1001
    ori $a0, $a0, 0x0000
    syscall

    addi $s3, $s3, 1           # i++
    addi $s4, $s4, 4           # ptr++
    j FOR_PRINT
FIM_PRINT: