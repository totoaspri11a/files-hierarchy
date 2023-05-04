#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARACTERS 50
// Definición de la estructura del archivo
typedef struct archivo {
    char nombre[MAX_CHARACTERS];
    char directorio[MAX_CHARACTERS];
    struct archivo* siguiente;
} archivo_t;

// Función para crear un nuevo archivo
archivo_t* crear_archivo(char* nombre, char* directorio) {
    archivo_t* archivo = malloc(sizeof(archivo_t));
    strcpy(archivo->nombre, nombre);
    strcpy(archivo->directorio, directorio);
    archivo->siguiente = NULL;
    return archivo;
}

// Función para eliminar un archivo
void eliminar_archivo(archivo_t** lista, char* nombre) {
    archivo_t* actual = *lista;
    archivo_t* anterior = NULL;

    while (actual != NULL) {
        if (strcmp(actual->nombre, nombre) == 0) {
            if (anterior == NULL) {
                *lista = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            free(actual);
            printf("Archivo eliminado.\n");
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    printf("El archivo no se encontró en el directorio.\n");
}

// Función para buscar un archivo
void buscar_archivo(archivo_t* lista, char* nombre, char* usuario) {
    archivo_t* actual = lista;

    while (actual != NULL) {
        if (strcmp(actual->nombre, nombre) == 0) {
            printf("Archivo encontrado en el directorio %s del usuario %s.\n", actual->directorio, usuario);
            return;
        }
        actual = actual->siguiente;
    }

    printf("El archivo no se encontró en el directorio.\n");
}

// Función para listar todos los archivos en el directorio
void listar_archivos(archivo_t* lista, char* usuario) {
    archivo_t* actual = lista;
    printf("\n\n~~~~~~~~~~~~ ARCHIVOS DE %s EN: %s ~~~~~~~~~~~~~~\n", usuario, actual->directorio);
    while (actual != NULL) {
        printf("Nombre: %s\n", actual->nombre);
        actual = actual->siguiente;
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void options_menu(archivo_t* lista, char* nombre, char* directorio, char* usuario) {
    int opcion;
    do {
        printf("~~~~~~~~~~~~ MENÚ ~~~~~~~~~~~~~~\n");
        printf("1. Crear un archivo\n");
        printf("2. Eliminar un archivo\n");
        printf("3. Buscar un archivo\n");
        printf("4. Listar archivos\n");
        printf("5. Salir\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese el nombre del archivo: ");
                scanf("%s", nombre);
                archivo_t* nuevo_archivo = crear_archivo(nombre, directorio);
                nuevo_archivo->siguiente = lista;
                lista = nuevo_archivo;
                printf("Archivo creado.\n");
                break;
            case 2:
                printf("Ingrese el nombre del archivo a eliminar: ");
                scanf("%s", nombre);
                eliminar_archivo(&lista, nombre);
                break;
            case 3:
                printf("Ingrese el nombre del archivo a buscar: ");
                scanf("%s", nombre);
                buscar_archivo(lista, nombre, usuario);
                break;
            case 4:
                listar_archivos(lista, usuario);
                break;
            case 5:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida.\n");
                break;
        }

    printf("\n");

    } while (opcion != 5);
}