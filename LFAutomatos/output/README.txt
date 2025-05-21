AUTÔMATO FINITO DETERMINÍSTICO (AFD)

Este programa implementa um AFD interativo em C.
Permite criar autômatos com estados numéricos, alfabeto com símbolos simples,
e testar múltiplas palavras antes de encerrar.

---------------------------
COMPILAÇÃO (em Unix/Linux):
---------------------------

$ gcc -o afd programa.c

Onde:
- "programa.c" é o nome do arquivo com o código-fonte.
- "afd" será o executável gerado.

---------------------------
EXECUÇÃO:
---------------------------

$ ./afd

O programa solicitará as seguintes entradas, todas separadas por espaço:

1. Conjunto de estados:        Ex: 0 1 2
2. Símbolos do alfabeto:       Ex: a b
3. Estado inicial:             Ex: 0
4. Estados finais:             Ex: 2
5. Transições (delta):         Para cada (estado, símbolo), insira o estado destino
6. Palavra a ser testada:      Ex: a b b

Após o teste da palavra, o usuário pode:
- Testar nova palavra no mesmo autômato
- Criar novo autômato
- Encerrar o programa

---------------------------
OBSERVAÇÕES:
---------------------------

- Todos os estados devem ser números (ex: 0, 1, 2).
- Os símbolos do alfabeto podem ser strings (ex: a, b, 10).
- A entrada é feita por espaço. Não use vírgulas.
- O programa trata apenas autômatos determinísticos (AFD).
- Use "-1" para indicar transição inexistente.

---------------------------
DESENVOLVIDO POR: VICTOR RECH VENDRUSCOLO
PARA: OSVALDO - LINGUAGEM FORMAL E AUTOMATOS
