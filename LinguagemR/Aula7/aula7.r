# 01. Boxplot comparativo das turmas
# Criar vetores com as notas
turmaA <- c(7, 8, 6, 9, 5, 8, 7, 6, 9, 10)
turmaB <- c(5, 6, 5, 7, 6, 7, 5, 8, 7, 6)
turmaC <- c(8, 9, 7, 9, 8, 10, 9, 8, 9, 7)

# Criar data frame
notas <- data.frame(
    Turma = rep(c("A", "B", "C"), each = 10),
    Nota = c(turmaA, turmaB, turmaC)
)

# Criar boxplot
boxplot(Nota ~ Turma, data = notas,
        main = "Comparação das Notas por Turma",
        xlab = "Turma",
        ylab = "Notas",
        col = c("lightblue", "lightgreen", "lightpink"))

# Calcular estatísticas resumo
summary(turmaA)
summary(turmaB)
summary(turmaC)

# Calcular desvio padrão para verificar variabilidade
sd(turmaA)
sd(turmaB)
sd(turmaC)

# 02. Gráfico de barras de publicações por departamento
# Criar vetor com dados
departamentos <- c("Computação", "Matemática", "Engenharia")
publicacoes <- c(45, 30, 25)

# a) Gráfico de barras vertical
barplot(publicacoes, 
        names.arg = departamentos,
        main = "Publicações por Departamento",
        xlab = "Departamento",
        ylab = "Número de Publicações",
        col = "skyblue",
        border = "navy")

# b) Gráfico de barras horizontal
barplot(publicacoes, 
        names.arg = departamentos,
        main = "Publicações por Departamento",
        xlab = "Número de Publicações",
        ylab = "Departamento",
        col = "skyblue",
        border = "navy",
        horiz = TRUE)

# d) Soma total de publicações
total <- sum(publicacoes)
print(paste("Total de publicações:", total))

# e) Percentual por departamento
percentuais <- round((publicacoes/total) * 100, 1)
print(paste("Percentuais:"))
print(paste(departamentos, ":", percentuais, "%"))

# 03. Gráfico de pizza dos meios de transporte
# Criar vetores com dados
transportes <- c("Carro", "Ônibus", "Bicicleta", "A pé")
frequencia <- c(25, 20, 5, 10)

# Calcular percentuais
percentuais <- round(frequencia/sum(frequencia) * 100, 1)
rotulos <- paste(transportes, "\n", percentuais, "%", sep="")

# a) e b) Criar gráfico de pizza com percentuais
pie(frequencia, 
    labels = rotulos,
    main = "Meios de Transporte Utilizados",
    col = c("skyblue", "lightgreen", "pink", "lightyellow"))

# d) Comparar ônibus + bicicleta vs carro
sustentavel <- sum(frequencia[c(2,3)])  # ônibus + bicicleta
carro <- frequencia[1]

cat("\nComparação de transportes:\n")
cat("Ônibus + Bicicleta:", sustentavel, "alunos (", 
    round(sustentavel/sum(frequencia)*100, 1), "%)\n")
cat("Carro:", carro, "alunos (", 
    round(carro/sum(frequencia)*100, 1), "%)\n")

# 04. Distribuição de notas em classes de frequência
# Criar vetores com dados
intervalos <- c("0-2", "2-4", "4-6", "6-8", "8-10")
freq <- c(3, 5, 9, 8, 5)

# a) Gráfico de barras da distribuição
barplot(freq,
        names.arg = intervalos,
        main = "Distribuição das Notas dos Alunos",
        xlab = "Intervalos de Notas",
        ylab = "Frequência",
        col = "lightblue",
        border = "darkblue")

# b) Encontrar intervalo com maior frequência
maior_freq <- max(freq)
intervalo_maior <- intervalos[which.max(freq)]

cat("\nAnálise da distribuição:\n")
cat("Intervalo com maior frequência:", intervalo_maior, 
    "com", maior_freq, "alunos\n")

# Estatísticas adicionais
total_alunos <- sum(freq)
percentual_maior <- round(maior_freq/total_alunos * 100, 1)

cat("Representa", percentual_maior, "% do total de alunos\n")