#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

#define MAX_INPUT 1024
#define MAX_ARGS 7  /* program + up to 5 args + NULL */

void print_tree(int pid, int depth) {
    char path[256];
    char line[512];
    FILE *f;
    int p, ppid;
    char name[256], state[4];

    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
    f = fopen(path, "r");
    if (!f) return;

    fscanf(f, "%d %s %s %d", &p, name, state, &ppid);
    fclose(f);

    for (int i = 0; i < depth; i++) printf("  ");
    /* name is between parentheses, print as-is */
    printf("%d %s\n", pid, name);

    /* look for children */
    DIR *dir = opendir("/proc");
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        int child_pid = atoi(entry->d_name);
        if (child_pid <= 0) continue;

        char cpath[256];
        snprintf(cpath, sizeof(cpath), "/proc/%d/stat", child_pid);
        FILE *cf = fopen(cpath, "r");
        if (!cf) continue;

        int cp, cppid;
        char cname[256], cstate[4];
        fscanf(cf, "%d %s %s %d", &cp, cname, cstate, &cppid);
        fclose(cf);

        if (cppid == pid) {
            print_tree(child_pid, depth + 1);
        }
    }
    closedir(dir);
}

int main(void) {
    char input[MAX_INPUT];

    while (1) {
        printf("shell> ");
        fflush(stdout);

        if (!fgets(input, sizeof(input), stdin)) break;

        /* remove trailing newline */
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0) continue;

        /* check for background execution */
        int background = 0;
        int len = strlen(input);
        if (input[len - 1] == '&') {
            background = 1;
            input[len - 1] = '\0';
            /* trim trailing space if any */
            len = strlen(input);
            while (len > 0 && input[len - 1] == ' ') {
                input[--len] = '\0';
            }
        }

        /* tokenize */
        char *args[MAX_ARGS];
        int argc = 0;
        char *token = strtok(input, " ");
        while (token != NULL && argc < MAX_ARGS - 1) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;

        if (argc == 0) continue;

        /* built-in: exit */
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        /* built-in: cd */
        if (strcmp(args[0], "cd") == 0) {
            if (argc < 2) {
                fprintf(stderr, "cd: missing argument\n");
            } else {
                if (chdir(args[1]) != 0) {
                    perror("cd");
                }
            }
            continue;
        }

        /* built-in: tree */
        if (strcmp(args[0], "tree") == 0) {
            if (argc < 2) {
                fprintf(stderr, "tree: missing PID\n");
            } else {
                int pid = atoi(args[1]);
                print_tree(pid, 0);
            }
            continue;
        }

        /* external command: fork + execlp */
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
        } else if (pid == 0) {
            /* child: up to 5 additional args */
            execlp(args[0], args[0],
                   argc > 1 ? args[1] : NULL,
                   argc > 2 ? args[2] : NULL,
                   argc > 3 ? args[3] : NULL,
                   argc > 4 ? args[4] : NULL,
                   argc > 5 ? args[5] : NULL,
                   NULL);
            perror("execlp");
            exit(1);
        } else {
            if (!background) {
                waitpid(pid, NULL, 0);
            }
        }
    }

    return 0;
}
