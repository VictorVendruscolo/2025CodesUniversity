# RELATÓRIO DE ANÁLISE - ALGORITMOS DE ORDENAÇÃO
# Disciplina: Algoritmos e Estruturas de Dados II
# Prof. Fabrício Sérgio de Paula - UEMS
# 
# Este script analisa os resultados dos testes de performance dos 8 algoritmos

# Carregar bibliotecas necessárias
# Instalar todos os pacotes necessários de uma vez

library(ggplot2)
library(dplyr)
library(readr)
library(scales)
# Ler os dados
dados <- read_csv("resultados_testes.csv")

# Visualizar estrutura dos dados
str(dados)
summary(dados)

# ========== ANÁLISE 1: COMPARAÇÃO GERAL ==========

# Gráfico 1: Tempo vs Tamanho por Algoritmo
p1 <- ggplot(dados, aes(x = Tamanho, y = Tempo_Segundos, color = Nome_Algoritmo)) +
  geom_line(size = 1) +
  geom_point(size = 2) +
  scale_x_log10(labels = comma_format()) +
  scale_y_log10() +
  labs(title = "Tempo de Execução vs Tamanho da Entrada",
       subtitle = "Comparação dos 8 Algoritmos de Ordenação",
       x = "Tamanho da Entrada (log)", 
       y = "Tempo (segundos, log)",
       color = "Algoritmo") +
  theme_minimal() +
  theme(legend.position = "bottom")

print(p1)

# ========== ANÁLISE 2: ALGORITMOS O(n²) vs O(n log n) ==========

# Separar algoritmos por complexidade
dados_bubble_insertion <- dados %>% 
  filter(Algoritmo %in% c(1, 2, 3)) %>%
  filter(Tamanho <= 100000)  # Apenas tamanhos menores

dados_eficientes <- dados %>% 
  filter(Algoritmo %in% c(4, 6, 7, 8))

# Gráfico 2: Algoritmos O(n²)
p2 <- ggplot(dados_bubble_insertion, aes(x = Tamanho, y = Tempo_Segundos, color = Nome_Algoritmo)) +
  geom_line(size = 1) +
  geom_point(size = 2) +
  facet_wrap(~Tipo_Entrada, labeller = as_labeller(c("a" = "Aleatório", "c" = "Crescente", "d" = "Decrescente"))) +
  scale_x_continuous(labels = comma_format()) +
  labs(title = "Algoritmos O(n²): Bubble Sort e Insertion Sort",
       x = "Tamanho da Entrada", 
       y = "Tempo (segundos)",
       color = "Algoritmo") +
  theme_minimal()

print(p2)

# Gráfico 3: Algoritmos O(n log n)
p3 <- ggplot(dados_eficientes, aes(x = Tamanho, y = Tempo_Segundos, color = Nome_Algoritmo)) +
  geom_line(size = 1) +
  geom_point(size = 2) +
  facet_wrap(~Tipo_Entrada, labeller = as_labeller(c("a" = "Aleatório", "c" = "Crescente", "d" = "Decrescente"))) +
  scale_x_log10(labels = comma_format()) +
  scale_y_log10() +
  labs(title = "Algoritmos O(n log n): Mergesort, Quicksort e Heapsort",
       x = "Tamanho da Entrada (log)", 
       y = "Tempo (segundos, log)",
       color = "Algoritmo") +
  theme_minimal()

print(p3)

# ========== ANÁLISE 3: IMPACTO DO TIPO DE ENTRADA ==========

# Gráfico 4: Comparação por tipo de entrada
p4 <- ggplot(dados, aes(x = Tamanho, y = Tempo_Segundos, color = Tipo_Entrada)) +
  geom_line(size = 1) +
  facet_wrap(~Nome_Algoritmo, scales = "free_y") +
  scale_x_log10(labels = comma_format()) +
  scale_y_log10() +
  labs(title = "Impacto do Tipo de Entrada nos Algoritmos",
       x = "Tamanho da Entrada (log)", 
       y = "Tempo (segundos, log)",
       color = "Tipo Entrada") +
  scale_color_manual(values = c("a" = "red", "c" = "green", "d" = "blue"),
                     labels = c("a" = "Aleatório", "c" = "Crescente", "d" = "Decrescente")) +
  theme_minimal()

print(p4)

# ========== ANÁLISE 4: TABELAS COMPARATIVAS ==========

