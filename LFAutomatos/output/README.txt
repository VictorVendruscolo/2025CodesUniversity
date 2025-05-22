AUTÔMATO FINITO DETERMINiSTICO (AFD)

Este programa implementa um AFD interativo em C.

---------------------------
COMPILACAO (Unix/Linux):
---------------------------

$ gcc -o afd programa.c

EXECUcaO:
$ ./afd

---------------------------
ENTRADAS DO USUÁRIO:
---------------------------
1. Estados (ex: 0 1 2)
2. Alfabeto (ex: a b ou 0 1)
3. Estado inicial (ex: 0)
4. Estados finais (ex: 2)
5. Transicões delta (ex: delta(0, a) = 1)
6. Palavra a testar (simbolos sem espaço espaco: abba)

---------------------------
OBSERVAcÕES:
---------------------------
- Os estados devem ser nomes simples (preferencialmente números).
- Os simbolos devem ser separados por espaco.
- O simbolo de transicao ineistente e "-1".
- O programa rejeita automaticamente entradas inválidas.
- Aceita ate 30 estados e 30 simbolos.
- Programa criado por Victor Rech Vendruscolo para disciplina de Linguagens Formais.
