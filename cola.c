#include <stdlib.h>
#include <stdbool.h>
#include "cola.h"
#include <stdlib.h>

typedef struct nodo{
	void* dato;
	struct nodo* proximo;
} nodo_t;

struct cola{
	nodo_t* primero;
	nodo_t* ultimo;
	size_t largo;
};

// Crea una cola.
// Post: devuelve una nueva cola vacía.

cola_t* cola_crear(void){
	cola_t* cola = malloc (sizeof(cola_t));
	if(!cola){
		return NULL;
	}
	cola->primero = NULL;
	cola->ultimo = NULL;
	cola->largo = 0;
	return cola;
}

size_t cola_largo(cola_t* cola){
	return cola->largo;
}
// Devuelve verdadero o falso, según si la cola tiene o no elementos encolados.
// Pre: la cola fue creada.
bool cola_esta_vacia(const cola_t *cola){
	return !cola->primero && !cola->ultimo;
}

// Obtiene el valor del primer elemento de la cola. Si la cola tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el primer elemento de la cola, cuando no está vacía.
void* cola_ver_primero(const cola_t *cola){
	if (!cola->primero){
		return NULL;
	}
	return cola->primero->dato;
}

// Agrega un nuevo elemento a la cola. Devuelve falso en caso de error.
// Pre: la cola fue creada.
// Post: se agregó un nuevo elemento a la cola, valor se encuentra al final
// de la cola.
bool cola_encolar(cola_t *cola, void* valor){
	nodo_t* nodo_nuevo;
	nodo_nuevo = malloc (sizeof(nodo_t));
	if (!nodo_nuevo){
		return false; 
	}
	nodo_nuevo->dato = valor ;
	if (cola_esta_vacia(cola)){
		cola->primero = nodo_nuevo;
		cola->primero->proximo = NULL;
	}else{
		cola->ultimo->proximo = nodo_nuevo;
		nodo_nuevo->proximo = NULL;
	}
	cola->ultimo = nodo_nuevo ;
	cola->largo ++;
	return true;
}

// Saca el primer elemento de la cola. Si la cola tiene elementos, se quita el
// primero de la cola, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el valor del primer elemento anterior, la cola
// contiene un elemento menos, si la cola no estaba vacía.
void* cola_desencolar(cola_t *cola){
	if (cola_esta_vacia(cola)){
		return NULL;
	}
	nodo_t* temp;
	void* valor_retorno;
	temp = cola->primero;
	valor_retorno = temp->dato;
	cola->primero = (cola->primero)->proximo;
	if(!cola->primero){
		cola->ultimo = NULL;
	}
	free(temp);
	cola->largo --;
	return valor_retorno;
}

// Destruye la cola. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la cola llama a destruir_dato.
// Pre: la cola fue creada. destruir_dato es una función capaz de destruir
// los datos de la cola, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la cola.
void cola_destruir(cola_t *cola, void destruir_dato(void*)){
	void* temp;
 	while (!cola_esta_vacia(cola)){
		temp = cola_desencolar(cola);
		if (destruir_dato){
			destruir_dato(temp);
		}
	}
	cola->ultimo = NULL ;
	free (cola);
}