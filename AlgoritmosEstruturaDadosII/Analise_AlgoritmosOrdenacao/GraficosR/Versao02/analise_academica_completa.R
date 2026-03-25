# =============================================================================
# ANÁLISE COMPLETA DOS ALGORITMOS DE ORDENAÇÃO - QUALIDADE ACADÊMICA
# Disciplina: Algoritmos e Estruturas de Dados II
# Prof. Fabrício Sérgio de Paula - UEMS
# =============================================================================
install.packages(c("RColorBrewer", "gridExtra", "ggthemes", "viridis", "tidyr"))
# Carregar bibliotecas (instalar se necessário)
required_packages <- c("ggplot2", "dplyr", "readr", "scales", "RColorBrewer", 
                      "gridExtra", "ggthemes", "viridis", "knitr", "kableExtra", "tidyr")

for(pkg in required_packages) {
  if(!require(pkg, character.only = TRUE)) {
    install.packages(pkg)
    library(pkg, character.only = TRUE)
  }
}

# Configuração de tema acadêmico personalizado
theme_academic <- theme_minimal() +
  theme(
    plot.title = element_text(size = 14, face = "bold", hjust = 0.5),
    plot.subtitle = element_text(size = 11, hjust = 0.5, color = "gray30"),
    axis.title = element_text(size = 12, face = "bold"),
    axis.text = element_text(size = 10),
    legend.title = element_text(size = 11, face = "bold"),
    legend.text = element_text(size = 10),
    strip.text = element_text(size = 10, face = "bold"),
    panel.grid.minor = element_blank(),
    panel.grid.major = element_line(color = "gray90", size = 0.3),
    plot.background = element_rect(fill = "white", color = NA),
    panel.background = element_rect(fill = "white", color = NA)
  )

# Paleta de cores acadêmica
cores_algoritmos <- c("#1f77b4", "#ff7f0e", "#2ca02c", "#d62728", 
                     "#9467bd", "#8c564b", "#e377c2", "#7f7f7f")

# =============================================================================
# CARREGAMENTO E PREPARAÇÃO DOS DADOS
# =============================================================================

cat("Carregando dados...\n")
dados <- read_csv("resultados_testes.csv")

# Adicionar informações categóricas e de complexidade
dados <- dados %>%
  mutate(
    Complexidade = case_when(
      Algoritmo %in% c(1, 2, 3) ~ "O(n²)",
      Algoritmo %in% c(4, 6, 7, 8) ~ "O(n log n)",
      Algoritmo == 5 ~ "O(n log n) / O(n²)"
    ),
    Categoria = case_when(
      Algoritmo %in% c(1, 2) ~ "Bubble Sort",
      Algoritmo == 3 ~ "Insertion Sort",
      Algoritmo == 4 ~ "Mergesort", 
      Algoritmo %in% c(5, 6, 7) ~ "Quicksort",
      Algoritmo == 8 ~ "Heapsort"
    ),
    Tipo_Entrada_Nome = case_when(
      Tipo_Entrada == "a" ~ "Aleatório",
      Tipo_Entrada == "c" ~ "Crescente", 
      Tipo_Entrada == "d" ~ "Decrescente"
    ),
    Nome_Limpo = case_when(
      Nome_Algoritmo == "Bubble_Original" ~ "Bubble Original",
      Nome_Algoritmo == "Bubble_Melhorado" ~ "Bubble Melhorado",
      Nome_Algoritmo == "Insertion_Sort" ~ "Insertion Sort",
      Nome_Algoritmo == "Mergesort" ~ "Mergesort",
      Nome_Algoritmo == "Quicksort_Ultimo" ~ "Quick (último)",
      Nome_Algoritmo == "Quicksort_Aleatorio" ~ "Quick (aleatório)",
      Nome_Algoritmo == "Quicksort_Mediana3" ~ "Quick (mediana)",
      Nome_Algoritmo == "Heapsort" ~ "Heapsort"
    )
  )

cat("Dados carregados:", nrow(dados), "observações\n")
cat("Resumo dos dados:\n")
print(summary(dados))

# =============================================================================
# GRÁFICO 1: VISÃO GERAL COMPARATIVA - TODOS OS ALGORITMOS
# =============================================================================

cat("\nGerando Gráfico 1: Visão Geral Comparativa...\n")

