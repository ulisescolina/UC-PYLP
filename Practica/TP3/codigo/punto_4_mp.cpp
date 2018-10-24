#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <random>

const int TAMANIO_VEC=3;
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
	std::cout << "["<<std::flush;
	for (i; i <= TAMANIO_VEC-2;i++) {
	std::cout<<vec[i]<< ", "<<std::flush;
	}
	std::cout<<vec[TAMANIO_VEC-1]<<"]"<<std::endl;
}

int main(){
	int hilo, inicio, fin, total=0, salto=0, i;
	int vec1[TAMANIO_VEC], vec2[TAMANIO_VEC];
	int pescalar;

	omp_set_num_threads(3);
	#pragma omp parallel
	{
		#pragma omp for schedule(static, 2)
		for (i=0; i<TAMANIO_VEC; i++) {
			vec1[i] = i;
			vec2[i] = i;
		}
	}

	#pragma omp parallel private(hilo, inicio, fin)
	{
		hilo=omp_get_thread_num();
		salto=TAMANIO_VEC/omp_get_num_threads();
		inicio=hilo*salto;
		fin=inicio+salto;
		#pragma omp parallel for
		for (i=inicio; i<fin; i++) {
			total += vec1[i] * vec2[i];
		}
	}

	std::cout<<"V1: "<<std::flush;
	imprimir_vector(vec1);
	std::cout<<"V2: "<<std::flush;
	imprimir_vector(vec2);
	std::cout<<"Producto escalar: "<<total<<std::endl;
}
