#!/bin/bash
# Script para gerar todas as entradas necessárias para o trabalho
# Compatível com gera-in-out.c (gera arquivos N.c, N.d, N.a e N.c.out, N.d.out, N.a.out)

echo "===== GERAÇÃO DE ARQUIVOS DE ENTRADA E SAÍDA ====="
echo ""

# Verificar se o gerador existe
if [ ! -f "./gera-in-out" ]; then
    echo "Erro: gera-in-out não encontrado. Execute primeiro:"
    echo "   gcc -o gera-in-out gera-in-out.c"
    exit 1
fi

# Tamanhos para todos os algoritmos (1-8)
TAMANHOS_PEQUENOS=(10 100 1000 10000 100000)

# Tamanhos adicionais para algoritmos eficientes (4, 6, 7, 8)
TAMANHOS_GRANDES=(500000 5000000 50000000)

# Tipos: c (crescente), d (decrescente), a (aleatório)
TIPOS=(c d a)
TIPOS_NOMES=("Crescente" "Decrescente" "Aleatório")

echo "Arquivos que serão gerados:"
echo "• Entradas: N.c, N.d, N.a (onde N é o tamanho)"
echo "• Saídas esperadas: N.c.out, N.d.out, N.a.out"
echo ""

TOTAL_ARQUIVOS=0
ERRO_OCORREU=0

# Função para gerar um conjunto de arquivos
gerar_conjunto() {
    local tamanho=$1
    local descricao=$2
    
    echo "Gerando tamanho $tamanho ($descricao)..."
    
    # Calcular tamanho em MB
    local tamanho_mb=$(echo "scale=1; $tamanho * 4 / 1024 / 1024" | bc -l 2>/dev/null || echo "N/A")
    if [ "$tamanho_mb" != "N/A" ] && (( $(echo "$tamanho_mb > 10" | bc -l 2>/dev/null || echo 0) )); then
        echo "   Tamanho estimado: ${tamanho_mb} MB por arquivo"
    fi
    
    for i in {0..2}; do
        local tipo="${TIPOS[$i]}"
        local tipo_nome="${TIPOS_NOMES[$i]}"
        
        echo -n "   Gerando ${tamanho}.${tipo} (${tipo_nome})... "
        
        # Gerar arquivo
        ./gera-in-out $tamanho $tipo > /dev/null 2>&1
        
        if [ $? -eq 0 ]; then
            # Verificar se ambos os arquivos foram criados
            if [ -f "${tamanho}.${tipo}" ] && [ -f "${tamanho}.${tipo}.out" ]; then
                echo "✓"
                TOTAL_ARQUIVOS=$((TOTAL_ARQUIVOS + 2))
            else
                echo "❌ (arquivos não criados)"
                ERRO_OCORREU=1
            fi
        else
            echo "❌ (erro na execução)"
            ERRO_OCORREU=1
        fi
    done
    echo ""
}

# Gerar entradas pequenas
echo "FASE 1: Gerando entradas pequenas (todos os algoritmos: 1-8)"
echo "Tamanhos: ${TAMANHOS_PEQUENOS[*]}"
echo ""

for tamanho in "${TAMANHOS_PEQUENOS[@]}"; do
    gerar_conjunto $tamanho "para todos os algoritmos"
    
    # Parar se houver erro
    if [ $ERRO_OCORREU -eq 1 ]; then
        echo "Erro detectado. Interrompendo geração."
        exit 1
    fi
done

# Gerar entradas grandes
echo "FASE 2: Gerando entradas grandes (algoritmos eficientes: 4, 6, 7, 8)"
echo "Tamanhos: ${TAMANHOS_GRANDES[*]}"
echo ""

for tamanho in "${TAMANHOS_GRANDES[@]}"; do
    gerar_conjunto $tamanho "para algoritmos eficientes"
    
    # Parar se houver erro
    if [ $ERRO_OCORREU -eq 1 ]; then
        echo "Erro detectado. Interrompendo geração."
        exit 1
    fi
done

# Relatório final
echo "======================================================"
echo "GERAÇÃO CONCLUÍDA COM SUCESSO!"
echo ""

# Calcular estatísticas
PARES_PEQUENOS=$(( ${#TAMANHOS_PEQUENOS[@]} * 3 ))  # 5 * 3 = 15 pares
PARES_GRANDES=$(( ${#TAMANHOS_GRANDES[@]} * 3 ))    # 3 * 3 = 9 pares
PARES_TOTAL=$((PARES_PEQUENOS + PARES_GRANDES))     # 24 pares
ARQUIVOS_ESPERADOS=$((PARES_TOTAL * 2))              # 48 arquivos

echo "Resumo dos arquivos gerados:"
echo "• Entradas pequenas: ${PARES_PEQUENOS} pares de arquivos"
echo "• Entradas grandes: ${PARES_GRANDES} pares de arquivos"  
echo "• Total: ${PARES_TOTAL} pares = $TOTAL_ARQUIVOS arquivos"
echo ""

if [ $TOTAL_ARQUIVOS -eq $ARQUIVOS_ESPERADOS ]; then
    echo "✅ Todos os $ARQUIVOS_ESPERADOS arquivos foram gerados corretamente!"
else
    echo "⚠️  Esperado: $ARQUIVOS_ESPERADOS arquivos, Gerado: $TOTAL_ARQUIVOS"
fi

# Verificar espaço ocupado
echo ""
echo "Verificando espaço ocupado..."
ESPACO_TOTAL=$(du -sh *.c *.d *.a *.out 2>/dev/null | tail -1 | awk '{print $1}' 2>/dev/null || echo "N/A")

if [ "$ESPACO_TOTAL" != "N/A" ]; then
    echo "Espaço total ocupado: $ESPACO_TOTAL"
else
    echo "Espaço total ocupado: $(du -sh . | awk '{print $1}')"
fi

echo ""
echo "Estrutura dos arquivos gerados:"
echo "   NNN.c     = entrada crescente de NNN elementos"
echo "   NNN.d     = entrada decrescente de NNN elementos"  
echo "   NNN.a     = entrada aleatória de NNN elementos"
echo "   NNN.c.out = saída esperada para NNN.c (sempre ordenada)"
echo "   NNN.d.out = saída esperada para NNN.d (sempre ordenada)"
echo "   NNN.a.out = saída esperada para NNN.a (sempre ordenada)"
echo ""

# Exemplo de validação rápida
echo "Validação rápida (primeiros arquivos):"
ls -lh 10.* 2>/dev/null | head -8

echo ""
echo "Próximos passos:"
echo "   1. Verificar espaço em disco disponível"
echo "   2. Executar teste inicial: ./teste_inicial.sh"
echo "   3. Executar bateria completa: ./executar_testes.sh"
echo ""

echo "===== FIM DA GERAÇÃO ====="