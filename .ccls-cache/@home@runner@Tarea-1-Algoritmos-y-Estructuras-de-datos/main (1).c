#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//constantes
#define NAME 40

//lista dinamica ADN
struct ADN {
    char proteina;
    struct nodo * siguiente; 
};
typedef struct ADN tNodo;
typedef tNodo *ListaDeDatos;

ListaDeDatos crear_nodo_de_proteinas(char tipo_de_proteina){
    /* crea los nodos para el adn al resivir cada parametro */
    ListaDeDatos datos_de_proteina;
    datos_de_proteina = malloc(sizeof(tNodo));
    if (datos_de_proteina != NULL) {
        datos_de_proteina->proteina = tipo_de_proteina;
        datos_de_proteina->siguiente = NULL;
    } else {
        system("color 4");
        printf("\nNo hay memoria suficiente, para trabajar");
        exit(1);
    }
    return datos_de_proteina;
}

ListaDeDatos insertar_datos(ListaDeDatos datos_proteinas, char proteinas){
    /* insertar los valores en los nodos */
    ListaDeDatos pNodo, auxiliar;
    pNodo = crear_nodo_de_proteinas(proteinas);
    if(datos_proteinas == NULL){
        datos_proteinas = pNodo;
    }else {
        auxiliar = datos_proteinas;
        while(auxiliar->siguiente != NULL){
            auxiliar = auxiliar->siguiente;
        }
        auxiliar->siguiente = pNodo;
    }
    return datos_proteinas;
}

bool mutacion_guanina(ListaDeDatos buscar){
    // revisa las guaninas
    ListaDeDatos revisar;
    revisar = buscar;
    int contador = 0;
    while(revisar != NULL){
        if (revisar->proteina == 'g'){
            contador ++;
            if(contador >= 3)
                return false;
        } else
            contador = 0;
        revisar = revisar->siguiente;
    }
    return true;
}

bool mutacion_adeninas(ListaDeDatos buscar){
    //revisa las adeninas
    ListaDeDatos revisar;
    revisar = buscar;
    int contador = 0;
    while(revisar != NULL){
        if (revisar->proteina == 'a'){
            contador ++;
            if(contador >= 2)
                return true;
        } else
            contador = 0;

        revisar = revisar->siguiente;
    }
    return false;
}

bool mutacion_citosinas(ListaDeDatos buscar){
    //revisa las citosinas
    ListaDeDatos revisar;
    revisar = buscar;
    int contador = 0;
    while(revisar != NULL){
        if (revisar->proteina == 'c'){
            contador ++;
            if(contador >= 2)
                return true;
        } else
            contador = 0;

        revisar = revisar->siguiente;
    }
    return false;
}

bool timina_al_final(ListaDeDatos buscar){
    /* revisa si hay una timina al final del texto */
    ListaDeDatos revisar;
    revisar = buscar;
    while(revisar->siguiente != NULL)
        revisar = revisar->siguiente;
    if(revisar->proteina == 't')
        return true;
    return false;
}

void lectura_de_archivo(char nombre_documento[NAME]) {
    /* lectura de los archivos */
    FILE * archivo_a_leer;
    char dato;
    ListaDeDatos lista;
    lista = NULL;
    archivo_a_leer = fopen(nombre_documento, "r");	
    if(archivo_a_leer == NULL) {
        system("color 4");
        printf("El %s archivo no ha podido ser encontrado.", nombre_documento);  
        exit(1); 
    }
    while (fscanf(archivo_a_leer,"%c", &dato) != EOF)
        lista = insertar_datos(lista, dato);

    fclose(archivo_a_leer);
    if(timina_al_final(lista) == true && mutacion_guanina(lista) == true && mutacion_adeninas(lista) == true && mutacion_citosinas(lista) == true)
        printf("Mutante");
    else
        printf("Humano");

}

int main() {
    char nombre_archivo[NAME];
    printf("Ingrese el nombre del archivo: ");
    gets(nombre_archivo);
    lectura_de_archivo(nombre_archivo);

    return 0;
}