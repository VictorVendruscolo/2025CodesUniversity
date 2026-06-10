# REGISTRADORES UTILIZADOS:
# $s0: Valor de 'n' (quantidade de elementos)
# $s1: Endereço base do Array V (Original)
# $s2: Endereço base do Array P (Pares)
# $s3: Endereço base do Array I (Ímpares)
# $s4: Contador do laço (i)
# $s5: Contador de elementos inseridos em P
# $s6: Contador de elementos inseridos em I


    # --- LEITURA DE N ---
    addi $v0, $zero, 5          # Carrega o código da syscall 5 (ler inteiro) [cite: 8]
    syscall                     # Chama o sistema para ler a entrada do teclado
    add $s0, $zero, $v0         # Move o valor lido de $v0 para $s0 (nosso 'n') [cite: 10]

    # --- ALOCAÇÃO DINÂMICA (SYSCALL 9) ---
    addi $t0, $zero, 4          # $t0 = 4 (tamanho de um inteiro em bytes) [cite: 3]
    mul $a0, $s0, $t0           # $a0 = n * 4 (calcula o total de bytes necessários) [cite: 3]

    addi $v0, $zero, 9          # Código da syscall 9 (sbrk - alocação de memória) [cite: 3]
    syscall                     # Aloca o Array V
    add $s1, $zero, $v0         # $s1 recebe o endereço inicial de V [cite: 3]

    addi $v0, $zero, 9          # Aloca o Array P
    syscall
    add $s2, $zero, $v0         # $s2 recebe o endereço inicial de P

    addi $v0, $zero, 9          # Aloca o Array I
    syscall
    add $s3, $zero, $v0         # $s3 recebe o endereço inicial de I

    # --- LEITURA DO ARRAY V ---
    add $s4, $zero, $zero       # Inicializa i = 0 ($s4) [cite: 3]
FOR_LEIA:
    slt $t0, $s4, $s0           # $t0 = 1 se i < n, senão 0 [cite: 3, 5]
    beq $t0, $zero, FIM_LEIA    # Se $t0 == 0, sai do laço [cite: 3]

    addi $v0, $zero, 5          # Syscall para ler cada elemento
    syscall
    
    addi $t1, $zero, 4          # $t1 = 4
    mul $t1, $s4, $t1           # Calcula o deslocamento: i * 4 [cite: 3]
    add $t1, $t1, $s1           # Soma o deslocamento ao endereço base de V
    sw $v0, 0($t1)              # Salva o valor lido na memória de V[i] [cite: 1, 3]
    
    addi $s4, $s4, 1            # Incrementa o índice: i++ [cite: 3]
    j FOR_LEIA                  # Volta para o início do laço
FIM_LEIA:

    # --- PROCESSAMENTO (SEPARAÇÃO) ---
    add $s4, $zero, $zero       # Reseta i = 0 para percorrer V
    add $s5, $zero, $zero       # Inicializa contador de Pares = 0
    add $s6, $zero, $zero       # Inicializa contador de Ímpares = 0
    addi $t7, $zero, 2          # $t7 = 2 (divisor para verificar paridade) [cite: 6]

FOR_SEPARA:
    slt $t0, $s4, $s0           # Verifica se i < n
    beq $t0, $zero, FIM_SEPARA

    # Carrega V[i] para testar
    addi $t1, $zero, 4
    mul $t1, $s4, $t1
    add $t1, $t1, $s1
    lw $t2, 0($t1)              # $t2 = V[i] 

    div $t2, $t7                # Divide V[i] por 2 [cite: 6]
    mfhi $t3                    # $t3 recebe o resto da divisão (HI) [cite: 6]

    beq $t3, $zero, SALVA_PAR   # Se resto for 0, pula para SALVA_PAR

SALVA_IMPAR:
    mul $t1, $s6, $t7           # $t7 já tem 2, mas para offset precisamos de 4. Usaremos $t4 abaixo.
    addi $t4, $zero, 4
    mul $t1, $s6, $t4           # Offset do Ímpar: contador_I * 4
    add $t1, $t1, $s3           # Endereço base de I + offset
    sw $t2, 0($t1)              # Salva valor em I
    addi $s6, $s6, 1            # Incrementa contador de Ímpares
    j PROXIMO

SALVA_PAR:
    addi $t4, $zero, 4
    mul $t1, $s5, $t4           # Offset do Par: contador_P * 4
    add $t1, $t1, $s2           # Endereço base de P + offset
    sw $t2, 0($t1)              # Salva valor em P
    addi $s5, $s5, 1            # Incrementa contador de Pares

PROXIMO:
    addi $s4, $s4, 1            # i++
    j FOR_SEPARA
FIM_SEPARA:

    # --- IMPRESSÃO DOS PARES ---
    add $s4, $zero, $zero       # Reseta i = 0
FOR_PRINT_P:
    slt $t0, $s4, $s5           # Condição: i < total_de_pares ($s5)
    beq $t0, $zero, FIM_P
    
    addi $t1, $zero, 4
    mul $t1, $s4, $t1
    add $t1, $t1, $s2
    lw $a0, 0($t1)              # Carrega P[i] em $a0 para imprimir [cite: 4, 8]
    addi $v0, $zero, 1          # Syscall imprimir inteiro [cite: 8]
    syscall
    
    addi $s4, $s4, 1
    j FOR_PRINT_P
FIM_P:

    # --- IMPRESSÃO DOS ÍMPARES ---
    add $s4, $zero, $zero
FOR_PRINT_I:
    slt $t0, $s4, $s6           # Condição: i < total_de_impares ($s6)
    beq $t0, $zero, FIM_I
    
    addi $t1, $zero, 4
    mul $t1, $s4, $t1
    add $t1, $t1, $s3
    lw $a0, 0($t1)              # Carrega I[i] em $a0
    addi $v0, $zero, 1
    syscall
    
    addi $s4, $s4, 1
    j FOR_PRINT_I
FIM_I:

    addi $v0, $zero, 10         # Encerra o programa
    syscall