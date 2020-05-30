#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafos.h"
#include "monticulo.h"
#include "cola.h"
#include "pila.h"

void profundidad(int v_inicio, tipoGrafo * grafo) {

    int w;
    pArco  p;
    printf("%d ",v_inicio);
    grafo->directorio[v_inicio].alcanzado = 1;
    p = grafo->directorio[v_inicio].lista;
    while (p != NULL){
        w = p->v;
        if (!grafo->directorio[w].alcanzado)
            profundidad(w,grafo);
        p = p->sig;
    }
} //End of profundidad()

void amplitud(int v_inicio, tipoGrafo *grafo) {

    int w;
    pArco p;
    Cola c;

    colaCreaVacia(&c);
    colaInsertaC(v_inicio, &c);

    while (!colaVacia(&c)) {

        w = colaSuprime(&c);

        if (!grafo->directorio[w].alcanzado) {

            printf("%d ",w);
	        grafo->directorio[w].alcanzado = 1;
        	p = grafo->directorio[w].lista;
            while (p!=NULL){
                w = p->v;
                colaInsertaC(w ,&c);
                p = p->sig;
            }
        }
    }

} //End of amplitud()

void verGrafo(tipoGrafo *g){
    int i;
    pArco p;

    printf("\nGrafo  (Orden %d)\n\n",g->orden);
    printf("       alc gEnt oTop dist peso ant \n");
    printf("     +----+----+----+----+----+----+\n");

    for(i = 1; i <= g->orden; i++){
        printf("  %2d | %2d | %2d | %2d |", i, g->directorio[i].alcanzado,
                       g->directorio[i].gradoEntrada, g->directorio[i].ordenTop);
        
        if (g->directorio[i].distancia == INF) printf("  * |");
        
        else   printf(" %2d |", g->directorio[i].distancia);
        
        if (g->directorio[i].peso == INF) printf("  * |");
       
        else   printf(" %2d |", g->directorio[i].peso);
        
        printf(" %2d |",g->directorio[i].anterior);
        p = g->directorio[i].lista;
        
        while (p != NULL){
            printf(" ->%2d", p->v);	// Grafos no ponderados
            //printf(" ->%2d, %2d", p->v, p->peso); // Grafos ponderados
            p = p->sig;
        }
        printf("\n");
    }
    printf("     +----+----+----+----+----+----+\n\n");

} //End of verGrafo()

void iniciar(tipoGrafo *g){
    int i;
    pArco p;
    
    for(i = 0; i <= g->orden; i++) {

        g->directorio[i].alcanzado = 0;
        g->directorio[i].gradoEntrada = 0;
        g->directorio[i].ordenTop = 0;
        g->directorio[i].distancia = INF;
        g->directorio[i].peso = INF;
        g->directorio[i].anterior = 0;
    }
    
    for(i = 0; i <= g->orden; i++) { 

        p = g->directorio[i].lista;

        while(p != NULL) {

            g->directorio[p->v].gradoEntrada++;
            p = p->sig;

        }
    }

} //End of iniciar()

int ordenTop1(tipoGrafo *grafo) {

    int i, j, orden;
    pArco aux;
    
    iniciar(grafo);
    orden = 1;

    for (i = 1; i <= grafo->orden; i++) {

        j = 1;
        while(j <= grafo->orden && !(grafo->directorio[j].ordenTop == 0 && grafo->directorio[j].gradoEntrada == 0))
            j++;
    
        if (j > grafo->orden)
            return -1;
        
        
        grafo->directorio[j].ordenTop = orden++;
        aux = grafo->directorio[j].lista;

        while(aux != NULL) {

            grafo->directorio[aux->v].gradoEntrada--;
            aux = aux->sig;
        }
    }
    return 0;

} //End of ordenTop1()

int ordenTop2(tipoGrafo *grafo) {

    int i, v, orden;
    pArco p;
    Cola c;
    
    iniciar(grafo);
    colaCreaVacia(&c);
    
    for (i = 1; i <= grafo->orden; i++) {

        if (grafo->directorio[i].gradoEntrada == 0) 
            colaInsertaC(i, &c);
        
    }
    
    orden = 1;

    while(!colaVacia(&c)) {

        v = colaSuprime(&c);
        grafo->directorio[v].ordenTop = orden++;
        p = grafo->directorio[v].lista;

        while(p != NULL) {

            grafo->directorio[p->v].gradoEntrada--;
            if(grafo->directorio[p->v].gradoEntrada == 0) 
                colaInsertaC(p->v, &c);
            
            p = p->sig;
        }
    }
    return (orden >= grafo->orden)? (0) : (-1);

} //End of ordenTop2()

