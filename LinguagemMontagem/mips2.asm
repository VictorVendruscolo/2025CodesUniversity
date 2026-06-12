.data
    espaco: .asciiz " "

.text
    # FASE 1 E 2: Preparo e Alocação
    # Ler n
    addi $v0, $zero, 5
    syscall
    add $s0, $zero, $v0        # $s0 = n

    # Alocar array V no Heap
    addi $v0, $zero, 9
    addi $t0, $zero, 4         # Tamanho de um inteiro (4 bytes)
    mul  $a0, $s0, $t0         # $a0 = n * 4
    syscall
    add $s1, $zero, $v0        # $s1 = Endereço Base de V

    # Laço para LEITURA dos n elementos
    add $s5, $zero, $s1        # $s5 = ptr (Ponteiro de leitura)
    add $s6, $zero, $zero      # $s6 = i (Contador de leitura)

FOR_LEITURA:
    slt $t0, $s6, $s0          # Se i < n, $t0 = 1
    beq $t0, $zero, FIM_LEITURA

    addi $v0, $zero, 5         # Lê um inteiro
    syscall
    sw $v0, 0($s5)             # Salva o inteiro lido na memória ( *ptr = valor )

    addi $s6, $s6, 1           # i++
    addi $s5, $s5, 4           # ptr++ (avança 4 bytes)
    j FOR_LEITURA
FIM_LEITURA:

    # FASE 3 E 4: Inicialização e Processamento
    add $s2, $zero, $zero      # $s2 = soma = 0
    add $s3, $zero, $zero      # $s3 = cont_par = 0
    add $s4, $zero, $zero      # $s4 = cont_impar = 0

    add $s5, $zero, $s1        # Resetando: ptr = V
    add $s6, $zero, $zero      # Resetando: i = 0

FOR_PROCESSA:
    slt $t0, $s6, $s0          # Se i < n, $t0 = 1
    beq $t0, $zero, FIM_PROCESSA

    lw $t1, 0($s5)             # Carrega o valor atual: $t1 = *ptr
    add $s2, $s2, $t1          # soma += *ptr

    # Lógica Par/Ímpar
    addi $t2, $zero, 2
    div $t1, $t2               # Divide *ptr por 2
    mfhi $t3                   # $t3 = resto da divisão

    beq $t3, $zero, EH_PAR     # Inversão lógica: se resto == 0, pula para PAR

EH_IMPAR:
    addi $s4, $s4, 1           # cont_impar++
    j PROX_PASSO               # Pula o incremento do par

EH_PAR:
    addi $s3, $s3, 1           # cont_par++

PROX_PASSO:
    addi $s6, $s6, 1           # i++
    addi $s5, $s5, 4           # ptr++ (avança 4 bytes)
    j FOR_PROCESSA

FIM_PROCESSA:
    # FASE 5: Encerramento (Imprimir Soma, Ímpar e Par separados por espaço)
    
    # Imprime Soma ($s2)
    addi $v0, $zero, 1
    add $a0, $zero, $s2
    syscall

    # Imprime Espaço
    addi $v0, $zero, 4
    lui $a0, 0x1001
    ori $a0, $a0, 0x0000       # offset 0 para a string " "
    syscall

    # Imprime cont_impar ($s4)
    addi $v0, $zero, 1
    add $a0, $zero, $s4
    syscall

    # Imprime Espaço
    addi $v0, $zero, 4
    lui $a0, 0x1001
    ori $a0, $a0, 0x0000
    syscall

    # Imprime cont_par ($s3)
    addi $v0, $zero, 1
    add $a0, $zero, $s3
    syscall