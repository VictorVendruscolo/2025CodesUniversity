#Lista
minhaLista <- list(
  nome="Maria",
  idade = 25,
  notas = c(8.5, 9.0, 7.5),
  aprovado = TRUE
  
)
minhaLista
minhaLista$nome #Acessa o campo "nome" na lista

minhaLista$nome <- "Ana"  #Altera o nome antigo para "Ana"
minhaLista$nome

minhaLista$curso <- "Computação" #Adiciona o campo "curso" na lista
minhaLista

minhaLista$idade <- NULL #Remove um campo

lapply(minhaLista, class) #Retorna as classes de cada elemento da lista

