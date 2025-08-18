# 18/08/2025 Exercícios - Victor Rech Vendruscolo
# --- Resolução da Lista de Exercícios de Estatística em R ---

# Configurando o ambiente para garantir a reprodutibilidade dos resultados
# set.seed() fixa a "semente" geradora de números aleatórios.
# É como dar o mesmo ponto de partida para um sorteio, garantindo que
# os números "aleatórios" gerados sejam sempre os mesmos.
set.seed(123)

# --------------------------------------------------------------------------
# Questão 01: Amostra de 50 números inteiros entre 1 e 10
# --------------------------------------------------------------------------
cat("--- Questão 01 ---\n")

# Gerando a amostra de dados
# A função `sample()` sorteia valores.
# 1:10 -> Define o intervalo de números possíveis (de 1 a 10).
# 50 -> É o tamanho da amostra que queremos.
# replace = TRUE -> Permite que o mesmo número seja sorteado mais de uma vez.
dados_q1 <- sample(1:10, 50, replace = TRUE)
print("Amostra gerada:")
print(dados_q1)

# a) Frequência Absoluta
# `table()` é a função principal para contar a ocorrência de cada valor.
freq_abs_q1 <- table(dados_q1)
print("a) Tabela de Frequência Absoluta:")
print(freq_abs_q1)

# b) Frequência Relativa
# `prop.table()` calcula a proporção (frequência / total).
freq_rel_q1 <- prop.table(freq_abs_q1)
print("b) Tabela de Frequência Relativa:")
print(freq_rel_q1)

# c) Frequência Acumulada e Relativa Acumulada
# `cumsum()` calcula a soma acumulada dos valores.
freq_acum_q1 <- cumsum(freq_abs_q1)
freq_rel_acum_q1 <- cumsum(freq_rel_q1)
print("c) Frequência Acumulada:")
print(freq_acum_q1)
print("c) Frequência Relativa Acumulada:")
print(freq_rel_acum_q1)

# --------------------------------------------------------------------------
# Questão 02: Cor favorita de 15 pessoas
# --------------------------------------------------------------------------
cat("\n--- Questão 02 ---\n")

# Criando o vetor com os dados fornecidos
dados_q2 <- c(
    "Azul", "Vermelho", "Azul", "Verde", "Azul", "Preto", "Vermelho",
    "Verde", "Azul", "Preto", "Azul", "Vermelho", "Azul", "Preto", "Verde"
)
print("Dados:")
print(dados_q2)

# [cite_start]a) Monte a tabela de frequência absoluta [cite: 9]
freq_abs_q2 <- table(dados_q2)
print("a) Tabela de Frequência Absoluta:")
print(freq_abs_q2)

# [cite_start]b) Calcule a frequência relativa [cite: 10]
freq_rel_q2 <- prop.table(freq_abs_q2)
print("b) Tabela de Frequência Relativa:")
print(freq_rel_q2)

# [cite_start]c) Qual a cor mais escolhida? [cite: 11]
# `which.max()` retorna o índice (posição) do maior valor na tabela.
# `names()` pega o nome correspondente a essa posição.
cor_mais_escolhida <- names(which.max(freq_abs_q2))
cat("c) A cor mais escolhida é:", cor_mais_escolhida, "\n")

# --------------------------------------------------------------------------
# Questão 03: Forma de transporte para ir à faculdade
# --------------------------------------------------------------------------
cat("\n--- Questão 03 ---\n")

# [cite_start]Criando o vetor com os dados da pesquisa [cite: 13]
dados_q3 <- c("Carro", "Ônibus", "Bicicleta", "A pé", "Carro", "Ônibus", "Carro", "Bicicleta", "Ônibus", "Carro", "A pé", "Carro", "Ônibus", "Bicicleta", "A pé", "Carro", "Ônibus", "Carro", "Carro", "A pé", "Ônibus", "Bicicleta", "Carro", "Carro", "Ônibus", "Carro", "Ônibus", "Bicicleta", "A pé", "Carro", "Ônibus", "Carro", "Bicicleta", "Ônibus", "Carro", "Carro", "A pé", "Ônibus", "Carro", "Bicicleta")
print("Dados:")
print(dados_q3)


# [cite_start]a) Construa a tabela de frequência absoluta [cite: 14]
freq_abs_q3 <- table(dados_q3)
print("a) Tabela de Frequência Absoluta:")
print(freq_abs_q3)

# [cite_start]b) Construa a tabela de frequência relativa [cite: 15]
freq_rel_q3 <- prop.table(freq_abs_q3)
print("b) Tabela de Frequência Relativa:")
print(freq_rel_q3)

