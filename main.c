#include <stdlib.h>


typedef void * (*t_funcion)(size_t,void *);
typedef void * (*t_iterador)(t_funcion, void *, int);


void * next(void * inicio, size_t size) {

	return &inicio + size;
}

void * prev (void * inicio, size_t size) {
	return &inicio - size;
}



void * forward(t_funcion funcion, void * arreglo, int num) {
	
}

void * backward(t_funcion funcion, void * arreglo, int num) {

}

void * bidir(t_funcion funcion, void * arreglo, int num) {

}



void * recorre(void * arreglo, t_iterador iterador, size_t tamaño, int numElem) {
	int opcion = 0;
	void * curr;
	while (opcion >= 0) {
		printf("Teclea tu opcion \n");
		printf("1 - Begin \n 2 - End \n 3 - Next \n 4 - Prev \n Otro - Salir");
		scanf("%d", opcion);

		switch(opcion)
		{
		case(1) :
			curr = arreglo;
		case(2) :
			curr = &arreglo + (tamaño * (numElem - 1));
		case(3):
			if (&iterador != &forward || &iterador != &bidir) {
				printf("Este iterador no cuenta con esa funcionalidad");
				break;
			}
			   curr = next(arreglo, tamaño);
		case(4):
			if (&iterador != &backward || &iterador != &bidir) {
				printf("Este iterador no cuenta con esa funcionalidad");
				break;
			}
			   curr = backward(arreglo, tamaño);
		default:
			opcion = -1;
		}
	}

}


int main(int argc, const char * argv[]) {
	int juan[2];
	float jose[2];
	char pedro[2];

	juan[0] = 1;
	juan[1] = 2;
	juan[2] = 5;

	jose[0] = 1.0;
	jose[1] = 1.5;
	jose[2] = 2.0;

	pedro[0] = 'a';
	pedro[1] = 'b';
	pedro[2] = 'c';



}