void dijkstra1(int vInicio, tipoGrafo *g) {

    int i, j, v;
    pArco p;

    iniciar(g);
    g->directorio[vInicio].distancia = 0;
    g->directorio[vInicio].anterior = 0;

    for (i = 0; i<g->orden; i++) {

        v = -1;
        for (j = 1;j<=g->orden; j++) {

            if((v == -1 || g->directorio[j].distancia < g->directorio[v].distancia) && g->directorio[j].alcanzado==0)
                v = j;

        }

        if(-1 != v) {

            g->directorio[v].alcanzado = 1;
            p = g->directorio[v].lista;

            while(NULL != p) {

                if (g->directorio[p->v].alcanzado == 0 && g->directorio[p->v].distancia > (g->directorio[v].distancia + p->peso)) {

                    g->directorio[p->v].anterior = v;
                    g->directorio[p->v].distancia = g->directorio[v].distancia + p->peso;

                }

                p = p->sig;
            }
        }

    }

} //End of dijkstra1()


void dijkstra2(int vInicio, tipoGrafo *g) {

    int v;
    Monticulo m;
    tipoElementoM e = {0,0};
    pArco p;
    
    iniciar(g);
    iniciaMonticulo(&m);

    g->directorio[vInicio].distancia = 0;
    g->directorio[vInicio].anterior = 0;

    e.clave = 0;
    e.informacion = vInicio;

    insertar(e, &m);

    while(!vacioMonticulo(m)) {

        eliminarMinimo(&m,&e);
        v = e.informacion;

        g->directorio[v].alcanzado = 1;
        p = g->directorio[v].lista;

        while(NULL != p) {

            if (g->directorio[p->v].alcanzado == 0 && g->directorio[p->v].distancia > g->directorio[v].distancia + p->peso) {

                g->directorio[p->v].anterior = v;
                g->directorio[p->v].distancia = g->directorio[v].distancia + p->peso;
                e.informacion = p->v;
                e.clave = g->directorio[p->v].distancia;

                insertar(e,&m);

            }

            p = p->sig;
        }
    }

} //End of dijkstra2()

/*int costeyTrayectoria(int vIni, int vFin, tipoGrafo *g){
	Pila pila;
	int aux1, aux2;
	
	aux1 = vFin;
	inserta(pila, aux1);
	
	aux1 = g->directorio[vFin].anterior;
	inserta(pila, aux1);
		
	while(aux1 != vIni){
		aux1 = g->directorio[aux1].anterior;
		inserta(pila, aux1);
	}
	
	printf("\nCamino minimo del vertice %d al vertice %d: ", vIni, vFin);
	while(!vacia(pila)){
		aux2 = suprime(pila);
		printf("%d ", aux2);
	}
	printf("\n");
	
	return g->directorio[vFin].distancia;
}*/

int costeyTrayectoria(int vIni, int vFin, tipoGrafo *g) {

    int v, i, coste;
    Pila p;
    char string[100];
    memset(string, '\0', sizeof(string));

    v = vFin;
    pilaCreaVacia(&p);

    while(v != vIni && v != 0) {

        pilaInserta(v, &p);
        v = g->directorio[v].anterior;

    }

    pilaInserta(vIni, &p);
    coste = 0;

    if(v == 0) {

        printf ("No hay trayectorias.\n");
        return -1;
    }   
    else {

        i = 0;
        while(!pilaVacia(&p)) {

           printf ("v%d ", pilaSuprime(&p));

        }
        coste = g->directorio[vFin].distancia-g->directorio[vIni].distancia;
        printf("\n\tCamino con un coste de: %2d\n", coste);

        return coste;
    }

} //End of costeyTrayectoria()

void todosCaminosMin(int vIni, tipoGrafo *g) {

    int i;

    for (i = 1; i <= g->orden; i++) {

        printf("\nv%d: ",i);
        costeyTrayectoria(vIni, i, g);

    }
    printf("\n");

} //End of todosCaminosMin()
