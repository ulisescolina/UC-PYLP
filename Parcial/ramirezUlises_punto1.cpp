/*
 	NUM_PROC=7
*/
#include "mpi.h"
#include <iostream>
#include <stdio.h>
#include <random>
using namespace std;

const int LIM_INF_ALEATORIO=15;
const int LIM_SUP_ALEATORIO=31;
const int INDICE_MULTI=10;

/*
* Utilidad para imprimir el vector
* @param *vec puntero con la posicion
*		del arreglo en memoria.
* @param tam cantidad de elementos a imprimir
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

void carga_vector(int *v, int tam) {
	int i;
	for (i=0; i<tam; i++) {
		v[i] = aleatorio(LIM_INF_ALEATORIO, LIM_SUP_ALEATORIO);
	}
}

int main(int argc, char *argv[])
{
	int tamanio, id, cant_distribuir=INDICE_MULTI, i, max, max_local=0;
	double promedio_temperaturas=0;
	MPI_Status estado;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &tamanio);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);

	int CANT_TEMPERATURAS = tamanio*INDICE_MULTI;
	int temperaturas[CANT_TEMPERATURAS], temperaturas_local[cant_distribuir];

	if (id == 0) {
		carga_vector(temperaturas, CANT_TEMPERATURAS);
		cout<<"Las temperaturas generadas son las siguientes: "<<flush;
		imprimir_vector(temperaturas, CANT_TEMPERATURAS);
	}

	/* Dispersion del vector a los procesos */
	MPI_Scatter(
			&temperaturas,/*Buffer que se va a dispersar (Lo utiliza el root)*/
			cant_distribuir,/*cantidad elementos a enviar a cada proceso (Lo utiliza el root)*/
			MPI_INT,/*Tipo de datos a dispersar (Lo utiliza el root)*/
			&temperaturas_local,/*Buffer de recepcion de lo dispersado por el root*/
			cant_distribuir,/*Nro elementos que se espera recibir en cada proceso*/
			MPI_INT,/*Tipo de dato a recibir en el buffer*/
			0,/*Proceso que hace la dispersion (Lo utiliza el root)*/
			MPI_COMM_WORLD/*Comunicador*/);

	/* Busqueda de temperatura maxima */
	max_local = temperaturas_local[0];
	for (i=1; i < cant_distribuir; i++) {
		if (temperaturas_local[i] > max_local) {
			max_local = temperaturas_local[i];
		}
	}
	cout<<"Temp. Maxima calculada en P"<<id<<": "<<max_local<<endl;
	MPI_Reduce(
			&max_local,/*Buffer local que se quiere reducir*/
			&max,/*Buffer en el que se guarda la operacion de reduccion*/
			1,/*Numero de elementos*/
			MPI_INT,/*Tipo de datos*/
			MPI_SUM,/*Operacion de reduccion MPI_[MAX|MIN|SUM|PROD|LAND(y logica)|LOR(o logica)|LXOR(o exclusiva)]*/
			0,/*Proceso que realiza la reduccion*/
			MPI_COMM_WORLD/*Comunicador*/);

	if (id == 0) {
		promedio_temperaturas = max/tamanio;
		cout<<"El promedio de temperaturas maximas para la semana es de: "<<promedio_temperaturas<<endl;
	}

	MPI_Finalize();
	return 0;
}
