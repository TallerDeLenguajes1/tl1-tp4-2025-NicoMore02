#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estructuras//
typedef struct Tarea
{
    int TareaID;
    char *Descripcion;
    int Duracion;
}Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *siguiente;
}Nodo;


//Funciones del nodo//
Nodo * CrearListaVacia();
Nodo *CrearLista (int id);

//Funciones//
void insertarLista(Nodo **lista, Nodo *nueva);
void liberarlista(Nodo *lista);
void moverTarea(Nodo **pendientes, Nodo **realizadas, int id);
void listarTareas(Nodo *lista, char *tipo);

int main(int argc, char const *argv[])
{
    int opcion, buscarID, tareaID = 1000;
    char palabra[100];
    Nodo *pendientes = NULL;
    Nodo *realizadas = NULL;
    do
    {
        puts("Eliga una opcion");
        puts("1_ Agregar tarea");
        puts("2_ Marcar tarea como realizada");
        puts("3_ Listar Tareas");
        puts("4_ Buscar tarea por ID");
        puts("5_ Salir");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            Nodo *nueva = CrearLista(tareaID++);
            insertarLista(&pendientes, nueva);
            break;
        case 2:
            printf("Ingrese el ID de la tarea realizada: ");
            scanf("%d", &buscarID);
            moverTarea(&pendientes, &realizadas, buscarID);
            break;
        case 3:
            listarTareas(pendientes, "Pendiente");
            listarTareas(realizadas, "Realizada");
            break;
        default:
            break;
        }

    } while (opcion != 5);
    liberarlista(pendientes);
    liberarlista(realizadas);

    return 0;
}


//Definiciones//
void insertarLista(Nodo **lista, Nodo *nueva){
    nueva->siguiente = *lista;
    *lista = nueva;
}

void liberarlista(Nodo *lista) {
    while (lista)
    {
        Nodo *aux = lista;
        lista = lista->siguiente;
        free(aux->T.Descripcion);   
        free(aux);
    }
    
}

void moverTarea(Nodo **pendientes, Nodo **realizadas, int id){
    Nodo *aux = *pendientes, *anterior = CrearListaVacia;
    while (aux && aux->T.TareaID != id){
        anterior = aux;
        aux = aux->siguiente;
    }
    if (!aux)
    {
        printf("Tarea no encontrada en pendientes\n");
    }

    if (anterior)
    {
        anterior->siguiente = aux->siguiente;
    } else {
        *pendientes = aux->siguiente;

    }
    aux->siguiente = *realizadas;
    *realizadas = aux;
    
}

void listarTareas(Nodo *lista, char *tipo){
    printf("Tarea %s:\n", tipo);
    while (lista)
    {
        printf("Tarea: %s || duracion: %d || ID: %d", lista->T.Descripcion, lista->T.Duracion, lista->T.TareaID);
    }
    
}

//Definciones del nodo//
Nodo * CrearListaVacia(){
    return NULL;
}

Nodo *CrearLista (int id){
    Nodo * NNodo = (Nodo *)malloc(sizeof(Nodo));
    NNodo->T.TareaID = id;
    NNodo->T.Descripcion = (char *)malloc(100 * sizeof(char));
    printf("Descripcion: \n");
    gets(NNodo->T.Descripcion);
    do
    {
        printf("Duracion (10 - 100): ");
        scanf("%d", &NNodo->T.Duracion);
        getchar();
    } while (NNodo->T.Duracion < 10 || NNodo->T.Duracion > 100);
    NNodo->siguiente = CrearListaVacia;
    return NNodo;
}
