#include "stand.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LONGITUD_STRING 50

float calcularArea(const Stand *Stand){
    float Area = Stand->largo * Stand->ancho;
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

const char *estadoAString(StandEstado estado) {
    switch (estado) {
        case DISPONIBLE: return "Disponible";
        case RESERVADO:  return "Reservado";
        case VENDIDO:    return "Vendido";
        default:         return "Desconocido";
    }
}

void imprimirLista(const Stand *Head){
    const Stand *Actual = Head;
    while(Actual != NULL){
        printf("ID: %d\n", Actual->numero);
        printf("largo: %2.f\n", Actual->largo);
        printf("ancho: %2.f\n", Actual->ancho);
        printf("estado: %s\n", estadoAString(Actual->estado));
        printf("--------------------\n");
        Actual = Actual->siguiente;
    }
}

Stand *buscarStand(Stand *Head, int numero){
Stand *Actual = Head;

while(Actual != NULL && Actual->numero != numero){
    Actual = Actual->siguiente;
}

if(Actual == NULL){
    printf("No se encontro ningun stand con el numero");
    return NULL;
}
return Actual;
}

int borrarStand(Stand **Head, int numero) {
    if (Head == NULL || *Head == NULL) return 0;

    Stand *actual = *Head;
    Stand *anterior = NULL;

    while (actual != NULL && actual->numero != numero) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) return 0; // No se encontró

    if (anterior == NULL) {
        *Head = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    free(actual);
    return 1;
}

int actualizarStand(Stand **Head, int numero, float AltoNuevo, float AnchoNuevo, StandEstado EstadoNuevo){
    Stand *Actual = buscarStand(*Head, numero);

    if(Actual == NULL) return 0;

    if(strcmp(estadoAString(EstadoNuevo), "Desconocido") != 0) Actual->estado = EstadoNuevo;

    Actual->largo = AltoNuevo;
    Actual->ancho = AnchoNuevo;

    Actual->estado = EstadoNuevo;
    return 1;
}

Stand *crearStand(int numero, float ancho, float largo, StandEstado estado){
    Stand *NuevoStand = (Stand*)malloc(sizeof(Stand));
    if(NuevoStand == NULL){
        printf("Error al asignar memoria para el nuevo stand.\n");
        exit(1);
    }

    //Recolectamos los datos para el nuevo stand (Donde los parametros de la funcion definida) y los asignamos a la estructura
    NuevoStand->numero = numero;
    NuevoStand->estado = estado;
    NuevoStand->estado = estado;
    NuevoStand->largo = largo;
    NuevoStand->ancho = ancho;
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
