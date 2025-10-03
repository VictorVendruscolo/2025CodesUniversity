#!/bin/bash
# Script de execução completa dos testes - OTIMIZADO PARA PRATICIDADE
# Gera arquivo resultados_testes.csv com todos os tempos

echo "===== BATERIA COMPLETA DE TESTES ====="

# Arquivo de saída
RESULTADO="resultados_testes.csv"
echo "Algoritmo,Nome_Algoritmo,Tamanho,Tipo_Entrada,Tempo_Segundos" > $RESULTADO

# Nomes dos algoritmos
NOMES=(
    "Bubble_Original"
    "Bubble_Melhorado" 
    "Insertion_Sort"
    "Mergesort"
    "Quicksort_Ultimo"
    "Quicksort_Aleatorio"
    "Quicksort_Mediana3"
    "Heapsort"
)

# Tamanhos e algoritmos
TAMANHOS_PEQUENOS=(10 100 1000 10000 100000)
TAMANHOS_GRANDES=(500000 5000000 50000000)
TIPOS=(c d a)

TOTAL_TESTES=156  # 5*3*8 + 3*3*4 = 120+36
EXECUTADOS=0

echo "Total de testes: $TOTAL_TESTES"
echo "Executando..."
echo ""

# Função para mostrar progresso
progresso() {
    local atual=$1
    local total=$2
    local pct=$((atual * 100 / total))
    printf "\rProgresso: %d%% (%d/%d)" $pct $atual $total
}

# Função de teste otimizada
testar() {
    local alg=$1
    local nome=$2
    local tamanho=$3
    local tipo=$4
    
    local entrada="${tamanho}.${tipo}"
    local saida_esperada="${tamanho}.${tipo}.out"
    
    if [ ! -f "$entrada" ] || [ ! -f "$saida_esperada" ]; then
        echo "ERRO: Arquivos $entrada ou $saida_esperada não existem!"
        return 1
    fi
    
    # Executar 3 vezes e pegar mediana
    local tempos=()
    for i in {1..3}; do
        local tempo=$(./sortings $alg "$entrada" temp.bin 2>/dev/null)
        if [ $? -eq 0 ]; then
            tempos+=($tempo)
        else
            echo "ERRO na execução do algoritmo $alg com $entrada"
            return 1
        fi
    done
    
    # Verificar resultado
    if diff -q temp.bin "$saida_esperada" > /dev/null; then
        # Calcular mediana
        IFS=$'\n' sorted=($(sort -n <<<"${tempos[*]}"))
        local tempo_final=${sorted[1]}
        
        # Salvar resultado
        echo "$alg,$nome,$tamanho,$tipo,$tempo_final" >> $RESULTADO
        return 0
    else
        echo "ERRO: Resultado incorreto para algoritmo $alg com $entrada"
        return 1
    fi
}

# TESTES PEQUENOS (todos algoritmos)
echo "FASE 1: Entradas pequenas (algoritmos 1-8)"
for tamanho in "${TAMANHOS_PEQUENOS[@]}"; do
    for tipo in "${TIPOS[@]}"; do
        for alg in {1..8}; do
            nome="${NOMES[$((alg-1))]}"
            
            if testar $alg $nome $tamanho $tipo; then
                EXECUTADOS=$((EXECUTADOS + 1))
                progresso $EXECUTADOS $TOTAL_TESTES
            else
                echo ""
                echo "FALHA no teste: Algoritmo $alg, Tamanho $tamanho, Tipo $tipo"
                exit 1
            fi
        done
    done
done

echo ""
echo ""
echo "FASE 2: Entradas grandes (algoritmos 4,6,7,8)"

# TESTES GRANDES (apenas algoritmos eficientes)
ALGORITMOS_GRANDES=(4 6 7 8)
for tamanho in "${TAMANHOS_GRANDES[@]}"; do
    for tipo in "${TIPOS[@]}"; do
        for alg in "${ALGORITMOS_GRANDES[@]}"; do
            nome="${NOMES[$((alg-1))]}"
            
            echo ""
            echo "Executando: $nome com ${tamanho}.${tipo} (pode demorar...)"
            
            if testar $alg $nome $tamanho $tipo; then
                EXECUTADOS=$((EXECUTADOS + 1))
                progresso $EXECUTADOS $TOTAL_TESTES
            else
                echo ""
                echo "FALHA no teste: Algoritmo $alg, Tamanho $tamanho, Tipo $tipo"
                exit 1
            fi
        done
    done
done

# Limpeza e resultado final
rm -f temp.bin

echo ""
echo ""
echo "======================================================"
echo "🎉 TODOS OS TESTES CONCLUÍDOS COM SUCESSO!"
echo "======================================================"
echo ""
echo "Resultados salvos em: $RESULTADO"
echo "Total de linhas: $(wc -l < $RESULTADO)"
echo "Testes executados: $EXECUTADOS/$TOTAL_TESTES"
echo ""

# Estatísticas rápidas
echo "Próximos passos:"
echo "   1. Verificar resultados: head -10 $RESULTADO"
echo "   2. Coletar info do sistema: ./info_sistema.sh"  
echo "   3. Desenvolver relatório em R"
echo ""
echo "===== BATERIA COMPLETA FINALIZADA ====="