/*
	NUM_PROC=5
*/
#include "mpi.h"
#include <stdio.h>
#include <random>
using namespace std;

const int INDICE_MULTIPLICATIVO=10;
const int TAMANIO_VEC=50;
const int LIM_INF_ALEATORIO=1;
const int LIM_SUP_ALEATORIO=100;
/*
* Utilidad para imprimir el vector
* @param *vec puntero con la posicion
*		del arreglo en memoria.
* @param t cantidad de procesos solicitados
*		al entorno MPI
*/
void imprimir_vector(int *vec, int tam) {
	int i=0;
	cout << "["<<flush;
	for (i; i <= tam-2;i++) {
		cout<<vec[i]<< ", "<<flush;
	}
	cout<<vec[tam-1]<<"]"<<endl;
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

void ordenar_vector(int *v){
	int i, j;
  for (i = 0; i < INDICE_MULTIPLICATIVO-1; i++)
		for (j = 0; j < INDICE_MULTIPLICATIVO-i-1; j++)
			if(v[j] > v[j+1]){
				int temp = v[j];
				v[j] = v[j+1];
				v[j+1]=temp;
			}
}

int main (int argc, char *argv[]) {
	int tamanio, id, i;
	MPI_Status estado;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &tamanio);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);

	int tamanio_nuevo = tamanio*INDICE_MULTIPLICATIVO;
	int vec[tamanio_nuevo];
	int vec_local[INDICE_MULTIPLICATIVO];

	/*Carga de los vectores a ser multiplicados*/
	if (id == 0) {
		carga_vector(vec);
	}

	/* Proceso 0 se encarga de la dispersion del vector principal */
	MPI_Scatter(
			&vec,/*Buffer que se va a dispersar (Lo utiliza el root)*/
			INDICE_MULTIPLICATIVO,/*cantidad elementos a enviar a cada proceso (Lo utiliza el root)*/
			MPI_INT,/*Tipo de datos a dispersar (Lo utiliza el root)*/
			&vec_local,/*Buffer de recepcion de lo dispersado por el root*/
			INDICE_MULTIPLICATIVO,/*Nro elementos que se espera recibir*/
			MPI_INT,/*Tipo de dato a recibir en el buffer*/
			0,/*Proceso que hace la dispersion (root)*/
			MPI_COMM_WORLD/*Comunicador*/);

	cout<<"P"<<id<<": "<<flush;
	imprimir_vector(vec_local, 10);

	ordenar_vector(vec_local);

	MPI_Gather(
			&vec_local,/*Buffer que se va a juntar*/
			INDICE_MULTIPLICATIVO,/*cantidad elementos a recibir de cada proceso*/
			MPI_INT,/*Tipo de datos a recibir*/
			&vec,/*Buffer de recepcion*/
			INDICE_MULTIPLICATIVO,/*Nro elementos que se espera recibir*/
			MPI_INT,/*Tipo de dato a recibir en el buffer(Lo utiliza el root)*/
			0,/*Proceso Receptor*/
			MPI_COMM_WORLD/*Comunicador*/);

	if (id == 0) {
		cout << "Vector ordenado: "<< flush;
		imprimir_vector(vec, 50);
	}

	MPI_Finalize();
	return 0;

}
