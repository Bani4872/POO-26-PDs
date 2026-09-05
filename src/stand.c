#include "stand.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float calcularArea(const Stand *Stand){
    float Area = Stand->largo * Stand->ancho; //Operacion para hallar el area
    return Area;
}

void liberarLista(Stand **Head){
    Stand *Actual = *Head;

    while(Actual!= NULL){
        Stand *Anterior = Actual;
        Actual = Actual->siguiente;
        free(Anterior);
    }

    *Head = NULL;
}

const char *estadoAString(StandEstado Estado) {
    switch (Estado) {
        case DISPONIBLE: return "Disponible";//Segun el numero, retorna el string de estado
        case RESERVADO:  return "Reservado";
        case VENDIDO:    return "Vendido";
        default:         return "Desconocido";
    }
}

void imprimirLista(const Stand *Head){
    const Stand *Actual = Head;
    while(Actual != NULL){
        printf("Numero: %d\n", Actual->numero);
        printf("Largo: %.2f\n", Actual->largo);
        printf("Ancho: %.2f\n", Actual->ancho);
        printf("Estado: %s\n", estadoAString(Actual->estado));
        printf("--------------------\n");
        Actual = Actual->siguiente;
    }
}

Stand *buscarStand(Stand *Head, int Numero){
Stand *Actual = Head;

while(Actual != NULL && Actual->numero != Numero){
    Actual = Actual->siguiente;
}

if(Actual == NULL){
    printf("No se encontro ningun stand con el Numero");
    return NULL;
}

return Actual;
}

int borrarStand(Stand **Head, int Numero) {
    if (Head == NULL || *Head == NULL) return 0;

    Stand *Actual = *Head;
    Stand *Anterior = NULL;

    while (Actual != NULL && Actual->numero != Numero) {
        Anterior = Actual;
        Actual = Actual->siguiente;
    }

    if (Actual == NULL) return 0; // No se encontró

    if (Anterior == NULL) {
        *Head = Actual->siguiente;
    } else {
        Anterior->siguiente = Actual->siguiente;
    }

    free(Actual);
    return 1;
}

int actualizarStand(Stand **Head, int Numero, float AltoNuevo, float AnchoNuevo, StandEstado EstadoNuevo){
    Stand *Actual = buscarStand(*Head, Numero);

    if(Actual == NULL) return 0;

    if(strcmp(estadoAString(EstadoNuevo), "Desconocido") != 0) Actual->estado = EstadoNuevo;

    Actual->largo = AltoNuevo;
    Actual->ancho = AnchoNuevo;

    Actual->estado = EstadoNuevo;
    return 1;
}

Stand *crearStand(int Numero, float Ancho, float Largo, StandEstado Estado){
    Stand *NuevoStand = (Stand*)malloc(sizeof(Stand));
    if(NuevoStand == NULL){
        printf("Error al asignar memoria para el nuevo stand.\n");
        exit(1);
    }

    //Recolectamos los datos para el nuevo stand (Donde los parametros de la funcion definida) y los asignamos a la estructura
    NuevoStand->numero = Numero;
    NuevoStand->estado = Estado;
    NuevoStand->estado = Estado;
    NuevoStand->largo = Largo;
    NuevoStand->ancho = Ancho;
    NuevoStand->siguiente = NULL;
    return (NuevoStand);
}

void insertarOrdenadoPorArea(Stand **Head, Stand *NuevoStand){
    Stand *Actual = *Head; //Primera direccion de la lista ligada
    Stand *Anterior = NULL;

    float NuevoArea = calcularArea(NuevoStand);

    while(Actual != NULL && calcularArea(Actual) <= NuevoArea){
        Anterior = Actual;
        Actual = Actual->siguiente;
    }

    if(Anterior == NULL){//Inserta al inicio de la lista
        NuevoStand->siguiente = *Head;
        *Head = NuevoStand;
    }else{
        Anterior->siguiente = NuevoStand;
        NuevoStand->siguiente = Actual;
    }
    return;
}
