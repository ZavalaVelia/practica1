#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------
//        DEFINICIÓN DEL STRUCT PERSONA
// ---------------------------------------------------
typedef struct {
    char *nombre;
    char *cargo;
} Persona;

// Variables globales
char *texto = NULL;       
Persona *personas = NULL; 
int totalPersonas = 0;

// ---------------------------------------------------
//               FUNCION CREAR TEXTO
// ---------------------------------------------------
void crearTexto() {
    char buffer[500];
    printf("\nEscribe el texto base del documento:\n> ");
    fflush(stdin);
    fgets(buffer, sizeof(buffer), stdin);

    texto = (char *) malloc(strlen(buffer) + 1);
    if (texto == NULL) {
        printf("Error al asignar memoria.\n");
        return;
    }
    strcpy(texto, buffer);
    printf("Texto guardado correctamente.\n");
}

// ---------------------------------------------------
//           FUNCION MODIFICAR TEXTO (REALLOC)
// ---------------------------------------------------
void modificarTexto() {
    if (texto == NULL) {
        printf("\nPrimero debes crear un texto.\n");
        return;
    }

    char buffer[500];
    printf("\nIngresa el nuevo texto:\n> ");
    fflush(stdin);
    fgets(buffer, sizeof(buffer), stdin);

    texto = (char *) realloc(texto, strlen(buffer) + 1);
    if (texto == NULL) {
        printf("Error al reasignar memoria.\n");
        return;
    }

    strcpy(texto, buffer);
    printf("Texto modificado exitosamente.\n");
}

// ---------------------------------------------------
//        CAPTURAR PERSONAS (USA CALLOC)
// ---------------------------------------------------
void capturarPersonas() {
    printf("\n¿Cuantas personas deseas registrar? ");
    scanf("%d", &totalPersonas);
    getchar();

    personas = (Persona *) calloc(totalPersonas, sizeof(Persona));

    if (personas == NULL) {
        printf("Error al asignar memoria.\n");
        return;
    }

    for (int i = 0; i < totalPersonas; i++) {
        char bufferNombre[100];
        char bufferCargo[100];

        printf("\nPersona %d\n", i + 1);

        printf("Nombre: ");
        fgets(bufferNombre, sizeof(bufferNombre), stdin);
        bufferNombre[strcspn(bufferNombre, "\n")] = 0;

        printf("Cargo: ");
        fgets(bufferCargo, sizeof(bufferCargo), stdin);
        bufferCargo[strcspn(bufferCargo, "\n")] = 0;

        personas[i].nombre = (char *) malloc(strlen(bufferNombre) + 1);
        personas[i].cargo  = (char *) malloc(strlen(bufferCargo) + 1);

        strcpy(personas[i].nombre, bufferNombre);
        strcpy(personas[i].cargo, bufferCargo);
    }

    printf("\nPersonas registradas con exito.\n");
}

// ---------------------------------------------------
//         MEZCLAR TEXTO + PERSONA (CREAR DOC)
// ---------------------------------------------------
void mostrarDocumentos() {
    if (texto == NULL || personas == NULL) {
        printf("\nDebes capturar texto y personas primero.\n");
        return;
    }

    printf("\n--- DOCUMENTOS GENERADOS ---\n");

    for (int i = 0; i < totalPersonas; i++) {
        printf("\n========================================\n");
        printf("  Documento para: %s (%s)\n", personas[i].nombre, personas[i].cargo);
        printf("========================================\n");
        printf("%s\n", texto);
    }
}

// ---------------------------------------------------
//              LIBERAR MEMORIA
// ---------------------------------------------------
void liberarMemoria() {
    if (texto != NULL)
        free(texto);

    if (personas != NULL) {
        for (int i = 0; i < totalPersonas; i++) {
            free(personas[i].nombre);
            free(personas[i].cargo);
        }
        free(personas);
    }
}

// ---------------------------------------------------
//              MENU PRINCIPAL (SWITCH)
// ---------------------------------------------------
int main() {
    int opcion;

    do {
        printf("\n========= EDITOR DE TEXTO (P5) =========\n");
        printf("1. Crear texto\n");
        printf("2. Modificar texto\n");
        printf("3. Capturar personas\n");
        printf("4. Mostrar documentos generados\n");
        printf("5. Salir\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                crearTexto();
                break;
            case 2:
                modificarTexto();
                break;
            case 3:
                capturarPersonas();
                break;
            case 4:
                mostrarDocumentos();
                break;
            case 5:
                liberarMemoria();
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }

    } while (opcion != 5);

    return 0;
}

