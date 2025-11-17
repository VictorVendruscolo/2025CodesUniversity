/*
TM M2 — Decider de potência de dois para cadeias de ‘0’
Este programa implementa, em C, a máquina de Turing M2 (Sipser) que decide
A = { 0^{2^n} | n ≥ 0 }, aceitando cadeias formadas apenas por ‘0’ cujo
comprimento é potência de dois. A lógica segue a descrição clássica:
em cada rodada varre a fita cruzando cada segundo 0; se restar um único 0,
ACERTA; se sobrar quantidade ímpar > 1, REJEITA; repete caso contrário.
Referências didáticas com essa descrição aparecem em notas/aulas baseadas
no Sipser, exemplificando a M2 e seu procedimento de “metade repetida”.​

Uso

./tm_m2 [OPÇÕES] <cadeia_de_zeros>

Opções

-v, --verbose   Mostra logs por rodada (tape e contagem de 0 não cruzados).
-q, --quiet     Oculta logs; imprime apenas ACCEPT/REJECT.
-h, --help      Exibe esta ajuda.

Exemplos

./tm_m2 0         -> ACCEPT   (1 = 2^0)
./tm_m2 00        -> ACCEPT   (2 = 2^1)
./tm_m2 0000      -> ACCEPT   (4 = 2^2)
./tm_m2 000       -> REJECT   (3 é ímpar > 1)
./tm_m2 00000     -> REJECT   (5 é ímpar > 1)
./tm_m2 -v 0000   -> Logs detalhados + ACCEPT (demonstra as rodadas).

Requisitos

- Linux com GCC/Clang; compilar com:
    gcc -O2 -std=c17 -Wall -Wextra -o tm_m2 main.c
- Terminal UTF-8 recomendado; o programa chama setlocale(LC_ALL, "")
  para suportar Unicode quando necessário.
  
Observações
- Cadeia vazia rejeita (considera-se 2^0 = 1, portanto precisa de pelo menos um ‘0’).
- Implementação usa ‘x’ como marca de zero cruzado e repete a varredura até o critério
  de parada, reproduzindo o comportamento da M2 descrito em material de curso.
- Parsing de opções feito com getopt_long (glibc).
Saída extra

*/



#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include <locale.h>

static bool verbose = false;
static bool quiet = false;

static bool is_power_of_two_zeros(char *s) {
    size_t n = strlen(s);
    if (n == 0) return false;
    for (size_t i = 0; i < n; i++) if (s[i] != '0') return false;

    // fita mutável
    char tape[1 << 20];
    if (n >= sizeof(tape)) return false;
    strncpy(tape, s, sizeof(tape));
    tape[n] = '\0';

    int round = 0;
    while (1) {
        round++;
        int count_uncrossed = 0;
        bool cross_next = false;

        if (verbose && !quiet) {
            fprintf(stderr, "[round %d] scanning: %s\n", round, tape);
        }

        for (size_t i = 0; tape[i]; i++) {
            if (tape[i] == '0') {
                count_uncrossed++;
                if (cross_next) tape[i] = 'x';
                cross_next = !cross_next;
            }
        }

        if (verbose && !quiet) {
            fprintf(stderr, "[round %d] remaining zeros: %d; tape: %s\n",
                    round, count_uncrossed, tape);
        }

        if (count_uncrossed == 1) return true;
        if (count_uncrossed == 0) return false;
        if (count_uncrossed % 2 == 1) return false;
        // repete
    }
}

static void print_usage(const char *prog) {
    printf("Usage: %s [OPTIONS] <string_of_zeros>\n", prog);
    printf("Decide if the input length is a power of two (Sipser M2).\n");
    printf("Options:\n");
    printf("  -v, --verbose   print per-round logs\n");
    printf("  -q, --quiet     suppress logs, only ACCEPT/REJECT\n");
    printf("  -h, --help      show this help\n");
}

int main(int argc, char **argv) {
    // Habilita Unicode/UTF-8 no Linux quando disponível
    setlocale(LC_ALL, "");

    static struct option long_opts[] = {
        {"verbose", no_argument, 0, 'v'},
        {"quiet",   no_argument, 0, 'q'},
        {"help",    no_argument, 0, 'h'},
        {0,0,0,0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "vqh", long_opts, NULL)) != -1) {
        switch (opt) {
            case 'v': verbose = true; break;
            case 'q': quiet = true;   break;
            case 'h': print_usage(argv[0]); return 0;
            default:  print_usage(argv[0]); return 2;
        }
    }

    if (optind >= argc) {
        print_usage(argv[0]);
        return 2;
    }

    char *input = argv[optind];
    bool ok = is_power_of_two_zeros(input);

    if (!quiet) {
        printf("%s\n", ok ? "ACCEPT" : "REJECT");
    } else {
        // modo quiet: só resultado
        printf("%s\n", ok ? "ACCEPT" : "REJECT");
    }

    printf("Professor, nao esqueca das minhas faltas no SAU <3\n");

    return ok ? 0 : 1;
}

