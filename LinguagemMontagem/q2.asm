.data
    V: .space 40               # Alocando 10 inteiros (10 * 4 bytes) - Endereço base: 0x10010000
    espaco: .asciiz " "        # Fica no endereço 0x10010028 (40 em hexadecimal é 28)

.text
    # FASE 1 E 2: Dicionário e Preparo
    # Carregar endereço base de V (Truque dos 2 Passos)
    lui $s1, 0x1001
    ori $s1, $s1, 0x0000       # $s1 = Endereço Base de V

    # Ler n
    addi $v0, $zero, 5
    syscall
    add $s0, $zero, $v0        # $s0 = n

    # Laço para LEITURA via índices
    add $s6, $zero, $zero      # $s6 = i = 0

FOR_LEITURA_IDX:
    slt $t0, $s6, $s0          # Se i < n, $t0 = 1
    beq $t0, $zero, FIM_LEITURA_IDX

    # Cálculo do Índice: Endereço = Base + (i * 4)
    addi $t1, $zero, 4
    mul $t2, $s6, $t1          # $t2 = i * 4
    add $t3, $s1, $t2          # $t3 = Endereço temporário exato

    addi $v0, $zero, 5         # Lê valor
    syscall
    sw $v0, 0($t3)             # V[i] = valor

    addi $s6, $s6, 1           # i++
    j FOR_LEITURA_IDX
FIM_LEITURA_IDX:

    # FASE 3 E 4: Inicialização e Processamento
    add $s2, $zero, $zero      # $s2 = soma = 0
    add $s3, $zero, $zero      # $s3 = cont_par = 0
    add $s4, $zero, $zero      # $s4 = cont_impar = 0
    
    add $s6, $zero, $zero      # Resetando: i = 0

FOR_PROCESSA_IDX:
    slt $t0, $s6, $s0
    beq $t0, $zero, FIM_PROCESSA_IDX

    # Recalculando o deslocamento para leitura
    addi $t1, $zero, 4
    mul $t2, $s6, $t1
    add $t3, $s1, $t2

    lw $t4, 0($t3)             # $t4 = V[i]
    add $s2, $s2, $t4          # soma += V[i]

    # Lógica Par/Ímpar
    addi $t5, $zero, 2
    div $t4, $t5
    mfhi $t6                   # $t6 = V[i] % 2

    beq $t6, $zero, EH_PAR_IDX

EH_IMPAR_IDX:
    addi $s4, $s4, 1           # cont_impar++
    j PROX_PASSO_IDX

EH_PAR_IDX:
    addi $s3, $s3, 1           # cont_par++

PROX_PASSO_IDX:
    addi $s6, $s6, 1           # i++
    j FOR_PROCESSA_IDX

FIM_PROCESSA_IDX:
    # FASE 5: Impressão
    # Imprime Soma ($s2)
    addi $v0, $zero, 1
    add $a0, $zero, $s2
    syscall

    # Imprime Espaço (Carregando endereço 0x10010028)
    addi $v0, $zero, 4
    lui $a0, 0x1001
    ori $a0, $a0, 0x0028
    syscall

    # Imprime cont_impar ($s4)
    addi $v0, $zero, 1
    add $a0, $zero, $s4
    syscall

    # Imprime Espaço
    addi $v0, $zero, 4
    lui $a0, 0x1001
    ori $a0, $a0, 0x0028
    syscall

    # Imprime cont_par ($s3)
    addi $v0, $zero, 1
    add $a0, $zero, $s3
    syscall