g1 <- ggplot(dados, aes(x = Tamanho, y = Tempo_Segundos, color = Nome_Limpo)) +
  geom_line(size = 1.2, alpha = 0.8) +
  geom_point(size = 2, alpha = 0.9) +
  scale_x_log10(
    breaks = c(10, 100, 1000, 10000, 100000, 500000, 5000000, 50000000),
    labels = c("10", "100", "1K", "10K", "100K", "500K", "5M", "50M")
  ) +
  scale_y_log10(
    breaks = scales::trans_breaks("log10", function(x) 10^x),
    labels = scales::trans_format("log10", scales::math_format(10^.x))
  ) +
  scale_color_manual(values = cores_algoritmos) +
  facet_wrap(~Tipo_Entrada_Nome, scales = "free_y") +
  labs(
    title = "Comparação de Performance: Todos os Algoritmos de Ordenação",
    subtitle = "Tempo de execução vs. tamanho da entrada (escala logarítmica)",
    x = "Tamanho da Entrada (elementos)",
    y = "Tempo de Execução (segundos)",
    color = "Algoritmo"
  ) +
  theme_academic +
  theme(legend.position = "bottom") +
  guides(color = guide_legend(nrow = 2, byrow = TRUE))

ggsave("01_visao_geral_comparativa.png", g1, width = 14, height = 10, dpi = 300)

# =============================================================================
# GRÁFICO 2: ALGORITMOS O(n²) - ANÁLISE DETALHADA
# =============================================================================

cat("Gerando Gráfico 2: Algoritmos O(n²)...\n")

dados_quadraticos <- dados %>% filter(Algoritmo %in% c(1, 2, 3), Tamanho <= 100000)

g2 <- ggplot(dados_quadraticos, aes(x = Tamanho, y = Tempo_Segundos, color = Nome_Limpo)) +
  geom_line(size = 1.3, alpha = 0.9) +
  geom_point(size = 2.5, alpha = 0.9) +
  scale_x_continuous(
    breaks = c(10, 100, 1000, 10000, 100000),
    labels = c("10", "100", "1K", "10K", "100K")
  ) +
  scale_y_continuous(labels = scales::number_format(accuracy = 0.001, suffix = "s")) +
  scale_color_manual(values = c("#d62728", "#ff7f0e", "#2ca02c")) +
  facet_wrap(~Tipo_Entrada_Nome, scales = "free_y") +
  labs(
    title = "Algoritmos O(n²): Bubble Sort e Insertion Sort",
    subtitle = "Comparação detalhada de performance para entradas pequenas e médias",
    x = "Tamanho da Entrada (elementos)",
    y = "Tempo de Execução (segundos)",
    color = "Algoritmo"
  ) +
  theme_academic +
  theme(legend.position = "bottom")

ggsave("02_algoritmos_quadraticos.png", g2, width = 12, height = 8, dpi = 300)

# =============================================================================
# GRÁFICO 3: ALGORITMOS O(n log n) - ANÁLISE DETALHADA
# =============================================================================

cat("Gerando Gráfico 3: Algoritmos O(n log n)...\n")

dados_eficientes <- dados %>% filter(Algoritmo %in% c(4, 6, 7, 8))

g3 <- ggplot(dados_eficientes, aes(x = Tamanho, y = Tempo_Segundos, color = Nome_Limpo)) +
  geom_line(size = 1.3, alpha = 0.9) +
  geom_point(size = 2.5, alpha = 0.9) +
  scale_x_log10(
    breaks = c(10, 100, 1000, 10000, 100000, 500000, 5000000, 50000000),
    labels = c("10", "100", "1K", "10K", "100K", "500K", "5M", "50M")
  ) +
  scale_y_log10() +
  scale_color_manual(values = c("#1f77b4", "#9467bd", "#8c564b", "#7f7f7f")) +
  facet_wrap(~Tipo_Entrada_Nome, scales = "free_y") +
  labs(
    title = "Algoritmos O(n log n): Mergesort, Quicksort e Heapsort",
    subtitle = "Performance para todos os tamanhos de entrada (escala logarítmica)",
    x = "Tamanho da Entrada (elementos)",
    y = "Tempo de Execução (segundos)",
    color = "Algoritmo"
  ) +
  theme_academic +
  theme(legend.position = "bottom")

ggsave("03_algoritmos_eficientes.png", g3, width = 12, height = 8, dpi = 300)

# =============================================================================
# GRÁFICO 4: ANÁLISE POR COMPLEXIDADE TEÓRICA
# =============================================================================

cat("Gerando Gráfico 4: Análise por Complexidade...\n")

