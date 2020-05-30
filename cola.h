
typedef char tipoElementoC;

typedef struct tipoCelda {

	tipoElementoC elemento;
	struct tipoCelda * sig;

	} tipoCelda;

typedef struct {
	
        tipoCelda *frente, *fondo;
} Cola;

int colaCreaVacia(Cola *c);

// En vacía no sería necesario el paso por referencia
// pero por mantener la misma interfaz con la implementación
// de matrices

int colaVacia(Cola *c);

int colaInsertaC(tipoElementoC elemento, Cola *c);

tipoElementoC colaSuprime(Cola *c);
