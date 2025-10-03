#!/bin/bash
# Script de teste inicial para validar todos os 8 algoritmos
# Compatível com arquivos gerados pelo gera-in-out.c (formato N.c.out, N.d.out, N.a.out)

echo "===== TESTE INICIAL DOS ALGORITMOS DE ORDENAÇÃO ====="
echo ""

# 1. Compilar o programa principal
echo "1. Compilando sortings.c..."
gcc -Wall -Wextra -pedantic -O2 -o sortings sortings.c -lm

if [ $? -ne 0 ]; then
    echo "❌ Erro na compilação! Verifique o código."
    exit 1
fi
echo "   ✓ Compilado com sucesso (sem warnings)"

# 2. Compilar o gerador de testes (se existir)
echo ""
echo "2. Compilando gera-in-out.c..."
if [ -f "gera-in-out.c" ]; then
    gcc -o gera-in-out gera-in-out.c
    if [ $? -ne 0 ]; then
        echo "❌ Erro na compilação do gerador!"
        exit 1
    fi
    echo "   ✓ Gerador compilado com sucesso"
else
    echo "   ⚠️  gera-in-out.c não encontrado - assumindo que arquivos já existem"
fi

# 3. Gerar arquivos de teste pequenos (se necessário)
echo ""
echo "3. Verificando/Gerando arquivos de teste (tamanho 10)..."

if [ -f "./gera-in-out" ]; then
    ./gera-in-out 10 c  # crescente
    ./gera-in-out 10 d  # decrescente  
    ./gera-in-out 10 a  # aleatório
    echo "   ✓ Arquivos 10.c, 10.d, 10.a e respectivos .out gerados"
else
    if [ -f "10.c" ] && [ -f "10.d" ] && [ -f "10.a" ] && 
       [ -f "10.c.out" ] && [ -f "10.d.out" ] && [ -f "10.a.out" ]; then
        echo "   ✓ Arquivos de teste já existem"
    else
        echo "   ❌ Arquivos de teste não encontrados e gerador indisponível"
        echo "       Certifique-se de ter: 10.c, 10.d, 10.a, 10.c.out, 10.d.out, 10.a.out"
        exit 1
    fi
fi

# 4. Testar cada algoritmo
echo ""
echo "4. Testando todos os 8 algoritmos..."
echo ""

NOMES_ALGORITMOS=(
    "Bubble Sort Original"
    "Bubble Sort Melhorado"
    "Insertion Sort"
    "Mergesort"
    "Quicksort (pivô último)"
    "Quicksort (pivô aleatório)"
    "Quicksort (mediana de 3)"
    "Heapsort"
)

TIPOS=("c" "d" "a")
TIPOS_NOMES=("Crescente" "Decrescente" "Aleatório")

TOTAL_TESTES=0
TESTES_OK=0

for i in {1..8}; do
    algoritmo_nome="${NOMES_ALGORITMOS[$((i-1))]}"
    echo "Algoritmo $i: $algoritmo_nome"
    
    for j in {0..2}; do
        tipo="${TIPOS[$j]}"
        tipo_nome="${TIPOS_NOMES[$j]}"
        arquivo_entrada="10.${tipo}"
        arquivo_saida_esperada="10.${tipo}.out"
        
        # Verificar se arquivos existem
        if [ ! -f "$arquivo_entrada" ]; then
            echo "   ❌ Arquivo de entrada $arquivo_entrada não existe!"
            continue
        fi
        
        if [ ! -f "$arquivo_saida_esperada" ]; then
            echo "   ❌ Arquivo de saída esperada $arquivo_saida_esperada não existe!"
            continue
        fi
        
        # Executar algoritmo
        tempo=$(./sortings $i "$arquivo_entrada" resultado_teste.bin 2>/dev/null)
        
        if [ $? -eq 0 ]; then
            # Verificar se resultado está correto
            if diff -q resultado_teste.bin "$arquivo_saida_esperada" > /dev/null 2>&1; then
                echo "   ✓ $tipo_nome: OK (${tempo}s)"
                TESTES_OK=$((TESTES_OK + 1))
            else
                echo "   ✗ $tipo_nome: ERRO - resultado incorreto"
            fi
        else
            echo "   ✗ $tipo_nome: ERRO - falha na execução"
        fi
        
        TOTAL_TESTES=$((TOTAL_TESTES + 1))
    done
    echo ""
done

# 5. Resultado final
echo "======================================================"
echo "RESULTADO DOS TESTES INICIAIS:"
echo "Total de testes: $TOTAL_TESTES"
echo "Sucessos: $TESTES_OK"
echo "Falhas: $((TOTAL_TESTES - TESTES_OK))"

if [ $TESTES_OK -eq $TOTAL_TESTES ]; then
    echo ""
    echo "🎉 TODOS OS TESTES PASSARAM!"
    echo "   O programa está funcionando corretamente."
    echo "   Você pode prosseguir para os testes completos."
    echo ""
    echo "Próximos passos:"
    echo "   ./gerar_entradas.sh    # Gerar todas as entradas"
    echo "   ./executar_testes.sh   # Executar bateria completa"
else
    echo ""
    echo "❌ ALGUNS TESTES FALHARAM!"
    echo "   Verifique os algoritmos com problemas antes de continuar."
    echo ""
    echo "Para debug individual:"
    echo "   ./sortings 4 10.a resultado_teste.bin"
    echo "   diff resultado_teste.bin 10.a.out"
fi

# Limpeza
rm -f resultado_teste.bin

echo ""
echo "===== FIM DOS TESTES INICIAIS ====="