g4 <- ggplot(dados, aes(x = Tamanho, y = Tempo_Segundos, color = Complexidade)) +
  geom_point(size = 1.5, alpha = 0.7) +
  geom_smooth(method = "loess", se = TRUE, size = 1.2) +
  scale_x_log10(
    breaks = c(10, 100, 1000, 10000, 100000, 500000, 5000000, 50000000),
    labels = c("10", "100", "1K", "10K", "100K", "500K", "5M", "50M")
  ) +
  scale_y_log10() +
  scale_color_manual(values = c("#d62728", "#2ca02c", "#1f77b4")) +
  facet_wrap(~Tipo_Entrada_Nome) +
  labs(
    title = "Classificação por Complexidade Assintótica",
    subtitle = "Tendências de crescimento dos algoritmos (com intervalos de confiança)",
    x = "Tamanho da Entrada (elementos)",
    y = "Tempo de Execução (segundos)",
    color = "Complexidade"
  ) +
  theme_academic +
  theme(legend.position = "bottom")

ggsave("04_complexidade_assintotica.png", g4, width = 12, height = 8, dpi = 300)

# =============================================================================
# GRÁFICO 5: QUICKSORT - COMPARAÇÃO DAS TRÊS VARIANTES
# =============================================================================

cat("Gerando Gráfico 5: Variantes do Quicksort...\n")

dados_quicksort <- dados %>% filter(Algoritmo %in% c(5, 6, 7))

g5 <- ggplot(dados_quicksort, aes(x = Tamanho, y = Tempo_Segundos, color = Nome_Limpo)) +
  geom_line(size = 1.5, alpha = 0.9) +
  geom_point(size = 3, alpha = 0.9) +
  scale_x_log10(
    breaks = c(10, 100, 1000, 10000, 100000, 500000, 5000000, 50000000),
    labels = c("10", "100", "1K", "10K", "100K", "500K", "5M", "50M")
  ) +
  scale_y_log10() +
  scale_color_manual(values = c("#ff7f0e", "#9467bd", "#8c564b")) +
  facet_wrap(~Tipo_Entrada_Nome, scales = "free_y") +
  labs(
    title = "Quicksort: Comparação das Estratégias de Escolha de Pivô",
    subtitle = "Impacto da escolha do pivô na performance do algoritmo",
    x = "Tamanho da Entrada (elementos)",
    y = "Tempo de Execução (segundos)",
    color = "Variante"
  ) +
  theme_academic +
  theme(legend.position = "bottom")

ggsave("05_quicksort_variantes.png", g5, width = 12, height = 8, dpi = 300)

# =============================================================================
# GRÁFICO 6: BUBBLE SORT - ORIGINAL vs MELHORADO
# =============================================================================

cat("Gerando Gráfico 6: Bubble Sort Original vs Melhorado...\n")

dados_bubble <- dados %>% filter(Algoritmo %in% c(1, 2))

g6 <- ggplot(dados_bubble, aes(x = Tamanho, y = Tempo_Segundos, color = Nome_Limpo, linetype = Nome_Limpo)) +
  geom_line(size = 1.5, alpha = 0.9) +
  geom_point(size = 3, alpha = 0.9) +
  scale_x_continuous(
    breaks = c(10, 100, 1000, 10000, 100000),
    labels = c("10", "100", "1K", "10K", "100K")
  ) +
  scale_y_continuous(labels = scales::number_format(accuracy = 0.001, suffix = "s")) +
  scale_color_manual(values = c("#d62728", "#ff7f0e")) +
  scale_linetype_manual(values = c("solid", "dashed")) +
  facet_wrap(~Tipo_Entrada_Nome, scales = "free_y") +
  labs(
    title = "Bubble Sort: Impacto das Otimizações",
    subtitle = "Comparação entre a versão original e a versão melhorada",
    x = "Tamanho da Entrada (elementos)",
    y = "Tempo de Execução (segundos)",
    color = "Versão",
    linetype = "Versão"
  ) +
  theme_academic +
  theme(legend.position = "bottom")

ggsave("06_bubble_original_vs_melhorado.png", g6, width = 12, height = 8, dpi = 300)

# =============================================================================
# GRÁFICO 7: HEATMAP DE PERFORMANCE
# =============================================================================

cat("Gerando Gráfico 7: Heatmap de Performance...\n")

# Preparar dados para heatmap
heatmap_data <- dados %>%
  select(Nome_Limpo, Tamanho, Tipo_Entrada_Nome, Tempo_Segundos) %>%
  mutate(Log_Tempo = log10(Tempo_Segundos + 1e-10)) %>%
  group_by(Nome_Limpo, Tamanho) %>%
  summarise(Tempo_Medio = mean(Log_Tempo), .groups = 'drop')

