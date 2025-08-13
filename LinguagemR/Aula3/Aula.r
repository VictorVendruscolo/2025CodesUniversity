# Fixando a semente
set.seed(11)

# 01. Gere 15 números aleatórios uniformes entre 0 e 50. Calcule a média e o desvio padrão.
valores1 <- runif(15, min = 0, max = 50)
media1 <- mean(valores1)
desvio1 <- sd(valores1)

media1
desvio1

# 02. Gere 20 valores de uma distribuição normal com média 50 e desvio padrão 5.
valores2 <- rnorm(20, mean = 50, sd = 5)
variancia2 <- var(valores2)
soma2 <- sum(valores2)

variancia2
soma2

# 03. Gere 100 valores aleatórios normais com média 0 e desvio padrão 1.
valores3 <- rnorm(100, mean = 0, sd = 1)

# a) Filtre apenas os valores maiores que 1.
maiores_que_1 <- valores3[valores3 > 1]

# b) Calcule a proporção desses valores em relação ao total.
proporcao <- length(maiores_que_1) / length(valores3)

maiores_que_1
proporcao