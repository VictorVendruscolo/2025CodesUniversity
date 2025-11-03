data(airquality)
# Ver as primeiras linhas
head(airquality)

# Estrutura do dataset
str(airquality)

# Resumo estatístico
summary(airquality)


#1
mean(airquality$Ozone, na.rm = TRUE)
sd(airquality$Ozone, na.rm =TRUE)
mean(airquality$Temp, na.rm = TRUE)
sd(airquality$Temp, na.rm =TRUE)

#2 
variancia_por_dia <- tapply(airquality$Temp, airquality$Day, var, na.rm = TRUE)
dias <- as.numeric(names(variancia_por_dia))

plot(dias, variancia_por_dia,
    type="l",
    col="#FF0000",
    lwd=2,
    main="variação da temperatura ao longo dos dias",
    xlab="Dias",
    ylab="Temperatura")


#3
hist(
    airquality$Ozone, 
    main = "Histograma de Ozone",
    xlab = "Dias",
    ylab = "Níveis de Ozone",
    col = "lightblue",
    border = "blue",
    breaks = 5

)

#4

media <- tapply(airquality$Temp, airquality$Month, mean, na.rm = TRUE)
mes_maior <- names(which.max(media))
cat("O mês com a maior média de temperatura é:", mes_maior, "\n")
