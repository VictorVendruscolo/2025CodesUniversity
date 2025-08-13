idades <- c(20, 22, 20, 21, 23, 22, 20, 21, 22, 23)

# Frequência absoluta
freq_abs <- table(idades)

# Frequência relativa (em porcentagem)
freq_rel <- prop.table(freq_abs) * 100

# Frequência acumulada
freq_acum <- cumsum(freq_abs)

# Exibindo os resultados
print("Frequência absoluta:")
print(freq_abs)

print("Frequência relativa (%):")
print(freq_rel)

print("Frequência acumulada:")
print(freq_acum)