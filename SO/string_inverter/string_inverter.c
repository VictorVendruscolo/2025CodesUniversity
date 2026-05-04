#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[1024]; /* string compartilhada entre threads */

typedef struct {
    int thread_id;
    int start;
    int end;
} thread_args;

void *inverter(void *param)
{
    thread_args *args = (thread_args *)param;
    int start = args->start;
    int end = args->end;
    
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    
    free(args);
    pthread_exit(0);
}

int main()
{
    FILE *in, *out;
    pthread_t tid[4];
    int len, section_size;
    
    /* Lê string do arquivo */
    in = fopen("../in.txt", "r");
    if (in == NULL) {
        fprintf(stderr, "erro ao abrir ../in.txt\n");
        return -1;
    }
    
    fgets(str, sizeof(str), in);
    fclose(in);
    
    len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }
    
    section_size = len / 4; /* divisão pode não ser exata */
    
    /* Cria 4 threads */
    for (int i = 0; i < 4; i++) {
        thread_args *args = malloc(sizeof(thread_args));
        args->thread_id = i;
        args->start = i * section_size;
        args->end = (i == 3) ? len - 1 : (i + 1) * section_size - 1;
        
        pthread_create(&tid[i], NULL, inverter, args);
    }
    
    /* Aguarda todas as threads */
    for (int i = 0; i < 4; i++) {
        pthread_join(tid[i], NULL);
    }
    
   
    out = fopen("../out.txt", "w");
    if (out == NULL) {
        fprintf(stderr, "erro ao abrir ../out.txt\n");
        return -1;
    }
    
    fprintf(out, "%s\n", str);
    fclose(out);
    
    return 0;
}

