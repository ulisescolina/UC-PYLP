/*
	NUM_PROC=10
*/
#include <iostream>
#include <mpi.h>
using namespace std;
/*
* Utilidad para imprimir el vector
* @param *vec puntero con la posicion
*		del arreglo en memoria.
* @param t cantidad de procesos solicitados
*		al entorno MPI
*/
void imprimir_vector(int *vec, int t) {
	int i=0;
	cout << "["<<flush;
	for (i; i <= t-2;i++) {
		cout<<vec[i]<< ", "<<flush;
	}
	cout<<vec[t-1]<<"]"<<endl;
}

int main(int argc, char *argv[])
{
	int tamanio, id;
	MPI_Status estado;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &tamanio);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);

	int vec[tamanio];
	int cant_elementos = id;
	int p_destino = id+1;
	/*
	 El primer proceso, P0, no espera recibir nada
	 entonces a este no se le solicita que realice
	 MPI_Recv().
	*/
	if (id != 0) {
		MPI_Recv(&vec, cant_elementos, MPI_INT, id-1,
			0,  MPI_COMM_WORLD, &estado);
	}
	/*
	 Si el rango es par se carga -rango
	 si el rango es impar se carga rango
	*/
	if (id % 2 == 0) {
		vec[id] = -id;
	} else {
		vec[id] = id;
	}
	/*
	 El ultimo proceso, PN, no espera enviar nada
	 entonces a este no se le solicita que realice
	 MPI_Send().
	 Sin embargo, se hace a este proceso, el ultimo,
	 responsable de la impresion de la version
	 final del vector.
	*/
	if (id < tamanio-1) {
		MPI_Send(&vec, /* Mensaje a enviar */
			cant_elementos+1, /*Cantidad de elementos*/
			MPI_INT, /* Tipo de dato del mensaje*/
			p_destino, /*Proceso receptor del mensaje*/
			0, /* Etiqueta del mensaje */
			MPI_COMM_WORLD /* Comunicador */);
	} else {
		cout<<"Soy el ultimo proceso.\n"<<
		"Este es el vector final: "<<flush;
		imprimir_vector(vec, tamanio);
	}

	MPI_Finalize();
	return 0;
}

