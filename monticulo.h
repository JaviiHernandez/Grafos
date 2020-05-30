
typedef int tipoClave ;
typedef int tipoInfo ;

typedef struct{ 
        tipoClave clave;
        tipoInfo  informacion;
}tipoElementoM;

typedef struct{ 

        tipoElementoM elemento[100];
        int tamanno;

}Monticulo;

/* Funciones auxiliares que conviene implementar: las dos estrategias de filtrado en las 
   que se basan todos los algoritmos que manejan montículos */

void filtradoDescendente(Monticulo *m, int i, tipoElementoM x);
void filtradoAscendente(Monticulo *m, int i, tipoElementoM x);

/* Ejercicio 1 */

void iniciaMonticulo(Monticulo *m);
int vacioMonticulo(Monticulo m);
void imprime (Monticulo m);
int insertar(tipoElementoM x, Monticulo *m);
int eliminarMinimo(Monticulo *m, tipoElementoM *minimo);
void decrementarClave(int pos, tipoClave cantidad, Monticulo *m);
void incrementarClave(int pos, tipoClave cantidad, Monticulo *m);
int esMonticulo(Monticulo m);
void heapSort(Monticulo *m);

/* Operación crearMonticulo la utilizaremos en ejercicio 2 y en tema de grafos */ 

void crearMonticulo(Monticulo *m);
