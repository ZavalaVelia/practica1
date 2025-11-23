#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------------------------
//                 STRUCT PERSONA
// -----------------------------------------------
typedef struct {
    char *nombre;
    char *cargo;
} Persona;

// Variables globales
char *texto = NULL;          // texto base
Persona *personas = NULL;    // arreglo dinámico de personas
int totalPersonas = 0;

// -----------------------------------------------
//       CREAR TEXTO BASE (USA malloc)
// -----------------------------------------------
void crearTexto() {
    char buffer[500];

    printf("\nEscribe el texto base:\n> ");
    fflush(stdin);
    fgets(buffer, sizeof(buffer), stdin);

    texto = (char *) malloc(strlen(buffer) + 1);

    if (texto == NULL) {
        printf("Error al asignar memoria.\n");
        return;
    }

    strcpy(texto, buffer);
    printf("Texto creado correctamente.\n");
}

// -----------------------------------------------
//      MODIFICAR TEXTO (USA realloc)
// -----------------------------------------------
void modificarTexto() {
    if (texto == NULL) {
        printf("\nPrimero debes crear el texto.\n");
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
    printf("Texto modificado correctamente.\n");
}

// -----------------------------------------------
//     CAPTURAR PERSONAS (usa calloc + malloc)
// -----------------------------------------------
void capturarPersonas() {
    printf("\nCuantas personas deseas registrar?: ");
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

    printf("\nPersonas registradas.\n");
}

// -----------------------------------------------
//     MOSTRAR DOCUMENTOS EN PANTALLA
// -----------------------------------------------
void mostrarDocumentos() {
    if (texto == NULL || personas == NULL) {
        printf("\nDebes capturar texto y personas primero.\n");
        return;
    }

    printf("\n--- DOCUMENTOS GENERADOS ---\n");

    for (int i = 0; i < totalPersonas; i++) {

        printf("\n========================================\n");
        printf(" Documento para: %s (%s)\n", personas[i].nombre, personas[i].cargo);
        printf("========================================\n");
        printf("%s\n", texto);
    }
}

// -----------------------------------------------
//  GENERAR ARCHIVOS INDIVIDUALES
// -----------------------------------------------
void generarArchivos() {
    if (texto == NULL || personas == NULL) {
        printf("\nDebes capturar texto y personas primero.\n");
        return;
    }

    for (int i = 0; i < totalPersonas; i++) {

        char nombreArchivo[120];
        sprintf(nombreArchivo, "documento_%d.txt", i + 1);

        FILE *archivo = fopen(nombreArchivo, "w");

        if (!archivo) {
            printf("No se pudo abrir el archivo %s\n", nombreArchivo);
            continue;
        }

        fprintf(archivo, "Documento para: %s (%s)\n", personas[i].nombre, personas[i].cargo);
        fprintf(archivo, "-----------------------------------------\n");
        fprintf(archivo, "%s\n", texto);

        fclose(archivo);
    }

    printf("\nArchivos generados exitosamente.\n");
}

// -----------------------------------------------
//  GENERAR ARCHIVO ÚNICO CON TODOS LOS DOCUMENTOS
// -----------------------------------------------
void generarArchivoUnico() {
    if (texto == NULL || personas == NULL) {
        printf("\nDebes capturar texto y personas primero.\n");
        return;
    }

    FILE *archivo = fopen("documento_general.txt", "w");

    if (!archivo) {
        printf("No se pudo crear el archivo general.\n");
        return;
    }

    fprintf(archivo, "========== DOCUMENTO GENERAL ==========\n\n");

    for (int i = 0; i < totalPersonas; i++) {

        fprintf(archivo, "-----------------------------------------\n");
        fprintf(archivo, " Documento para: %s (%s)\n", personas[i].nombre, personas[i].cargo);
        fprintf(archivo, "-----------------------------------------\n");
        fprintf(archivo, "%s\n", texto);
    }

    fclose(archivo);

    printf("\nArchivo unico 'documento_general.txt' generado correctamente.\n");
}

// -----------------------------------------------
//        LIBERAR MEMORIA (free)
// -----------------------------------------------
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

// -----------------------------------------------
//                MENÚ (CON SWITCH)
// -----------------------------------------------
int main() {

    int opcion;

    do {
        printf("\n========= EDITOR AVANZADO (PROYECTO FINAL) =========\n");
        printf("1. Crear texto\n");
        printf("2. Modificar texto\n");
        printf("3. Capturar personas\n");
        printf("4. Mostrar documentos en pantalla\n");
        printf("5. Generar documentos en archivos separados\n");
        printf("6. Generar un solo archivo con todos los registros\n");
        printf("7. Salir\n");
        printf("Selecciona una opcion: ");

        scanf("%d", &opcion);
        getchar();

        switch (opcion) {

            case 1: crearTexto(); break;
            case 2: modificarTexto(); break;
            case 3: capturarPersonas(); break;
            case 4: mostrarDocumentos(); break;
            case 5: generarArchivos(); break;
            case 6: generarArchivoUnico(); break;

            case 7:
                printf("Saliendo...\n");
                liberarMemoria();
                break;

            default:
                printf("Opcion no valida.\n");
        }

    } while (opcion != 7);

    return 0;
}

