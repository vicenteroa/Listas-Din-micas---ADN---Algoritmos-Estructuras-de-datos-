/* - - - - - - -   TAREA N°1  - - - - - - -     */
/*- - - - -   FECHA: 16 -09 - 2022  - - - -     */
/* - - - ALGORITMOS Y ESTRUCUTRAS DE DATOS - - - */


//LIBRERIAS:
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    char dato; 
    struct nodo{
        char x;
        struct nodo *sig;
    };
    typedef struct nodo tNodo;
    typedef tNodo *Lista;
    Lista creaNodo(char p)
    {
        Lista aux;
        aux = malloc(sizeof(tNodo));
        if (aux !=NULL)
        {
            aux->x = p;
            aux->sig = NULL;
        }
        else
        {
            //CONDICION EN CASO DE QUE NO SE PUEDA GENERAR EL NODO PEDIDO

            printf("\n\t ERROR : no hay suficente espacio en la memoria para crear el nodo");
            system("Pause"); // Funcion que dejara la terminal en pause y no se cierra hasta apretar cualquier boton.
        }
    }
    Lista insertaLista(Lista L , char info)
    {
        Lista pNodo , aux; //CREAMOS LAS VARIABLES.

        pNodo = creaNodo(info); // ESTA VARIABLE CREARA UN NUEVO NODO CON LA FUNCION CREANODO (ESTE NO APUNTARA A NADA)
        if (L == NULL)
        {
            L = pNodo; // ACA DEJAMOS LA LISTA QUE CONTIENE LAS PROTEINAS LIGADO A NUESTRA NUEVA VARIABLE pNodo
        }
        else
        {
            aux=L;
            while (aux->sig != NULL)
            {
                aux =  aux -> sig;
            }
            aux ->sig =  pNodo;
        }
        return L;
    }
    bool guanina(Lista buscador_g )
    {
        int cont =0; //Iniciamos un contador de guaninas

        Lista aux;
        aux = buscador_g;
        while (aux !=NULL)
        {
            if (aux->x == 'g') {
                cont++; // CADA VEZ QUE ENCUENTRE UNA G SUMARA 1 EN EL CONTADOR
                if (cont >=3)
                    return false;
            }else
            cont = 0;
        aux=aux->sig;
        }
        return true;
    }
    bool adenina( Lista buscador_a)
    {
        int cont =0; //Iniciamos un contador de adeninas

        Lista aux;
        aux = buscador_a;
        while (aux !=NULL){
            if (aux->x == 'a') {
            cont++; // CADA VEZ QUE ENCUENTRE UNA G SUMARA 1 EN EL CONTADOR
            if (cont >=2)
                return true;
            }else
                cont = 0;
                    aux=aux->sig;
        }
        return false;
    }
    bool citosina(Lista buscador_c)
    {
        int cont =0; //Iniciamos un contador de citosinas
        Lista aux;
        aux = buscador_c;
        while (aux !=NULL){
            if (aux->x == 'c'){
            cont++;
            if (cont >=2)
                return true;
            }else
            cont = 0;
                aux=aux->sig;
        }
        return false;
    }   
    bool timina(Lista buscador_t)
    {
        Lista aux;
        aux = buscador_t;

        while(aux->sig != NULL)
            aux = aux ->sig;
        if (aux -> x == 't')
            return true;
        return false;
    }
    bool condicon_1(Lista L)
    {
        if(timina(L) == true && guanina(L) == true && (adenina(L) == true || citosina(L)==true)){
            return true;
        }
        else{
            return false;
        }
    }


    void leeArchivo(char nombre[30]) //LA FUNCION VOID NO DEVULEVE NADA EN LA FUNCION
    {
        FILE *archivo;
        Lista L;
        L =NULL;

        archivo = fopen(nombre, "r");
        if (archivo == NULL)
        {
            printf("El archivo no existe..");
            exit(1);
        }
        while (feof(archivo) == 0)
        {
            fscanf(archivo, "%c", &dato);
            L =  insertaLista(L,dato);
        }


        //CONDICIONALES PARA DETERMINAR SI ES MUTANTE O HUMANO

        if(condicon_1(L) == true){
            printf("Mutante");
        }

        else if (condicon_1(L) == false)
                {
            printf("Humano");
                }
        else
        {
            printf("No se pudo determinar..");
        }
        fclose(archivo);
    }


    // FUNCION PRINCIPAL
    int main()
    {
        char nomArch[30];
        printf("Ingresa el nombre del archivo: ");
        gets(nomArch);
        leeArchivo(nomArch);

        printf("\n\n");
        return 0;
    }