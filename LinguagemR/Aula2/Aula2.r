# 01. Lista
meses <- c("Jan", "Fev", "Mar", "Abr", "Mai", "Jun", "Jul", "Ago", "Set", "Out", "Nov", "Dez")
temp <- c(28.1, 30.5, 29.0, 27.3, 25.5, 23.2, 22.0, 24.5, 26.3, 27.8, 29.2, 30.0)

# a) Qual o mês mais quente?
meses[which.max(temp)]

# b) Meses com temperatura acima de 28°C
meses[temp > 28]

# c) Média das temperaturas
mean(temp)

# d) Novo vetor com temperaturas em Fahrenheit
temp_f <- temp * 9/5 + 32
temp_f

# 02. Data Frame
# a) Crie uma matriz 3x3 com os números de 1 a 9
matriz <- matrix(1:9, nrow = 3, byrow = TRUE)

# b) Some os elementos de cada linha usando rowSums()
rowSums(matriz)

# c) Multiplique todos os elementos da matriz por 2
matriz * 2

# d) Extraia a segunda coluna da matriz
matriz[, 2]

# 03. Data Frame
nome <- c("Ana", "João", "Carlos", "Sofia", "Augusto")
idade <- c(25, 30, 28, 32, 29)
altura <- c(1.65, 1.80, 1.75, 1.68, 1.70)
df <- data.frame(nome, idade, altura)

# a) Filtre as pessoas com altura maior que 1.72
df[df$altura > 1.72, ]

# b) Média das alturas
mean(df$altura)

# c) Dados da pessoa mais velha
df[which.max(df$idade), ]

# 04. Data Frame
# a) Vetor com nomes das disciplinas
disciplinas <- c("Matemática", "História", "Biologia", "Geografia")

# b) Notas de cada disciplina
notas <- c(8.5, 6.0, 7.5, 9.0)

# c) Data frame com disciplina e nota
df_disc <- data.frame(disciplina = disciplinas, nota = notas)

# d) Filtre disciplinas com nota maior ou igual a 7
df_disc[df_disc$nota >=  7, ]