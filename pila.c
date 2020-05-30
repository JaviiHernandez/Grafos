#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pila.h"


//pilaCreaVacia devuelve:
//	-> -1 si p es null
//	->  0 si exito

int pilaCreaVacia(Pila *p)
{
    if(p==NULL)
    	return -1;
    else{
    	*p=NULL;
    	return 0;
	}
}

//pilaVacia devuelve:
//	-> -1 si p es null
//	->  1 si esta vacia
//	->  0 si NO esta vacia

int pilaVacia(Pila *p)
{
    if(p==NULL)
    	return -1;
    else if(*p==NULL)
    	return 1;
    else
    	return 0; 
}

//pilaInserta devuelve:
//	-> -1 si p es null
//	-> -2 si fallo en reserva de memoria
//	->  0 si esta vacia

int pilaInserta(tipoElementoP elemento, Pila *p)
{
	tipoCeldaP *aux;//Pila aux;
	
    if(p==NULL)
    	return -1;
    else{
    	if(NULL == (aux=malloc(sizeof(tipoCeldaP))))
    		return -2;
    	
    	aux->elemento=elemento;
		aux->sig=*p;
		*p=aux;
		
		return 0;
	}
}

//pilaSuprime devuelve:
//	-> -1 si c es null
//	-> -2 si pila vacia
//	->  valor del elemento borrado si exito

tipoElementoP pilaSuprime(Pila *p)
{
	tipoCeldaP *aBorrar;//Pila aBorrar;
	tipoElementoP elemento;
	
    if(p==NULL)
    	return -1;
    else if(*p==NULL)
		return -2;
	else{
    	aBorrar=*p;
    	elemento=aBorrar->elemento;
    	*p=aBorrar->sig;
    	
    	free(aBorrar);
    	return elemento;
	}
    
}
