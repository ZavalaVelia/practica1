#include <stdio.h>
#include <stdlib.h>

#define TAM_INICIAL 64

// --- Prototipos ---
char* leer_texto_dinamico(void);
void mostrar(const char *titulo, const char *texto);
int longitud(const char *cadena);
char* buscar_y_reemplazar(const char *original, const char *buscar, const char *reemplazar);
void liberar_memoria(char **ptr);

int main(void) {
    char *texto_original = NULL;
    char *texto_buscar = NULL;
    char *texto_reemplazar = NULL;
    char *resultado = NULL;

    printf("=== EDITOR DE TEXTO BASICO CON MEMORIA DINAMICA ===\n");

    // Leer textos
    printf("\nIngrese el texto original:\n");
    texto_original = leer_texto_dinamico();
    mostrar("Texto original", texto_original);

    printf("\nIngrese el texto a buscar:\n");
    texto_buscar = leer_texto_dinamico();
    mostrar("Texto a buscar", texto_buscar);

    printf("\nIngrese el texto de reemplazo:\n");
    texto_reemplazar = leer_texto_dinamico();
    mostrar("Texto a reemplazar", texto_reemplazar);

    // Buscar y reemplazar
    resultado = buscar_y_reemplazar(texto_original, texto_buscar, texto_reemplazar);
    mostrar("Texto final", resultado);

    // Liberar memoria
    liberar_memoria(&texto_original);
    liberar_memoria(&texto_buscar);
    liberar_memoria(&texto_reemplazar);
    liberar_memoria(&resultado);

    printf("\nMemoria liberada correctamente.\n");

    return 0;
}

// --- Función para leer texto dinámicamente ---
char* leer_texto_dinamico(void) {
    char *buffer = (char *)malloc(TAM_INICIAL * sizeof(char));
    if (!buffer) { 
        printf("Error de memoria\n"); 
        exit(1); 
    }

    int capacidad = TAM_INICIAL;
    int longitud = 0;
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
        if (longitud >= capacidad - 1) {
            capacidad *= 2;
            char *temp = (char *)realloc(buffer, capacidad * sizeof(char));
            if (!temp) { free(buffer); printf("Error de memoria\n"); exit(1); }
            buffer = temp;
            printf("[DEBUG] Memoria expandida a %d bytes\n", capacidad);
        }
        buffer[longitud++] = (char)c;
    }
    buffer[longitud] = '\0';
    return buffer;
}

// --- Mostrar texto ---
void mostrar(const char *titulo, const char *texto) {
    printf("\n>> %s:\n%s\n", titulo, texto);
}

// --- Longitud manual ---
int longitud(const char *cadena) {
    int len = 0;
    while (cadena[len] != '\0') len++;
    return len;
}

// --- Buscar y reemplazar ---
char* buscar_y_reemplazar(const char *original, const char *buscar, const char *reemplazar) {
    int len_buscar = longitud(buscar);
    int len_reemplazar = longitud(reemplazar);
    int capacidad = 128;
    char *resultado = (char *)malloc(capacidad * sizeof(char));
    if (!resultado) { printf("Error de memoria\n"); exit(1); }

    int idx = 0;
    const char *p = original;

    while (*p) {
        int coincide = 1;
        for (int i = 0; i < len_buscar && p[i]; i++) {
            if (p[i] != buscar[i]) { coincide = 0; break; }
        }

        if (coincide && len_buscar > 0) {
            // Asegurar espacio
            while (idx + len_reemplazar >= capacidad) {
                capacidad *= 2;
                char *temp = (char *)realloc(resultado, capacidad * sizeof(char));
                if (!temp) { free(resultado); printf("Error de memoria\n"); exit(1); }
                resultado = temp;
                printf("[DEBUG] Memoria expandida a %d bytes\n", capacidad);
            }
            // Copiar reemplazo
            for (int j = 0; j < len_reemplazar; j++)
                resultado[idx++] = reemplazar[j];
            p += len_buscar;
        } else {
            // Asegurar espacio
            if (idx + 1 >= capacidad) {
                capacidad *= 2;
                char *temp = (char *)realloc(resultado, capacidad * sizeof(char));
                if (!temp) { free(resultado); printf("Error de memoria\n"); exit(1); }
                resultado = temp;
                printf("[DEBUG] Memoria expandida a %d bytes\n", capacidad);
            }
            resultado[idx++] = *p++;
        }
    }
    resultado[idx] = '\0';
    return resultado;
}

// --- Liberar memoria ---
void liberar_memoria(char **ptr) {
    if (*ptr) { free(*ptr); *ptr = NULL; }
}

