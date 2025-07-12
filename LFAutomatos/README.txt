================================================================================
  CONVERSOR DE AUTÔMATO FINITO NÃO-DETERMINÍSTICO (AFN) PARA DETERMINÍSTICO (AFD)
================================================================================

DESCRIÇÃO
-----------
Este programa implementa a conversão de um Autômato Finito Não-Determinístico (AFN) para um Autômato Finito Determinístico (AFD) equivalente. O programa solicita ao usuário a definição de um AFN de forma interativa e, utilizando o Algoritmo de Construção de Subconjuntos, gera e exibe a definição completa do AFD correspondente.

Este projeto foi desenvolvido para a disciplina de Linguagens Formais e Autômatos.


COMO COMPILAR (Ambiente Linux/Unix)
--------------------------------------
Para compilar o código-fonte, é necessário ter um compilador C como o GCC instalado.

1. Salve o código-fonte em um arquivo com a extensão ".c", por exemplo: `conversor_afn_afd.c`.
2. Abra um terminal na pasta onde o arquivo foi salvo.
3. Execute o seguinte comando:

   $ gcc -o conversor conversor_afn_afd.c

4. Este comando criará um arquivo executável chamado `conversor`.


COMO EXECUTAR
---------------
Após a compilação, execute o programa a partir do terminal com o comando:

   $ ./conversor

O programa iniciará e guiará o usuário para fornecer os dados do AFN.


FORMATO DE ENTRADA
--------------------
O programa solicita os componentes do AFN na seguinte ordem. É crucial seguir a formatação para que o programa funcione corretamente.

1. ESTADOS (Q):
   - Insira os nomes de todos os estados do AFN, separados por espaço.
   - Exemplo: q0 q1 q2

2. ALFABETO (Σ):
   - Insira os símbolos do alfabeto, separados por espaço.
   - O símbolo para a palavra vazia (épsilon) não deve ser incluído aqui.
   - Exemplo: a b

3. ESTADO INICIAL (q0):
   - Insira o nome do estado inicial.
   - Exemplo: q0

4. ESTADOS FINAIS (F):
   - Insira os nomes de todos os estados finais, separados por espaço.
   - Exemplo: q2

5. FUNÇÃO DE TRANSIÇÃO (δ):
   - Insira as transições do AFN, uma por linha, no formato: Origem Simbolo Destino
   - Para representar a PALAVRA VAZIA (ÉPSILON), utilize o caractere '&'.
   - Após inserir todas as transições, pressione a tecla ENTER em uma linha vazia para finalizar.
   - Exemplo de transições:
     d_nfa > q0 a q0
     d_nfa > q0 & q1
     d_nfa > q1 b q2
     d_nfa > 


EXEMPLO DE USO COMPLETO
-------------------------
A seguir, uma sessão de exemplo baseada no autômato do quadro:

$ ./conversor

& CONVERSOR DE AFN PARA AFD &
----------------------------------
Entre com os estados do AFN (ex: q0 q1 q2): 1 2 3
Entre com o alfabeto do AFN (ex: a b): a b
Entre com o estado inicial do AFN (ex: q0): 1
Entre com os estados finais do AFN (ex: q2 q3): 1

Informe as transicoes do AFN (Origem Simbolo Destino).
Use '&' para a palavra vazia. Pressione ENTER em uma linha vazia para finalizar.
  d_nfa > 1 & 3
  d_nfa > 1 b 2
  d_nfa > 2 a 2
  d_nfa > 2 a 3
  d_nfa > 2 b 3
  d_nfa > 3 a 1
  d_nfa > 
...Iniciando conversao para AFD...


ENTENDENDO A SAÍDA
--------------------
O programa exibirá a definição completa do AFD gerado:

- Q_d: O conjunto de novos estados do AFD, nomeados com letras maiúsculas (A, B, C...).
- Detalhamento dos Estados: Mostra qual subconjunto de estados do AFN cada estado do AFD representa (Ex: A = <1,3>).
- Alfabeto: O alfabeto do AFD (o mesmo do AFN, sem o '&').
- q0_d: O estado inicial do AFD.
- F_d: O conjunto de estados finais do AFD. Um estado do AFD é final se contém ao menos um estado final do AFN.
- delta_d: A função de transição do AFD.

OBSERVAÇÃO IMPORTANTE:
----------------------
As transições que não aparecem explicitamente na saída do `delta_d` levam a um estado de erro (ou sumidouro) implícito, que pode ser representado como `<>`. O programa não exibe este estado para manter a saída mais limpa, o que é uma abordagem padrão.