# [cite_start]c) Qual o transporte mais utilizado? [cite: 16]
transporte_mais_utilizado <- names(which.max(freq_abs_q3))
cat("c) O transporte mais utilizado é:", transporte_mais_utilizado, "\n")

# [cite_start]d) Qual a proporção de alunos que usam carro ou ônibus? [cite: 17]
# Somamos as frequências relativas de "Carro" e "Ônibus".
prop_carro_onibus <- freq_rel_q3["Carro"] + freq_rel_q3["Ônibus"]
cat("d) A proporção de alunos que usam carro ou ônibus é:", prop_carro_onibus, "ou", prop_carro_onibus * 100, "%\n")

# --------------------------------------------------------------------------
# Questão 04: 100 lançamentos de uma moeda
# --------------------------------------------------------------------------
cat("\n--- Questão 04 ---\n")

# [cite_start]Fixando a semente para reprodutibilidade [cite: 18]
set.seed(123)

# Simulando os 100 lançamentos
# `c("Cara", "Coroa")` -> Define os possíveis resultados.
# 100 -> Número de lançamentos.
# replace = TRUE -> Essencial para permitir repetições.
lancamentos <- sample(c("Cara", "Coroa"), 100, replace = TRUE)
print("Resultado dos 100 lançamentos:")
print(lancamentos)

# [cite_start]a) Construa a tabela de frequência absoluta [cite: 19]
freq_abs_q4 <- table(lancamentos)
print("a) Tabela de Frequência Absoluta:")
print(freq_abs_q4)

# [cite_start]b) Obtenha a frequência relativa [cite: 20]
freq_rel_q4 <- prop.table(freq_abs_q4)
print("b) Tabela de Frequência Relativa:")
print(freq_rel_q4)

# --------------------------------------------------------------------------
# Questão 05: Pesquisa com 30 pessoas usando rep()
# --------------------------------------------------------------------------
cat("\n--- Questão 05 ---\n")

# [cite_start]Usando a função rep() para gerar o vetor [cite: 21]
# `rep("Valor", vezes)` repete o "Valor" um número de "vezes".
# Juntamos tudo com a função `c()` para criar um único vetor.
respostas_q5 <- c(rep("Sim", 10), rep("Não", 12), rep("Talvez", 8))
print("Vetor de respostas gerado:")
print(respostas_q5)

# [cite_start]a) Monte a tabela de frequência absoluta [cite: 25]
freq_abs_q5 <- table(respostas_q5)
print("a) Tabela de Frequência Absoluta:")
print(freq_abs_q5)

# [cite_start]b) Calcule a frequência relativa [cite: 26]
freq_rel_q5 <- prop.table(freq_abs_q5)
print("b) Tabela de Frequência Relativa:")
print(freq_rel_q5)

# [cite_start]c) Qual a resposta mais comum? [cite: 27]
resposta_comum <- names(which.max(freq_abs_q5))
cat("c) A resposta mais comum é:", resposta_comum, "\n")

# --------------------------------------------------------------------------
# Questão 06: Tipo de música favorita com probabilidades
# --------------------------------------------------------------------------
cat("\n--- Questão 06 ---\n")

# Definindo os estilos e suas respectivas probabilidades
estilos <- c("Pop", "Rock", "Sertanejo", "Funk")
probabilidades <- c(0.3, 0.25, 0.35, 0.1) # [cite: 29]

# [cite_start]Simulação das 100 respostas [cite: 28]
# O argumento `prob` na função `sample()` permite definir um peso para cada item
# Sertanejo (0.35) tem a maior chance de ser sorteado.
dados_q6 <- sample(estilos, 100, replace = TRUE, prob = probabilidades)
print("Amostra de estilos musicais gerada:")
print(dados_q6)

# [cite_start]a) Monte a tabela de frequência absoluta [cite: 30]
freq_abs_q6 <- table(dados_q6)
print("a) Tabela de Frequência Absoluta:")
print(freq_abs_q6)

# [cite_start]b) Obtenha a frequência relativa [cite: 31]
freq_rel_q6 <- prop.table(freq_abs_q6)
print("b) Tabela de Frequência Relativa:")
print(freq_rel_q6)

# [cite_start]c) Construa a frequência acumulada e relativa acumulada [cite: 32]
freq_acum_q6 <- cumsum(freq_abs_q6)
freq_rel_acum_q6 <- cumsum(freq_rel_q6)
print("c) Frequência Acumulada:")
print(freq_acum_q6)
print("c) Frequência Relativa Acumulada:")
print(freq_rel_acum_q6)

# [cite_start]d) Qual o estilo mais escolhido? [cite: 33]
estilo_mais_escolhido <- names(which.max(freq_abs_q6))
cat("d) O estilo mais escolhido foi:", estilo_mais_escolhido, "\n")