# Tabela 1: Melhores tempos por tamanho
melhores_por_tamanho <- dados %>%
  group_by(Tamanho, Tipo_Entrada) %>%
  slice_min(Tempo_Segundos) %>%
  select(Tamanho, Tipo_Entrada, Nome_Algoritmo, Tempo_Segundos)

print("MELHORES ALGORITMOS POR TAMANHO:")
print(melhores_por_tamanho)

# Tabela 2: Comparação Quicksort (3 variantes)
quicksort_compare <- dados %>%
  filter(Algoritmo %in% c(5, 6, 7)) %>%
  group_by(Nome_Algoritmo, Tamanho, Tipo_Entrada) %>%
  summarise(Tempo_Medio = mean(Tempo_Segundos), .groups = 'drop')

print("COMPARAÇÃO ENTRE VARIANTES DO QUICKSORT:")
print(quicksort_compare)

# ========== ANÁLISE 5: ESCALABILIDADE ==========

# Calcular razão de crescimento
dados_crescimento <- dados %>%
  arrange(Nome_Algoritmo, Tipo_Entrada, Tamanho) %>%
  group_by(Nome_Algoritmo, Tipo_Entrada) %>%
  mutate(Razao_Crescimento = Tempo_Segundos / lag(Tempo_Segundos)) %>%
  filter(!is.na(Razao_Crescimento))

# Gráfico 5: Razão de crescimento
p5 <- ggplot(dados_crescimento, aes(x = Tamanho, y = Razao_Crescimento, color = Nome_Algoritmo)) +
  geom_line(size = 1) +
  facet_wrap(~Tipo_Entrada, labeller = as_labeller(c("a" = "Aleatório", "c" = "Crescente", "d" = "Decrescente"))) +
  scale_x_log10(labels = comma_format()) +
  labs(title = "Taxa de Crescimento do Tempo de Execução",
       subtitle = "Razão entre tempos consecutivos",
       x = "Tamanho da Entrada (log)", 
       y = "Razão de Crescimento",
       color = "Algoritmo") +
  theme_minimal()

print(p5)

# ========== ESTATÍSTICAS DESCRITIVAS ==========

# Resumo estatístico por algoritmo
resumo_estatistico <- dados %>%
  group_by(Nome_Algoritmo) %>%
  summarise(
    Tempo_Min = min(Tempo_Segundos),
    Tempo_Max = max(Tempo_Segundos),
    Tempo_Medio = mean(Tempo_Segundos),
    Tempo_Mediano = median(Tempo_Segundos),
    Desvio_Padrao = sd(Tempo_Segundos),
    .groups = 'drop'
  )

print("RESUMO ESTATÍSTICO POR ALGORITMO:")
print(resumo_estatistico)

# ========== SALVAR GRÁFICOS ==========

# Salvar todos os gráficos em alta resolução
ggsave("grafico1_comparacao_geral.png", p1, width = 12, height = 8, dpi = 300)
ggsave("grafico2_algoritmos_quadraticos.png", p2, width = 12, height = 8, dpi = 300)
ggsave("grafico3_algoritmos_eficientes.png", p3, width = 12, height = 8, dpi = 300)
ggsave("grafico4_impacto_entrada.png", p4, width = 15, height = 10, dpi = 300)
ggsave("grafico5_escalabilidade.png", p5, width = 12, height = 8, dpi = 300)

# Salvar tabelas em CSV
write_csv(melhores_por_tamanho, "melhores_por_tamanho.csv")
write_csv(quicksort_compare, "comparacao_quicksort.csv")
write_csv(resumo_estatistico, "resumo_estatistico.csv")

cat("========================================\n")
cat("ANÁLISE CONCLUÍDA COM SUCESSO!\n")
cat("========================================\n")
cat("Gráficos salvos:\n")
cat("- grafico1_comparacao_geral.png\n")
cat("- grafico2_algoritmos_quadraticos.png\n") 
cat("- grafico3_algoritmos_eficientes.png\n")
cat("- grafico4_impacto_entrada.png\n")
cat("- grafico5_escalabilidade.png\n")
cat("\nTabelas salvas:\n")
cat("- melhores_por_tamanho.csv\n")
cat("- comparacao_quicksort.csv\n")
cat("- resumo_estatistico.csv\n")
cat("\nUtilize estes materiais no seu relatório acadêmico!\n")