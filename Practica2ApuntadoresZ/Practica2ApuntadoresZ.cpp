/* editor_basico_simple.c
   Editor de texto básico (Buscar y Reemplazar)
   Usa arreglos, apuntadores y funciones simples sin librerías avanzadas.
   Compilar: gcc -o editor_basico_simple editor_basico_simple.c
   Ejecutar: ./editor_basico_simple
*/

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define TEMP_SIZE 2048

// --- Prototipos ---
void llenar_buffer(char *buf, int size);
void mostrar(const char *titulo, const char *texto);
void buscar_y_reemplazar(const char *original, const char *buscar, const char *reemplazar, char *resultado, int res_size);

// --- Función principal ---
int main(void) {
    char buffer[BUFFER_SIZE];
    char buscar[BUFFER_SIZE];
    char reemplazar[BUFFER_SIZE];
    char resultado[TEMP_SIZE];

    printf("=== EDITOR DE TEXTO BASICO (Buscar y Reemplazar) ===\n\n");

    // Llenar el texto original
    printf("Ingrese el texto original:\n");
    llenar_buffer(buffer, BUFFER_SIZE);
    mostrar("Texto original", buffer);

    // Texto a buscar
    printf("\nIngrese el texto a buscar:\n");
    llenar_buffer(buscar, BUFFER_SIZE);
    mostrar("Texto a buscar", buscar);

    // Texto a reemplazar
    printf("\nIngrese el texto a reemplazar:\n");
    llenar_buffer(reemplazar, BUFFER_SIZE);
    mostrar("Texto a reemplazar", reemplazar);

    // Realizar el reemplazo
    buscar_y_reemplazar(buffer, buscar, reemplazar, resultado, TEMP_SIZE);

    // Mostrar resultado final
    mostrar("\nTexto final", resultado);

    return 0;
}

// --- Función para leer texto del usuario ---
void llenar_buffer(char *buf, int size) {
    fgets(buf, size, stdin);
    // eliminar salto de línea si lo hay
    int len = 0;
    while (buf[len] != '\0') {
        if (buf[len] == '\n') {
            buf[len] = '\0';
            break;
        }
        len++;
    }
}

// --- Mostrar título y texto ---
void mostrar(const char *titulo, const char *texto) {
    printf("\n>> %s:\n%s\n", titulo, texto);
}

/* --- Buscar y reemplazar (versión básica) ---
   Recorre carácter por carácter el texto original.
   Cuando encuentra la palabra a buscar, copia la palabra de reemplazo.
*/
void buscar_y_reemplazar(const char *original, const char *buscar, const char *reemplazar, char *resultado, int res_size) {
    const char *p = original;  // puntero para recorrer el texto original
    char *r = resultado;       // puntero para escribir el nuevo texto

    int len_buscar = 0, len_reemplazar = 0;

    // calcular longitudes manualmente (sin strlen)
    while (buscar[len_buscar] != '\0') len_buscar++;
    while (reemplazar[len_reemplazar] != '\0') len_reemplazar++;

    // si la cadena a buscar está vacía, copiamos el original
    if (len_buscar == 0) {
        while (*p != '\0' && (r - resultado) < res_size - 1) {
            *r = *p;
            r++;
            p++;
        }
        *r = '\0';
        return;
    }

    // recorrer el texto original
    while (*p != '\0' && (r - resultado) < res_size - 1) {
        int i = 0;
        int coincide = 1;  // asumimos que sí coincide

        // Comprobar si desde 'p' comienza la palabra 'buscar'
        while (i < len_buscar && p[i] != '\0') {
            if (p[i] != buscar[i]) {
                coincide = 0;
                break;
            }
            i++;
        }

        if (coincide && len_buscar > 0) {
            // Copiar palabra de reemplazo
            int j = 0;
            while (j < len_reemplazar && (r - resultado) < res_size - 1) {
                *r = reemplazar[j];
                r++;
                j++;
            }
            // Avanzar puntero original más allá de la palabra encontrada
            p += len_buscar;
        } else {
            // Copiar carácter tal cual
            *r = *p;
            r++;
            p++;
        }
    }

    *r = '\0'; // terminar cadena
}

