/*
	NUM_PROC=8
*/
#include "mpi.h"
#include <stdio.h>
using namespace std;

int main (int argc, char *argv[]) {
	int 	numtasks,
		rank,
		next,
		prev,
		msj_forward=100,
		bzn_forward,
		tag=1;
	MPI_Status estado;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/*Se definen los vecinos*/
	next = rank+1;
	if (rank == (numtasks-1))
		next=0;

	prev = rank-1;
	if (rank == 0)
		prev=numtasks-1;

	/*Se envian los mensajes*/
	MPI_Send(&msj_forward,
		1,
		MPI_INT,
		next,
		tag,
		MPI_COMM_WORLD);

	/*Se reciben los mensajes*/
	MPI_Recv(&bzn_forward,
		1,
		MPI_INT,
		prev,
		tag,
		MPI_COMM_WORLD,
		&estado);

	cout << "Soy "<<rank<<" y recibi"
	<<" el msj "<<bzn_forward<<" de "
	<<estado.MPI_SOURCE<<endl;

	MPI_Finalize();
	return 0;

}
