#include "pila.h"

#include <stdlib.h>
#include <stdio.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

const size_t CAPACIDAD_INICIAL = 20;
const size_t COEFICIENTE_AUMENTO_CAP = 2;
const size_t DENOMINADOR_DISMINUCION_CAP = 2;
const size_t DENOM_CONDICION_DISMINUCION = 4;

pila_t *pila_crear(void){

	pila_t* pila = malloc(sizeof(pila_t));

	if (pila == NULL){
		return NULL;
	}

	pila->datos = malloc(CAPACIDAD_INICIAL * sizeof(void*));

	if (pila->datos == NULL){
		free(pila);
		return NULL;
	}

	pila->cantidad = 0;
	pila->capacidad = CAPACIDAD_INICIAL;
	return pila;
}

void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
	return pila->cantidad == 0;
}


bool pila_redimensionar(pila_t* pila, size_t nueva_capacidad){
	void* datos_nuevo = realloc(pila->datos, nueva_capacidad * sizeof(void*));
	if (datos_nuevo == NULL) return false;

	pila->datos = datos_nuevo;
	pila->capacidad = nueva_capacidad;
	return true;
}


bool pila_apilar(pila_t *pila, void *valor){

	if (pila->cantidad >= pila->capacidad){
		//si la cantidad supera o iguala la capacidad => duplico la capacidad
		bool redimensiono = pila_redimensionar(pila, pila->capacidad * COEFICIENTE_AUMENTO_CAP);
		if (!redimensiono) return false;
	}

	pila->datos[pila->cantidad] = valor;
	pila->cantidad++;
	return true;
}

void *pila_ver_tope(const pila_t *pila){
	if (pila_esta_vacia(pila)){
		return NULL;
	}
	return pila->datos[pila->cantidad - 1];
}


void *pila_desapilar(pila_t *pila){

	if (pila_esta_vacia(pila)){
		return NULL;
	}

	pila->cantidad--;

	void* dato = pila->datos[pila->cantidad];

	if(pila->cantidad <= pila->capacidad / DENOM_CONDICION_DISMINUCION && pila->capacidad > CAPACIDAD_INICIAL){
		//Si la cantidad es un cuarto de la capacidad => disminuyo a la mitad la capacidad
		pila_redimensionar(pila, pila->capacidad / DENOMINADOR_DISMINUCION_CAP);
	}
	
	return dato;
}

