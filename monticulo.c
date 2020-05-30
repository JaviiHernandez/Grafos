#include <stdio.h>
#include <stdlib.h>
#include "monticulo.h"

//filtrados, funciones auxiliares para no repetir codigo en todos los algoritmos
void filtradoDescendente(Monticulo *m, int i, tipoElementoM ultimo){
    int hijo,finFiltrado=0;
    
    while(2*i <= m->tamanno && !finFiltrado){
        hijo=2*i;
        if(hijo!=m->tamanno)
            if(m->elemento[hijo+1].clave < m->elemento[hijo].clave)
                hijo=hijo+1;
            if(ultimo.clave > m->elemento[hijo].clave){
            	m->elemento[i] = m->elemento[hijo];
            	i=hijo;
            }
            else
                finFiltrado=1;      
    }
    m->elemento[i]=ultimo;
}

void filtradoAscendente(Monticulo *m, int i,tipoElementoM x){
    while(m->elemento[i/2].clave > x.clave && i!=1){
       	m->elemento[i]=m->elemento[i/2];
      	i=i/2;
    }
    m->elemento[i]=x;
}

//===========================================================================================

//pone el tamanno a 0
void iniciaMonticulo(Monticulo *m){
    m->tamanno=0; 
    //m->elemento[0].clave=-1;       
}

//devuelve 1 si esta vacio, es decir, si el tamanno es 0
//si no, devuelve 0
int vacioMonticulo(Monticulo m){
    if(m.tamanno==0)
        return 1;
    else 
        return 0;
}

//imprime el monticulo por pantalla
void imprime (Monticulo m)
{
    int i;
    if(vacioMonticulo(m))
    	printf("Monticulo vacio.\n");
    else{
    	for (i = 1; i <= m.tamanno; i++)
        	printf("|%d", m.elemento[i].clave);
    	printf("|\n");
	}
}

//devuelve -1 si el monticulo esta ya lleno
//devuelve 1 si se inserta con exito
int insertar(tipoElementoM x, Monticulo *m){
    int i;
    if(m->tamanno==100){
        printf("Monticulo lleno.\n");
        return -1;
    }
    else{	
        m->tamanno=m->tamanno+1;
        i=m->tamanno;
        filtradoAscendente(m,i,x);
        return 1;
    }
}

//devuelve -1 si el monticulo esta vacio
//el valor minimo si este se elimina con exito
int eliminarMinimo(Monticulo *m, tipoElementoM *minimo){
    tipoElementoM ultimo;
    int i;
    
    if(vacioMonticulo(*m)){
        printf("Monticulo vacio.\n");
    	return -1;                     
    }
    else{
        *minimo=m->elemento[1];
        ultimo=m->elemento[m->tamanno];
        m->tamanno=m->tamanno-1;
        i=1;
        filtradoDescendente(m,i,ultimo);
        return 0;  
    }
}

//decrementa en cantidad el valor de la clave que se encuentra en pos
//si al hacerlo queda descolocado el monticulo, se coloca para no perder sus propiedades
void decrementarClave(int pos, int cantidad, Monticulo *m)
{
    tipoElementoM dec;
    
    dec = m->elemento[pos];
    dec.clave -= cantidad;
    filtradoAscendente(m,pos,dec);
}

//incrementa en cantidad el valor de la clave que se encuentra en pos
//si al hacerlo queda descolocado el monticulo, se coloca para no perder sus propiedades
void incrementarClave(int pos, int cantidad, Monticulo *m)
{
    tipoElementoM inc;
    
    inc = m->elemento[pos];
    inc.clave += cantidad;
    filtradoDescendente(m,pos,inc);
}

//devuelve 1 si ES monticulo, es decir, cumple el orden entre padres e hijos
//si no, es decir, si alguno de sus dos hijos es menor que el padre, devuelve 0
int esMonticulo(Monticulo m)
{
    int i;
    
    for(i=1;(2*i+1)<=m.tamanno;i++)
    {
        if ((m.elemento[i].clave > m.elemento[2*i].clave) || (m.elemento[i].clave > m.elemento[2*i + 1].clave))
            return 0;
    }
    return 1;
}

//crea monticulo de tamanno n con los elementos que contiene el vector
//es decir, los coloca ordenados para que SEAN monticulo
void crearMonticulo(Monticulo *m){
    int i,n;
    n=m->tamanno;
    tipoElementoM ultimo; 
     
    for(i=n/2;i>=1;i--){
    	ultimo=m->elemento[i];
        filtradoDescendente(m,i,ultimo);
	}  
}

//===================================================================================
//version : utilizando el propio monticulo para hacer la ordenacion
void heapSort(Monticulo *m){
    int i,j,n;
    tipoElementoM min;
        
    n=m->tamanno;
    j=n;
    for(i=1;i<=n;i++){
        if(!vacioMonticulo(*m)){
        	eliminarMinimo(m,&min); 
			m->elemento[j].clave=min.clave;
			j--;       
        }
    } 
	m->tamanno=n; 
}
