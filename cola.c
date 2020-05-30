#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "cola.h"

//colaCreaVacia devuelve:
//	-> -1 si c es null
//	->  0 si exito

int colaCreaVacia(Cola *c)
{
    if(c==NULL)
		return -1;
	else{
		c->frente=c->fondo=NULL;
		return 0;
	}
}

//colaVacia devuelve:
//	-> -1 si c es null
//	->  1 si esta vacia
//	->  0 si NO esta vacia

int colaVacia(Cola *c)
{
    if(c==NULL)
		return -1;
	else if(c->frente == NULL && c->fondo == NULL)
		return 1;
	else
		return 0; 
   	
}

//colaInserta devuelve:
//	-> -1 si c es null
//	-> -2 si fallo en reserva memoria
//	->  0 si exito

int colaInsertaC(tipoElementoC elemento, Cola *c)
{
	tipoCelda *aux;
	
    if(c==NULL)
		return -1;
	else{
		if(NULL == (aux=malloc(sizeof(tipoCelda))))
			return -2;
		aux->elemento=elemento;
		aux->sig=NULL;
		
		if(c->frente == NULL && c->fondo == NULL){
			c->fondo=c->frente=aux;
		}
		else{
			c->fondo->sig = aux;
			c->fondo = aux;
		}
		
		return 0;
	}      
}

//colaSuprime devuelve:
//	-> -1 si c es null
//	-> -2 si cola vacia
//	->  valor del elemento borrado si exito

tipoElementoC colaSuprime(Cola *c)
{
	tipoCelda *aBorrar;
	tipoElementoC elemento;
	
    if(c==NULL)
		return -1;

	else if(c->frente == NULL && c->fondo == NULL)
		return -2;

	else{

		aBorrar=c->frente;
		elemento=aBorrar->elemento;

		if(c->fondo==c->frente)
			c->frente=c->fondo=NULL;
		
		else
			c->frente=aBorrar->sig;
		
		
		free(aBorrar);
		return elemento;
	}
}
