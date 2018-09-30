/*
	NUM_HILOS=4
*/
#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char *argv[])
{
	int tamanio, id;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &tamanio);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	cout<<"¡Hola Mundo soy el proceso "<< id << " de "
					 << tamanio << endl;
	MPI_Finalize();
	return 0;
}
