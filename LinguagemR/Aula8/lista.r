# 01. Monitoramento de pacotes perdidos
# Criar vetores com dados
dia1 <- c(0,1,0,2,1,0,1,0,2,3,2,1,0,1,0,2,1,0,1,0,2,1,0,1)
dia2 <- c(1,0,2,1,3,2,1,2,3,1,4,2,3,2,1,3,2,1,2,1,3,2,1,2)
horas <- 1:24

# a) Gráfico de linha para Dia 1
plot(horas, dia1, 
     type = "l",           # tipo linha
     col = "blue",         # cor azul
     lwd = 2)             # espessura da linha

# b) Adicionar títulos
plot(horas, dia1,
     type = "l",
     col = "blue",
     lwd = 2,
     main = "Pacotes Perdidos - Dia 1",
     xlab = "Hora",
     ylab = "Número de Pacotes Perdidos")

# Adicionar linha do Dia 2 para comparação
lines(horas, dia2, 
      col = "red", 
      lwd = 2)

# Adicionar legenda
legend("topright",
       legend = c("Dia 1", "Dia 2"),
       col = c("blue", "red"),
       lwd = 2)

# c) Análise de estabilidade
cat("\nAnálise de estabilidade:\n")
cat("Dia 1 - Média:", mean(dia1), "Desvio padrão:", sd(dia1), "\n")
cat("Dia 2 - Média:", mean(dia2), "Desvio padrão:", sd(dia2), "\n")

# 02. Análise do jogo de apostas
# Criar vetor com resultados
resultados <- c(3,7,1,5,9,3,2,4,1,6,2,8,10,7,5,9,4,6,2,3,5,7,8,9,2,6,10,1,5,4)

# a) Calcular lucro líquido apostando no 5
apostas_5 <- resultados == 5  # TRUE para ganhos
ganhos <- sum(apostas_5) * 90    # R$90 por acerto
perdas <- sum(!apostas_5) * 10   # R$10 por erro
lucro <- ganhos - perdas

# b) Distribuição de frequência
freq <- table(resultados)

# c) Gráfico de barras
barplot(freq,
        main = "Frequência dos Números Sorteados",
        xlab = "Número",
        ylab = "Frequência",
        col = "lightblue",
        border = "darkblue")

# Mostrar resultados
cat("\nAnálise das apostas no número 5:\n")
cat("Número de acertos:", sum(apostas_5), "\n")
cat("Ganhos:", ganhos, "reais\n")
cat("Perdas:", perdas, "reais\n")
cat("Lucro líquido:", lucro, "reais\n")


# Dados de tráfego
trafego <- c(52, 55, 49, 60, 72, 68, 65, 58, 70, 75, 62, 55, 80, 78, 74, 67, 73, 69, 64, 76, 71, 66, 59, 63, 77, 61, 56, 69, 74, 72)
dias <- 1:30

# a) Gráfico de linha do tráfego diário
# Para salvar o gráfico, você pode usar png("trafego_diario.png") antes do plot
plot(dias, trafego, type = 'l', col = 'blue', lwd = 2,
     main = 'Tráfego Diário da Rede (GB)',
     xlab = 'Dia',
     ylab = 'Tráfego (GB)',
     ylim = c(45, 85),
     panel.first = grid())

# c) Marcar no gráfico os dias com tráfego > 70 GB
dias_acima_70 <- dias[trafego > 70]
trafego_acima_70 <- trafego[trafego > 70]
points(dias_acima_70, trafego_acima_70, col = 'red', pch = 19, cex = 1.2)

# Adicionar legenda para clareza
legend("topleft", legend = c("Tráfego Diário", "Tráfego > 70 GB"),
       col = c("blue", "red"), lty = 1, pch = c(NA, 19))

# b) Calcular média e desvio padrão
media_trafego <- mean(trafego)
desvio_padrao_trafego <- sd(trafego)

# Imprimir os resultados
print(paste("Média do tráfego:", round(media_trafego, 2), "GB"))
print(paste("Desvio Padrão do tráfego:", round(desvio_padrao_trafego, 2), "GB"))


# Dados dos estudantes
horas_estudo <- c(10, 12, 15, 18, 20, 22, 25, 28, 30, 12, 16, 24)
horas_sono <- c(6, 7, 6, 8, 7, 7, 8, 9, 8, 6, 7, 8)
nota_final <- c(6.0, 6.5, 7.0, 7.8, 8.0, 8.2, 8.5, 9.0, 9.2, 6.8, 7.5, 8.8)

# a) Gráficos de dispersão
# Configura o layout para mostrar dois gráficos lado a lado
par(mfrow = c(1, 2))

# Gráfico 1: Nota vs Estudo
plot(horas_estudo, nota_final, main = "Nota vs. Horas de Estudo",
     xlab = "Horas de Estudo/Semana", ylab = "Nota Final", pch = 19, col = "darkgreen")
grid()

# Gráfico 2: Nota vs Sono
plot(horas_sono, nota_final, main = "Nota vs. Horas de Sono",
     xlab = "Horas de Sono/Noite", ylab = "Nota Final", pch = 19, col = "purple")
grid()

# b) Estatísticas descritivas
# Criar um data frame para facilitar a análise
dados_estudantes <- data.frame(
  "Horas de Estudo" = horas_estudo,
  "Horas de Sono" = horas_sono,
  "Nota Final" = nota_final
)

# A função summary() já fornece a maioria das estatísticas
summary(dados_estudantes)

# Para adicionar o desvio padrão
desvios_padrao <- sapply(dados_estudantes, sd)
print("Desvios Padrão:")
print(desvios_padrao)

# Dados das notas
matematica <- c(68, 75, 80, 90, 55, 72, 88, 94, 60, 70, 82, 77, 85, 91, 66, 73, 79, 87, 65, 78, 92, 84, 69, 71, 76, 81, 74, 89, 63, 67, 70, 83, 95, 61, 68, 72, 86, 90, 64, 75, 79, 88, 82, 69, 71, 85, 93, 77, 80, 74)
programacao <- c(78, 82, 85, 91, 70, 80, 88, 94, 72, 79, 84, 81, 89, 92, 75, 78, 83, 90, 74, 82, 93, 87, 76, 77, 85, 86, 79, 91, 73, 75, 78, 84, 95, 72, 80, 82, 88, 90, 74, 81, 85, 89, 83, 77, 79, 87, 92, 80, 84, 78)

# a) Calcular estatísticas
estatisticas <- data.frame(
  Metrica = c("Média", "Mediana", "Desvio Padrão", "Variância"),
  Matematica = c(mean(matematica), median(matematica), sd(matematica), var(matematica)),
  Programacao = c(mean(programacao), median(programacao), sd(programacao), var(programacao))
)
print(estatisticas)

# b) Gráfico de dispersão
plot(matematica, programacao,
     main = "Notas de Programação vs. Matemática",
     xlab = "Notas de Matemática",
     ylab = "Notas de Programação",
     pch = 19, col = alpha("blue", 0.6))
grid()

# c) Adicionar linha de regressão
abline(lm(programacao ~ matematica), col = "red", lwd = 2)

# d) Histogramas
par(mfrow = c(1, 2)) # Layout para 2 gráficos

hist(matematica, main = "Distribuição - Matemática",
     xlab = "Notas", ylab = "Frequência", col = "skyblue", border = "black")

hist(programacao, main = "Distribuição - Programação",
     xlab = "Notas", ylab = "Frequência", col = "salmon", border = "black")