g7 <- ggplot(heatmap_data, aes(x = factor(Tamanho), y = Nome_Limpo, fill = Tempo_Medio)) +
  geom_tile(color = "white", size = 0.5) +
  scale_fill_viridis_c(name = "Log₁₀(Tempo)", option = "plasma", direction = -1) +
  scale_x_discrete(
    labels = c("10", "100", "1K", "10K", "100K", "500K", "5M", "50M")
  ) +
  labs(
    title = "Mapa de Calor: Performance dos Algoritmos",
    subtitle = "Tempo médio de execução por tamanho de entrada (escala logarítmica)",
    x = "Tamanho da Entrada",
    y = "Algoritmo"
  ) +
  theme_academic +
  theme(
    axis.text.x = element_text(angle = 45, hjust = 1),
    panel.grid = element_blank()
  )

ggsave("07_heatmap_performance.png", g7, width = 12, height = 8, dpi = 300)

# =============================================================================
# GRÁFICO 8: SENSIBILIDADE AO TIPO DE ENTRADA
# =============================================================================

cat("Gerando Gráfico 8: Sensibilidade ao Tipo de Entrada...\n")

# Calcular razões de performance
sens_data <- dados %>%
  group_by(Nome_Limpo, Tamanho) %>%
  summarise(
    Crescente = Tempo_Segundos[Tipo_Entrada == "c"],
    Decrescente = Tempo_Segundos[Tipo_Entrada == "d"],
    Aleatorio = Tempo_Segundos[Tipo_Entrada == "a"],
    .groups = 'drop'
  ) %>%
  mutate(
    Razao_DC = Decrescente / Crescente,
    Razao_AC = Aleatorio / Crescente,
    Razao_DA = Decrescente / Aleatorio
  )

# Reformatar para plotting
sens_long <- sens_data %>%
  select(Nome_Limpo, Tamanho, Razao_DC, Razao_AC) %>%
  pivot_longer(cols = c(Razao_DC, Razao_AC), 
               names_to = "Comparacao", values_to = "Razao") %>%
  mutate(
    Comparacao = case_when(
      Comparacao == "Razao_DC" ~ "Decrescente / Crescente",
      Comparacao == "Razao_AC" ~ "Aleatório / Crescente"
    )
  )

g8 <- ggplot(sens_long, aes(x = Tamanho, y = Razao, color = Nome_Limpo)) +
  geom_line(size = 1.2, alpha = 0.8) +
  geom_point(size = 2.5, alpha = 0.9) +
  geom_hline(yintercept = 1, linetype = "dashed", color = "gray50", size = 1) +
  scale_x_log10(
    breaks = c(10, 100, 1000, 10000, 100000, 500000, 5000000, 50000000),
    labels = c("10", "100", "1K", "10K", "100K", "500K", "5M", "50M")
  ) +
  scale_y_continuous(breaks = seq(0, 10, 0.5)) +
  scale_color_manual(values = cores_algoritmos) +
  facet_wrap(~Comparacao, scales = "free_y") +
  labs(
    title = "Sensibilidade dos Algoritmos ao Tipo de Entrada",
    subtitle = "Razões de tempo de execução (linha tracejada = performance igual)",
    x = "Tamanho da Entrada (elementos)",
    y = "Razão de Tempo de Execução",
    color = "Algoritmo"
  ) +
  theme_academic +
  theme(legend.position = "bottom") +
  guides(color = guide_legend(nrow = 2, byrow = TRUE))

ggsave("08_sensibilidade_entrada.png", g8, width = 14, height = 8, dpi = 300)

# =============================================================================
# GRÁFICO 9: ESCALABILIDADE - TAXA DE CRESCIMENTO
# =============================================================================

cat("Gerando Gráfico 9: Taxa de Crescimento...\n")

crescimento_data <- dados %>%
  arrange(Nome_Limpo, Tipo_Entrada, Tamanho) %>%
  group_by(Nome_Limpo, Tipo_Entrada_Nome) %>%
  mutate(
    Taxa_Crescimento = Tempo_Segundos / lag(Tempo_Segundos),
    Fator_Tamanho = Tamanho / lag(Tamanho)
  ) %>%
  filter(!is.na(Taxa_Crescimento), Taxa_Crescimento < 100) %>%
  ungroup()

