/*
	NUM_PROC=5
*/
#include "mpi.h"
#include <stdio.h>
#include <random>
using namespace std;

const int TAMANIO_VEC=10;
const int LIM_INF_ALEATORIO=1;
const int LIM_SUP_ALEATORIO=10;
/*
* Utilidad para imprimir el vector
* @param *vec puntero con la posicion
*		del arreglo en memoria.
* @param t cantidad de procesos solicitados
*		al entorno MPI
*/
void imprimir_vector(int *vec) {
	int i=0;
	cout << "["<<flush;
	for (i; i <= TAMANIO_VEC-2;i++) {
		cout<<vec[i]<< ", "<<flush;
	}
	cout<<vec[TAMANIO_VEC-1]<<"]"<<endl;
}

int aleatorio(int li, int ls) {
		mt19937 rng;
		rng.seed(random_device()());
		uniform_int_distribution<std::mt19937::result_type> dist6(li,ls);
		return dist6(rng);
}

void carga_vector(int *v) {
	int i;
	for (i=0; i<TAMANIO_VEC; i++) {
		v[i] = aleatorio(LIM_INF_ALEATORIO, LIM_SUP_ALEATORIO);
	}
}

int main (int argc, char *argv[]) {
	int tamanio, id, pescalar=0, pescalartotal=0, i;
	int vec1[TAMANIO_VEC], vec2[TAMANIO_VEC];
	MPI_Status estado;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &tamanio);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);

	int cant_elem_scatt = TAMANIO_VEC/(tamanio);
	int vec1r[cant_elem_scatt], vec2r[cant_elem_scatt];
	/*Carga de los vectores a ser multiplicados*/
	if (id == 0) {
		carga_vector(vec1);
		carga_vector(vec2);
	}

	MPI_Scatter(
			&vec1,/*Buffer que se va a dispersar (Lo utiliza el root)*/
			cant_elem_scatt,/*cantidad elementos a enviar a cada proceso (Lo utiliza el root)*/
			MPI_INT,/*Tipo de datos a dispersar (Lo utiliza el root)*/
			&vec1r,/*Buffer de recepcion de lo dispersado por el root*/
			2,/*Nro elementos que se espera recibir*/
			MPI_INT,/*Tipo de dato a recibir en el buffer*/
			0,/*Proceso que hace la dispersion (root)*/
			MPI_COMM_WORLD/*Comunicador*/);

	MPI_Scatter(
			&vec2,/*Buffer que se va a dispersar (Lo utiliza el root)*/
			cant_elem_scatt,/*cantidad elementos a enviar a cada proceso (Lo utiliza el root)*/
			MPI_INT,/*Tipo de datos a dispersar (Lo utiliza el root)*/
			&vec2r,/*Buffer de recepcion de lo dispersado por el root*/
			2,/*Nro elementos que se espera recibir*/
			MPI_INT,/*Tipo de dato a recibir en el buffer*/
			0,/*Proceso que hace la dispersion (root)*/
			MPI_COMM_WORLD/*Comunicador*/);

	/*Calculo de la multiplicacion*/
	for (i=0; i<cant_elem_scatt; i++) {
		pescalar += vec1r[i] * vec2r[i];
	}
	cout<<"P. Escalar Parcial para P"<<id<<": "<<pescalar<<endl;

	MPI_Reduce(
			&pescalar,/*Buffer de envio inicial*/
			&pescalartotal,
			1,/*Numero de elementos*/
			MPI_INT,/*Tipo de datos*/
			MPI_SUM,/*Operacion de reduccion*/
			0,/*Proceso que realiza la reduccion*/
			MPI_COMM_WORLD/*Comunicador*/);

	if (id == 0) {
		cout << "Resultado de producto escalar: "<<pescalartotal<<endl;
	}

	MPI_Finalize();
	return 0;

}
