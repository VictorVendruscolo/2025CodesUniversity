# Título: Script de Análise e Visualização de Dados de Algoritmos de Ordenação
# Autor: [Seu Nome] via Gemini
# Data: 04/10/2025
# Descrição: Este script lê os resultados dos testes de algoritmos de ordenação,
#            processa os dados e gera gráficos e tabelas para o relatório.

# --- 1. Instalação e Carregamento de Pacotes ---
# Certifique-se de que os pacotes necessários estão instalados.
# Descomente as linhas abaixo se for a primeira vez que os utiliza.
# install.packages("dplyr")
# install.packages("ggplot2")
# install.packages("tidyr")
# install.packages("stringr")
# install.packages("knitr")
# install.packages("RColorBrewer")

library(dplyr)
library(ggplot2)
library(tidyr)
library(stringr)
library(knitr)
library(RColorBrewer)

# Suprime avisos de "no visible binding for global variable"
utils::globalVariables(c("Nome_Algoritmo", "Tamanho", "Tipo_Entrada", "Tempo_Segundos", "Tipo_Entrada_Desc"))

# --- 2. Carregamento e Preparação dos Dados ---

# Carrega o arquivo CSV
# Certifique-se de que o arquivo 'resultados_testes.csv' está no mesmo diretório
# que este script, ou forneça o caminho completo.
tryCatch({
  dados <- read.csv("resultados_testes.csv")
}, error = function(e) {
  stop("Erro: O arquivo 'resultados_testes.csv' não foi encontrado. Verifique o caminho.")
})


# Limpeza e transformação dos dados
dados_proc <- dados %>%
  # Renomeia os tipos de entrada para nomes mais descritivos
  mutate(Tipo_Entrada_Desc = case_when(
    Tipo_Entrada == 'a' ~ "Aleatório (Caso Médio)",
    Tipo_Entrada == 'c' ~ "Crescente (Melhor Caso)",
    Tipo_Entrada == 'd' ~ "Decrescente (Pior Caso)",
    TRUE ~ as.character(Tipo_Entrada)
  )) %>%
  # Converte o tipo de entrada em um fator para ordenação nos gráficos
  mutate(Tipo_Entrada_Desc = factor(Tipo_Entrada_Desc, levels = c("Crescente (Melhor Caso)", "Aleatório (Caso Médio)", "Decrescente (Pior Caso)"))) %>%
  # Remove o prefixo numérico do nome do algoritmo
  mutate(Nome_Algoritmo = str_replace(Nome_Algoritmo, "^[0-9]+,", "")) %>%
  # Garante que Tamanho seja numérico
  mutate(Tamanho = as.numeric(Tamanho))


# Define uma paleta de cores para consistência nos gráficos
qual_col_pals <- brewer.pal.info[brewer.pal.info$category == 'qual',]
col_vector <- unlist(mapply(brewer.pal, qual_col_pals$maxcolors, rownames(qual_col_pals)))
# Pegar 8 cores distintas
cores_algoritmos <- sample(col_vector, length(unique(dados_proc$Nome_Algoritmo)))
names(cores_algoritmos) <- unique(dados_proc$Nome_Algoritmo)


# --- 3. Geração dos Gráficos ---

# GRÁFICO 1: Visão Geral (O(n log n)) com escala logarítmica
# Filtra apenas os algoritmos eficientes para evitar distorção na escala
dados_eficientes <- dados_proc %>%
  filter(!grepl("Bubble|Insertion", Nome_Algoritmo))

plot1 <- ggplot(dados_eficientes, aes(x = Tamanho, y = Tempo_Segundos, color = Nome_Algoritmo, group = Nome_Algoritmo)) +
  geom_line(linewidth = 1) +
  geom_point(size = 2) +
  # Usa escala logarítmica para o eixo Y para melhor visualização das diferenças
  scale_y_log10(breaks = c(0.001, 0.01, 0.1, 1, 10), labels = scales::comma) +
  scale_x_log10(breaks = c(10, 100, 1000, 10000, 100000, 500000), labels = scales::comma) +
  facet_wrap(~Tipo_Entrada_Desc) +
  labs(
    title = "Gráfico 1: Desempenho de Algoritmos Eficientes (O(n log n))",
    subtitle = "Tempo de Execução (em segundos, escala log) vs. Tamanho da Entrada",
    x = "Tamanho da Entrada (n - escala log)",
    y = "Tempo de Execução (segundos - escala log)",
    color = "Algoritmo"
  ) +
  scale_color_manual(values = cores_algoritmos) +
  theme_minimal(base_size = 14) +
  theme(legend.position = "bottom", strip.text = element_text(face = "bold"))