g9 <- ggplot(crescimento_data, aes(x = Fator_Tamanho, y = Taxa_Crescimento, color = Complexidade)) +
  geom_point(size = 2, alpha = 0.7) +
  geom_smooth(method = "loess", se = TRUE, size = 1.2) +
  scale_x_continuous(breaks = c(2, 5, 10, 50, 100), trans = "log2") +
  scale_y_continuous(breaks = c(1, 2, 5, 10, 25, 50), trans = "log2") +
  scale_color_manual(values = c("#d62728", "#2ca02c", "#1f77b4")) +
  facet_wrap(~Tipo_Entrada_Nome) +
  labs(
    title = "Taxa de Crescimento dos Algoritmos",
    subtitle = "Razão entre tempos consecutivos vs. aumento do tamanho",
    x = "Fator de Aumento do Tamanho",
    y = "Taxa de Crescimento do Tempo",
    color = "Complexidade"
  ) +
  theme_academic +
  theme(legend.position = "bottom")

ggsave("09_taxa_crescimento.png", g9, width = 12, height = 8, dpi = 300)

# =============================================================================
# GRÁFICO 10: EFICIÊNCIA RELATIVA - NORMALIZADO
# =============================================================================

cat("Gerando Gráfico 10: Eficiência Relativa...\n")

# Normalizar pela performance do Mergesort (considerado baseline)
eficiencia_data <- dados %>%
  group_by(Tamanho, Tipo_Entrada) %>%
  mutate(
    Tempo_Mergesort = Tempo_Segundos[Nome_Algoritmo == "Mergesort"],
    Eficiencia_Relativa = Tempo_Segundos / Tempo_Mergesort
  ) %>%
  ungroup() %>%
  filter(!is.na(Eficiencia_Relativa))

g10 <- ggplot(eficiencia_data, aes(x = Tamanho, y = Eficiencia_Relativa, color = Nome_Limpo)) +
  geom_line(size = 1.2, alpha = 0.8) +
  geom_point(size = 2, alpha = 0.9) +
  geom_hline(yintercept = 1, linetype = "dashed", color = "red", size = 1.2) +
  scale_x_log10(
    breaks = c(10, 100, 1000, 10000, 100000, 500000, 5000000, 50000000),
    labels = c("10", "100", "1K", "10K", "100K", "500K", "5M", "50M")
  ) +
  scale_y_log10(breaks = c(0.1, 0.5, 1, 2, 5, 10, 100, 1000)) +
  scale_color_manual(values = cores_algoritmos) +
  facet_wrap(~Tipo_Entrada_Nome) +
  labs(
    title = "Eficiência Relativa ao Mergesort",
    subtitle = "Razão de tempo normalizada (linha vermelha = performance do Mergesort)",
    x = "Tamanho da Entrada (elementos)",
    y = "Eficiência Relativa (log)",
    color = "Algoritmo"
  ) +
  theme_academic +
  theme(legend.position = "bottom") +
  guides(color = guide_legend(nrow = 2, byrow = TRUE))

ggsave("10_eficiencia_relativa.png", g10, width = 14, height = 8, dpi = 300)

# =============================================================================
# ANÁLISES ESTATÍSTICAS E TABELAS
# =============================================================================

cat("\nGerando análises estatísticas...\n")

# Tabela 1: Resumo estatístico por algoritmo
resumo_geral <- dados %>%
  group_by(Nome_Limpo, Complexidade) %>%
  summarise(
    N_Testes = n(),
    Tempo_Min = min(Tempo_Segundos),
    Tempo_Max = max(Tempo_Segundos),
    Tempo_Medio = mean(Tempo_Segundos),
    Tempo_Mediano = median(Tempo_Segundos),
    Desvio_Padrao = sd(Tempo_Segundos),
    CV = Desvio_Padrao / Tempo_Medio * 100,
    .groups = 'drop'
  ) %>%
  arrange(Tempo_Medio)

write_csv(resumo_geral, "resumo_estatistico_algoritmos.csv")

# Tabela 2: Melhores algoritmos por tamanho e tipo
melhores_por_contexto <- dados %>%
  group_by(Tamanho, Tipo_Entrada_Nome) %>%
  slice_min(Tempo_Segundos, n = 3) %>%
  select(Tamanho, Tipo_Entrada_Nome, Nome_Limpo, Tempo_Segundos) %>%
  mutate(Ranking = row_number()) %>%
  ungroup()

write_csv(melhores_por_contexto, "melhores_por_contexto.csv")

