#Vetores com os dados
nomes <- c("Ana", "Carlos", "Maria")
idades <- c(23,34,28)
alturas <- c(1.65,1.78,1.70)

#Criando o data frame
dados <- data.frame(Nome = nomes, Idade = idades, Altura = alturas)
dados

dados$Nome #Acessa o nome
mean(dados$Altura) #Mostra a média das alturas
sum(dados$Idade) #Somatória das idades

dados[dados$Idade > 25, ] #Filtra  todas as linhas de dados onde a coluna "Idade" tem um valor maior que 25

novaLinha <- data.frame(Nome = "Daniel", Idade = 28, Altura = 1.75) 
novaLinha

#rbind() - adiciona uma nova informação no data.frame()
dados <- rbind(dados, novaLinha) 
dados