# Salva o Gráfico 1 em um arquivo
ggsave("grafico_1_visao_geral.png", plot = plot1, width = 12, height = 7, dpi = 300)


# Função para gerar os gráficos individuais por tipo de entrada
gerar_plot_por_tipo <- function(dados_filtrados, titulo, subtitulo, nome_arquivo) {
  
# Filtra o Quicksort_Ultimo para entradas > 10000 em cenários ordenados, pois distorce a escala
  if(unique(dados_filtrados$Tipo_Entrada) %in% c('c', 'd')) {
  #    dados_filtrados <- dados_filtrados %>% filter(!(Nome_Algoritmo == 'Quicksort_Ultimo' & Tamanho > 10000))
  }
    
 # plot <- ggplot(dados_filtrados, aes(x = Tamanho, y = Tempo_Segundos, color = Nome_Algoritmo, group = Nome_Algoritmo)) +
    geom_line(linewidth = 1) +
    geom_point(size = 2) +
    scale_x_continuous(labels = scales::comma) +
    scale_y_continuous(labels = scales::comma) +
    labs(
      title = titulo,
      subtitle = subtitulo,
      x = "Tamanho da Entrada (n)",
      y = "Tempo de Execução (segundos)",
      color = "Algoritmo"
    ) +
    scale_color_manual(values = cores_algoritmos) +
    theme_minimal(base_size = 14) +
    theme(legend.position = "bottom")

  ggsave(nome_arquivo, plot = plot, width = 10, height = 6, dpi = 300)
  return(plot)
}

# GRÁFICO 2: Entradas Aleatórias
plot2 <- gerar_plot_por_tipo(
  dados_proc %>% filter(Tipo_Entrada == 'a'),
  "Gráfico 2: Desempenho para Entradas Aleatórias (Caso Médio)",
  "Todos os algoritmos incluídos",
  "grafico_2_aleatorio.png"
)

# GRÁFICO 3: Entradas Crescentes
plot3 <- gerar_plot_por_tipo(
  dados_proc %>% filter(Tipo_Entrada == 'c'),
  "Gráfico 3: Desempenho para Entradas Crescentes (Melhor Caso)",
  "Quicksort_Ultimo (n > 10k) omitido para melhor visualização",
  "grafico_3_crescente.png"
)

# GRÁFICO 4: Entradas Decrescentes
plot4 <- gerar_plot_por_tipo(
  dados_proc %>% filter(Tipo_Entrada == 'd'),
  "Gráfico 4: Desempenho para Entradas Decrescentes (Pior Caso)",
  "Quicksort_Ultimo (n > 10k) omitido para melhor visualização",
  "grafico_4_decrescente.png"
)


# --- 4. Geração da Tabela Resumo ---

# Filtra os dados para as maiores entradas
tabela_dados <- dados_proc %>%
  filter(Tamanho %in% c(100000, 500000)) %>%
  # Pivota a tabela para o formato desejado
  pivot_wider(
    names_from = Tipo_Entrada_Desc,
    values_from = Tempo_Segundos
  ) %>%
  # Organiza as colunas
  select(Nome_Algoritmo, Tamanho, `Crescente (Melhor Caso)`, `Aleatório (Caso Médio)`, `Decrescente (Pior Caso)`) %>%
  # Ordena
  arrange(match(Nome_Algoritmo, names(cores_algoritmos)), Tamanho)

# Formata a tabela em Markdown usando o pacote kable
tabela_markdown <- kable(tabela_dados, format = "pipe", digits = 4, 
                         caption = "Tabela 1: Resumo dos tempos de execução (em segundos) para as maiores entradas testadas.",
                         col.names = c("Algoritmo", "Tamanho (n)", "Crescente", "Aleatório", "Decrescente"))

# Salva a tabela em um arquivo de texto
cat("## Tabela de Resultados\n\n", file = "tabela_1_resumo.md")
cat(tabela_markdown, file = "tabela_1_resumo.md", sep = "\n", append = TRUE)


# --- 5. Fim do Script ---

print("Script finalizado com sucesso!")
print("Os seguintes arquivos foram gerados:")
print("- grafico_1_visao_geral.png")
print("- grafico_2_aleatorio.png")
print("- grafico_3_crescente.png")
print("- grafico_4_decrescente.png")
print("- tabela_1_resumo.md (contém a tabela em formato Markdown)")

# Exibe a tabela no console
print(tabela_markdown)
