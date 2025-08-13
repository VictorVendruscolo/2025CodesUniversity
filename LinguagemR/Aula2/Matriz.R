#Matriz 
mat1 <- matrix(c(1,2,3,4,5,6,7,8), nrow = 2, ncol =4)
mat1
mat2 <- matrix(c(1,2,3,4,5,6,7,8), nrow = 2, ncol = 4, byrow = TRUE )
mat2
mat3 <- matrix(1:9, nrow = 3, ncol = 3)
mat3

mat4 <- matrix(c(1,2,3,4,5,6,7,8,4), nrow = 3, ncol = 3, byrow = TRUE)

#Operações e funções prontas
mat2[1,3]
mat2[ ,2]
mat2[2, ]
dim(mat1) #Dimensão
nrow(mat1) #Numero de linhas
rowSums(mat1) #Somatória de linhas
colSums(mat2) #Somatória de colunas
t(mat2) #Transposta da matriz
solve(mat4) #Inversa da matriz


#Matriz inversa - exemplo
A <- matrix(c(2, 3, 1, 4), nrow = 2, ncol = 2)
inversa <- solve(A)
inversa

#EXEMPLO EXTRA
  # 2x + 3y = 8
  # 1x + 4y = 7

A <- matrix(c(2, 3, 1, 4), nrow = 2, byrow = TRUE)
B <- c(8, 7)
solucao <- solve(A) %*% B #Resolvendo o sistema (Ax = B), ou seja, x = solve(A) %*% B
solucao #Valor de x e y que resolvem a equação
