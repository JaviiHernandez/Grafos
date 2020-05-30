
typedef char tipoElementoP;

typedef struct tipoCeldaP {
	tipoElementoP elemento;
	struct tipoCeldaP * sig;
	} tipoCeldaP;

	
typedef tipoCeldaP * Pila;

int pilaCreaVacia(Pila *p);


// En vacía no sería necesario el paso por referencia
// pero por mantener la misma interfaz con la implementación
// de matrices
int pilaVacia(Pila *p);

int pilaInserta(tipoElementoP elemento, Pila *p);

tipoElementoP pilaSuprime(Pila *p);

