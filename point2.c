#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functionsArchive.c"

#define MAX_CHARACTERS 50
// Definición de la struct para el directorio
typedef struct directorio {
    char usuario[MAX_CHARACTERS];
    char password[MAX_CHARACTERS];
    char nombre[MAX_CHARACTERS]; // nombre del directorio
    struct directorio* siguiente;
} directorio_t;

// function para crear directorios predeterminados cuando se inicia el programa
directorio_t* crear_directorio(char* usuario, char* password, char* nombre, directorio_t* lista) {
    directorio_t* directorio = malloc(sizeof(directorio_t));
    strcpy(directorio->usuario, usuario);
    strcpy(directorio->password, password);
    strcpy(directorio->nombre, nombre);
    directorio->siguiente = lista;
    return directorio;
}

// Lista de directorios predeterminados con su usuario predeterminado
directorio_t* directorios_predeterminados() {
    directorio_t* lista = NULL;
    lista = crear_directorio("root", "root", "Documentos", lista);
    lista = crear_directorio("user", "user", "Escritorio", lista);
    lista = crear_directorio("admin", "admin", "Descargas", lista);
    return lista;
}

// función que con el usuario y contraseña ingresados, verifica si existe el directorio
// si existe retorna el directorio, si no existe retorna NULL
directorio_t* login_directorio(directorio_t* lista, char* usuario, char* password) {
    directorio_t* actual = lista;

    while (actual != NULL) {
        if (strcmp(actual->usuario, usuario) == 0 && strcmp(actual->password, password) == 0) {
            printf("Bienvenido %s.\n\n", actual->usuario);
            return actual;
        }
        actual = actual->siguiente;
    }

    printf("El usuario o contraseña son incorrectos.\n");
    return NULL;
}

int main(){
    archivo_t* lista = NULL;
    char nombre[MAX_CHARACTERS];

    directorio_t* lista_directorios = NULL;
    char usuario[MAX_CHARACTERS];
    char password[MAX_CHARACTERS];

    lista_directorios = directorios_predeterminados();

    printf("\nIngrese su usuario: ");
    scanf("%s", usuario);
    printf("Ingrese su contraseña: ");
    scanf("%s", password);

    login_directorio(lista_directorios, usuario, password);

    // llamar options_menu con el nombre del directorio actual
    options_menu(lista, nombre, lista_directorios->nombre, lista_directorios->usuario);

    // Liberar memoria de los archivos restantes
    archivo_t* actual = lista;
    while (actual != NULL) {
        archivo_t* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    return 0;

}