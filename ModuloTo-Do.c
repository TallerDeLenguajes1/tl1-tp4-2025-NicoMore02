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
Nodo *CrearLista(int id);
Nodo *BuscarporID(Nodo *lista, int id);
Nodo *BuscarporPalabra(Nodo *lista, char *palabra);

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
            case 1: {
                Nodo *nueva = CrearLista(tareaID++);
                insertarLista(&pendientes, nueva);
                break;
            }
            case 2:
                printf("Ingrese el ID de la tarea realizada: ");
                scanf("%d", &buscarID);
                moverTarea(&pendientes, &realizadas, buscarID);
                break;
            case 3:
                listarTareas(pendientes, "Pendiente");
                listarTareas(realizadas, "Realizada");
                break;
            case 4:{ 
                puts("Ingrese 1 para buscar por ID o 2 para buscar por palabra");
                int tipo;
                scanf("%d", &tipo);
                if (tipo == 1) {
                    printf("Ingrese el ID de la tarea a buscar: ");
                    scanf("%d", &buscarID);
                
                    Nodo *res = BuscarporID(pendientes, buscarID);
                    if (!res)
                    {
                        res = BuscarporID(realizadas, buscarID);
                    }
                
                    if (res != NULL) {
                        printf("Tarea encontrada: %s (%d min)\n", res->T.Descripcion, res->T.Duracion);
                    } else
                    {
                        puts("Tarea no encontrada");
                    }
                
                } else if (tipo == 2)
                {
                    printf("Ingrese la palabra a buscar: ");
                    getchar();
                    fgets(palabra, 100, stdin);
                    Nodo *res = BuscarporPalabra(pendientes, palabra);
                    if (!res) {
                        res = BuscarporPalabra(realizadas, palabra);
                    }
                    if (res != NULL) {
                        printf("Tarea encontrada: %s (%d min)\n", res->T.Descripcion, res->T.Duracion);
                    } else {
                        puts("No se encontró ninguna tarea con esa palabra");
                    }
                
                }
                break;
            }
            case 5:
                puts("Saliendo del programa");
                break;
            default:
                puts("Opción no válida");
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
    Nodo *aux = *pendientes, *anterior = NULL;
    while (aux && aux->T.TareaID != id){
        anterior = aux;
        aux = aux->siguiente;
    }
    if (!aux)
    {
        printf("Tarea no encontrada en pendientes\n");
        return;
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
        printf("Tarea: %s || duracion: %d || ID: %d\n", lista->T.Descripcion, lista->T.Duracion, lista->T.TareaID);
        lista = lista->siguiente;
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
    getchar();
    fgets(NNodo->T.Descripcion, 100, stdin);
    do
    {
        printf("Duracion (10 - 100): ");
        scanf("%d", &NNodo->T.Duracion);
        getchar();
    } while (NNodo->T.Duracion < 10 || NNodo->T.Duracion > 100);
    NNodo->siguiente = NULL;
    return NNodo;
}


Nodo *BuscarporID(Nodo *lista, int id) {
    while (lista) {
        if (lista->T.TareaID == id)
            return lista;
        lista = lista->siguiente;
    }
    return NULL;
}

Nodo *BuscarporPalabra(Nodo *lista, char *palabra) {
    while (lista) {
        if (strstr(lista->T.Descripcion, palabra))
            return lista;
        lista = lista->siguiente;
    }
    return NULL;
}