# Tabela 3: Análise do Quicksort
analise_quicksort <- dados %>%
  filter(Algoritmo %in% c(5, 6, 7)) %>%
  group_by(Nome_Limpo, Tipo_Entrada_Nome) %>%
  summarise(
    Tempo_Medio = mean(Tempo_Segundos),
    Tempo_Min = min(Tempo_Segundos),
    Tempo_Max = max(Tempo_Segundos),
    Variabilidade = sd(Tempo_Segundos),
    .groups = 'drop'
  ) %>%
  pivot_wider(names_from = Tipo_Entrada_Nome, values_from = c(Tempo_Medio, Variabilidade))

write_csv(analise_quicksort, "analise_quicksort.csv")

# Tabela 4: Escalabilidade por complexidade
escalabilidade <- dados %>%
  group_by(Complexidade, Tamanho) %>%
  summarise(Tempo_Medio = mean(Tempo_Segundos), .groups = 'drop') %>%
  arrange(Complexidade, Tamanho) %>%
  group_by(Complexidade) %>%
  mutate(
    Fator_Crescimento = Tempo_Medio / first(Tempo_Medio),
    Taxa_por_Tamanho = (Tempo_Medio / lag(Tempo_Medio) - 1) * 100
  )

write_csv(escalabilidade, "escalabilidade_complexidade.csv")

# =============================================================================
# RELATÓRIO FINAL
# =============================================================================

cat("\n" + rep("=", 80) + "\n")
cat("RELATÓRIO COMPLETO GERADO COM SUCESSO!\n")
cat(rep("=", 80) + "\n")

cat("\n📊 GRÁFICOS GERADOS (10 visualizações):\n")
graficos <- c(
  "01_visao_geral_comparativa.png - Comparação completa de todos os algoritmos",
  "02_algoritmos_quadraticos.png - Análise detalhada dos algoritmos O(n²)",
  "03_algoritmos_eficientes.png - Análise detalhada dos algoritmos O(n log n)",
  "04_complexidade_assintotica.png - Agrupamento por complexidade teórica",
  "05_quicksort_variantes.png - Comparação das estratégias do Quicksort",
  "06_bubble_original_vs_melhorado.png - Impacto das otimizações no Bubble Sort",
  "07_heatmap_performance.png - Mapa de calor da performance",
  "08_sensibilidade_entrada.png - Sensibilidade ao tipo de entrada",
  "09_taxa_crescimento.png - Taxa de crescimento dos algoritmos",
  "10_eficiencia_relativa.png - Eficiência normalizada pelo Mergesort"
)

for(i in seq_along(graficos)) {
  cat("  ", graficos[i], "\n")
}

cat("\n📈 TABELAS DE ANÁLISE GERADAS (4 arquivos CSV):\n")
tabelas <- c(
  "resumo_estatistico_algoritmos.csv - Estatísticas descritivas completas",
  "melhores_por_contexto.csv - Ranking dos melhores algoritmos por cenário",
  "analise_quicksort.csv - Análise comparativa das variantes do Quicksort", 
  "escalabilidade_complexidade.csv - Análise de escalabilidade por complexidade"
)

for(i in seq_along(tabelas)) {
  cat("  ", tabelas[i], "\n")
}

cat("\n🎯 PRINCIPAIS INSIGHTS PARA O RELATÓRIO:\n")
insights <- c(
  "• Algoritmos O(n²) mostram limitações claras para entradas grandes",
  "• Mergesort apresenta performance mais estável entre os tipos de entrada",
  "• Quicksort com mediana de 3 oferece melhor robustez",
  "• Bubble Sort melhorado mostra ganhos significativos em entradas parcialmente ordenadas",
  "• Heapsort mantém performance consistente independente da entrada",
  "• Algorithms O(n log n) são essenciais para aplicações com grandes volumes de dados"
)

for(insight in insights) {
  cat("  ", insight, "\n")
}

cat("\n📝 PRÓXIMOS PASSOS:\n")
cat("  1. Incorporar os gráficos no relatório Word/LaTeX\n")
cat("  2. Usar as tabelas CSV para análises quantitativas\n")
cat("  3. Citar as complexidades teóricas vs. resultados empíricos\n")
cat("  4. Discutir as implicações práticas de cada algoritmo\n")
cat("  5. Incluir recomendações de uso por cenário\n")

cat("\n🎉 ANÁLISE ACADÊMICA COMPLETA!\n")
cat("Todos os arquivos foram gerados com qualidade de publicação.\n")
cat(rep("=", 80) + "\n")