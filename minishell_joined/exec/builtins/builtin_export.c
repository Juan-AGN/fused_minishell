#include "builtins.h"

/*
// Función auxiliar para verificar si un identificador es válido
int is_valid_identifier(const char *str) {
    if (!str || *str == '\0' || !(isalpha(*str) || *str == '_'))
        return 0;
    str++;
    while (*str) {
        if (!(isalnum(*str) || *str == '_'))
            return 0;
        str++;
    }
    return 1;
}

// Añadir o reemplazar variables en el entorno
void add_to_env(char *key, char *value, char ***envp) {
    int i = 0;
    size_t key_len = strlen(key);
    char *new_var;
    char **new_envp;

    if (!key || !value || !envp) {
        write(2, "add_to_env: Invalid arguments\n", 30);
        return;
    }

    // Verificar si el entorno está vacío y configurarlo
    if (*envp == NULL) {
        write(1, "add_to_env: Initializing empty environment\n", 43);
        *envp = malloc(sizeof(char *)); // Crear espacio para un único NULL
        if (!*envp) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        (*envp)[0] = NULL; // Terminar con NULL
    }

    write(1, "add_to_env: Starting search for existing variable\n", 50);
    for (i = 0; (*envp)[i]; i++) {
        if (strncmp((*envp)[i], key, key_len) == 0 && (*envp)[i][key_len] == '=') {
            write(1, "add_to_env: Variable found, replacing value\n", 45);
            free((*envp)[i]); // Liberar memoria anterior
            new_var = malloc(key_len + strlen(value) + 2);
            if (!new_var) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            sprintf(new_var, "%s=%s", key, value);
            (*envp)[i] = new_var;
            write(1, "add_to_env: Value replaced successfully\n", 40);
            return;
        }
    }

    write(1, "add_to_env: Variable not found, adding new variable\n", 53);

    // Validar si `*envp` tiene memoria válida antes de usar realloc
    if (*envp == NULL) {
        write(2, "add_to_env: envp is NULL before realloc, critical error\n", 56);
        exit(EXIT_FAILURE);
    }

    // Redimensionar el entorno
    new_envp = realloc(*envp, (i + 2) * sizeof(char *));
    if (!new_envp) {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    *envp = new_envp;

    // Crear nueva variable
    new_var = malloc(key_len + strlen(value) + 2);
    if (!new_var) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    sprintf(new_var, "%s=%s", key, value);
    (*envp)[i] = new_var;
    (*envp)[i + 1] = NULL;
    write(1, "add_to_env: New variable added successfully\n", 45);
}

// Implementación del comando export
void builtin_export(char **args, char **envp) {
    int i;
    char *equal_sign;

    if (!args || !envp || !*envp) {
        write(2, "builtin_export: Invalid arguments\n", 34);
        return;
    }

    if (!args[0]) {
        write(1, "builtin_export: Listing exported variables\n", 44);
        for (i = 0; (*envp)[i]; i++) {
            printf("declare -x %s\n", (*envp)[i]);
        }
        return;
    }

    write(1, "builtin_export: Processing arguments\n", 37);
    for (i = 0; args[i]; i++) {
        write(1, "builtin_export: Checking argument\n", 35);
        equal_sign = strchr(args[i], '=');
        if (equal_sign) {
            *equal_sign = '\0';
            write(1, "builtin_export: Found key-value pair\n", 38);
            if (is_valid_identifier(args[i])) {
                write(1, "builtin_export: Identifier is valid\n", 37);
                add_to_env(args[i], equal_sign + 1, envp);
            } else {
                write(2, "builtin_export: Invalid identifier\n", 36);
                fprintf(stderr, "export: `%s': not a valid identifier\n", args[i]);
            }
            *equal_sign = '=';
        } else {
            write(1, "builtin_export: No value, only key\n", 36);
            if (is_valid_identifier(args[i])) {
                add_to_env(args[i], "", envp);
            } else {
                write(2, "builtin_export: Invalid identifier (no value)\n", 46);
                fprintf(stderr, "export: `%s': not a valid identifier\n", args[i]);
            }
        }
    }
}*/