#!/bin/bash
# Coleta informações do sistema para o relatório

ARQUIVO="info_sistema.txt"

echo "===== COLETANDO INFORMAÇÕES DO SISTEMA ====="
echo "Salvando em: $ARQUIVO"
echo ""

# Limpar arquivo
> $ARQUIVO

echo "=========================================" >> $ARQUIVO
echo "INFORMAÇÕES DO SISTEMA - TRABALHO AEDII" >> $ARQUIVO  
echo "Prof. Fabrício Sérgio de Paula - UEMS" >> $ARQUIVO
echo "=========================================" >> $ARQUIVO
echo "" >> $ARQUIVO

echo "Data/Hora: $(date)" >> $ARQUIVO
echo "" >> $ARQUIVO

echo "Sistema Operacional:" >> $ARQUIVO
echo "$(lsb_release -d 2>/dev/null | cut -f2 || cat /etc/os-release | head -1)" >> $ARQUIVO
echo "Kernel: $(uname -r)" >> $ARQUIVO
echo "Arquitetura: $(uname -m)" >> $ARQUIVO
echo "" >> $ARQUIVO

echo "Processador:" >> $ARQUIVO
echo "$(lscpu | grep 'Model name' | cut -d':' -f2 | xargs)" >> $ARQUIVO
echo "Núcleos: $(nproc)" >> $ARQUIVO
echo "Frequência: $(lscpu | grep 'CPU MHz' | cut -d':' -f2 | xargs) MHz" >> $ARQUIVO
echo "" >> $ARQUIVO

echo "Memória:" >> $ARQUIVO
echo "RAM Total: $(free -h | grep 'Mem:' | awk '{print $2}')" >> $ARQUIVO
echo "RAM Disponível: $(free -h | grep 'Mem:' | awk '{print $7}')" >> $ARQUIVO
echo "" >> $ARQUIVO

echo "Compilador:" >> $ARQUIVO
echo "$(gcc --version | head -1)" >> $ARQUIVO
echo "" >> $ARQUIVO

echo "Arquivos de teste:" >> $ARQUIVO
if [ -f "resultados_testes.csv" ]; then
    echo "Resultados: $(wc -l < resultados_testes.csv) linhas" >> $ARQUIVO
    echo "Data dos testes: $(stat -c %y resultados_testes.csv | cut -d'.' -f1)" >> $ARQUIVO
else
    echo "Resultados: ainda não executados" >> $ARQUIVO
fi
echo "" >> $ARQUIVO

echo "=========================================" >> $ARQUIVO

echo "✓ Informações coletadas em: $ARQUIVO"
echo ""
echo "Para o relatório em R, use essas informações junto com resultados_testes.csv"