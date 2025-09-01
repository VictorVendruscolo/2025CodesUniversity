# 1. Gráfico de dispersão x vs x²
x <- 1:20
y <- x^2

# Plot inicial
plot(x, y)

# a) Mudar cor para vermelho
plot(x, y, col="red")

# b) Mudar símbolo para triângulo (pch=2)
plot(x, y, col="red", pch=2)

# c) Adicionar título e rótulos
plot(x, y, col="red", pch=2,
     main="Gráfico de Dispersão: x vs x²",
     xlab="Valores de x",
     ylab="Valores de x²")

# 2. Gráfico de temperaturas médias mensais
tempo <- 1:12
temperaturas <- c(23, 25, 22, 20, 18, 17, 16, 18, 20, 22, 24, 26)

# Criar gráfico de linha com personalizações
plot(tempo, temperaturas, 
     type = "l",           # tipo linha
     col = "blue",         # cor azul
     lwd = 2,              # espessura da linha
     main = "Temperaturas Médias Mensais",
     xlab = "Mês",
     ylab = "Temperatura (°C)")

# Adicionar legendas nos meses (opcional)
axis(1, at=1:12, labels=c("Jan","Fev","Mar","Abr","Mai","Jun",
                         "Jul","Ago","Set","Out","Nov","Dez"))

# 3. Histograma da distribuição normal
# Gerar 100 valores normais
set.seed(123)  # Para reprodutibilidade
valores <- rnorm(100, mean = 50, sd = 10)

# Criar histograma com personalizações
hist(valores, 
     breaks = 15,         # 15 quebras
     col = "lightblue",   # cor das barras
     border = "white",    # cor da borda
     main = "Distribuição dos Valores",
     xlab = "Valores",
     ylab = "Frequência")

# Adicionar linha de densidade (opcional)
lines(density(valores), col = "red", lwd = 2)

# 4. Gráfico de dispersão com linha de tendência
# Gerar valores
x <- 1:50
y <- 3*x + rnorm(50, 0, 10)  # y = 3x + ruído normal

# Criar gráfico de dispersão personalizado
plot(x, y,
     col = "blue",        # pontos azuis
     pch = 16,           # círculos preenchidos
     lwd = 2,            # espessura dos pontos
     main = "Gráfico de Dispersão com Linha de Tendência",
     xlab = "Valores de X",
     ylab = "Valores de Y")

# Adicionar linha de tendência
abline(lm(y ~ x), col = "red", lwd = 2)

# Adicionar legenda
legend("topleft", 
       legend = c("Dados", "Linha de Tendência"),
       col = c("blue", "red"),
       pch = c(16, NA),
       lty = c(NA, 1),
       lwd = c(2, 2))

# 5. Gráfico da função seno
# Criar sequência de valores x
x <- seq(0, 2*pi, length.out = 100)
y <- sin(x)

# Criar gráfico em linha
plot(x, y, 
     type = "l",         # tipo linha
     col = "darkblue",   # cor da linha
     lwd = 2,            # espessura
     main = "Função Seno",
     xlab = "x",
     ylab = "sin(x)")

# Adicionar linha horizontal em y = 0
abline(h = 0, col = "red", lty = 2)  # linha tracejada vermelha

# Adicionar grade (opcional)
grid()

# 6. Gráfico com vetores dados
x <- c(4, 7, 8, 9, 10, 12, 14, 16, 18, 20)
y <- c(2, 4, 7, 10, 15, 20, 28, 32, 40, 50)

# a) Plot com pontos sólidos
plot(x, y, pch = 16)  # ponto sólido

# b) Adicionar linha de regressão vermelha
linha_reg <- lm(y ~ x)
lines(x, predict(linha_reg), col = "red", lwd = 2)

# c) Adicionar linha horizontal em y = 20
abline(h = 20, col = "blue", lty = 2)

# d) Adicionar linha vertical em x = 12
abline(v = 12, col = "green", lty = 2)

# Personalizar gráfico
title(main = "Gráfico de Dispersão com Linhas de Referência",
      xlab = "Valores de X",
      ylab = "Valores de Y")

# Adicionar legenda
legend("topleft", 
       legend = c("Dados", "Regressão", "Linha y = 20", "Linha x = 12"),
       col = c("black", "red", "blue", "green"),
       lty = c(NA, 1, 2, 2),
       pch = c(16, NA, NA, NA))




