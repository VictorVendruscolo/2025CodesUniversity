#QUESTÃO 1
meses <- c("Jan", "Fev", "Mar", "Abr", "Mai", "Jun", 
           "Jul", "Ago", "Set", "Out", "Nov", "Dez")

temp <- c(28.1, 30.5, 29.0, 27.3, 25.5, 23.2, 
          22.0, 24.5, 26.3, 27.8, 29.2, 30.0)

meses[temp == max(temp)] #(a)
meses[temp > 28] #(b)
mean(temp) #(c)
temp_fah <- temp * 9/5 + 32 #(d)
temp_fah

data.frame(Mês = meses, Temperatura_C = temp, Temperatura_F = temp_f)

#QUESTÃO 2
mat <- matrix(1:9, nrow = 3, ncol = 3) #(a)
mat
rowSums(mat) #(b)
mat * 2 #(c)
mat[, 2] #(d)

#QUESTÃO 3
nome <- c("Ana", "João", "Carlos", "Sofia", "Augusto")
idade <- c(25, 30, 28, 32, 29)
altura <- c(1.65, 1.80, 1.75, 1.68, 1.70)

dados <- data.frame(
  Nome = nome,
	Idade = idade,
	Altura = altura

)
dados$Nome
dados[dados$Altura > 1.72, ] #(a)
mean(dados$Altura) #(b)
dados[dados$Idade == max(dados$Idade), ] #(c)

#max(dados$Idade) - calcula o maior valor na coluna Idade.
#dados$Idade == max(dados$Idade) - comparamos cada idade com o valor máximo encontrado (32)
#dados[...] - filtrando linhas 
##Mostre todas as colunas da(s) linha(s) onde a idade é igual à maior idade encontrada

#QUESTÃO 4
disciplinas <- c("Matemática", "Português", "História", "Física") #(a)
notas <- c(8.5, 6.0, 9.0, 7.2) #(b)
df <- data.frame(Disciplina = disciplinas, Nota = notas) #(c)
df
df_aprovadas <- df[df$Nota >= 7, ] #(d)
df_aprovadas
