#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <random>

const int TAMANIO_VEC=12;

/*
* Utilidad para imprimir el vector
* @param *vec puntero con la posicion
*		del arreglo en memoria.
* @param t cantidad de procesos solicitados
*		al entorno MPI
*/
void imprimir_vector(int *vec) {
	int i=0;
	std::cout << "["<<std::flush;
	for (i; i <= TAMANIO_VEC-2;i++) {
	std::cout<<vec[i]<< ", "<<std::flush;
	}
	std::cout<<vec[TAMANIO_VEC-1]<<"]"<<std::endl;
}

void carga_vector(int *v) {
	int i;
	for (i=0; i<TAMANIO_VEC; i++) {
		v[i] = i+1;
	}
}

int main(){
	int hilo, i, suma=0, cant_multiplos=0;
	int vector[TAMANIO_VEC];
	omp_set_num_threads(TAMANIO_VEC);
	/*Se carga el vector*/
	carga_vector(vector);

	#pragma omp parallel private(hilo, i, suma) shared(cant_multiplos)
	{
		hilo = omp_get_thread_num();
		switch(hilo) {
			case 0:
				if (vector[hilo-1] % vector[hilo] == 0) {
					#pragma omp critical
					cant_multiplos++;
				}
				break;
			case (TAMANIO_VEC-1):
				if (vector[TAMANIO_VEC-2] % vector[TAMANIO_VEC-1] == 0) {
					#pragma omp critical
					cant_multiplos++;
				}
				break;
			default:
				suma = vector[hilo-1] + vector[hilo+1];
				if (suma % vector[hilo] == 0) {
					#pragma omp critical
					cant_multiplos++;
				}
				break;
		}
	}

	std::cout<<"Vector generado: "<<std::flush;
	imprimir_vector(vector);
	std::cout<<"Cantidad de multiplos detectados: "<<cant_multiplos<<std::endl;
}
