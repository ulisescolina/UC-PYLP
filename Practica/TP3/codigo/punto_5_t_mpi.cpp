/*
	NUM_PROC=8
*/
#include "mpi.h"
#include <stdio.h>
using namespace std;

int main (int argc, char *argv[]) {
	int 	numtasks, rank,
		next, prev,
		r_next, r_prev,
		msj_forward=100, bzn_forward,
		r_msj_forward=200, r_bzn_forward,
		tag=1, r_tag=2;
	MPI_Status estado, r_estado;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/*Se definen los vecinos*/
	next = rank+1;
	r_prev = rank+1;
	if (rank == (numtasks-1)){
		next=0;
		r_prev=0;
	}
	prev = rank-1;
	r_next = rank-1;
	if (rank == 0){
		prev=numtasks-1;
		r_next=numtasks-1;
	}
	/*Se envian/reciben los mensajes*/
	/*         Ascendentes          */
	MPI_Send(&msj_forward, 1, MPI_INT, next, tag,
			MPI_COMM_WORLD);
	MPI_Recv(&bzn_forward,1,MPI_INT,prev,tag,
			MPI_COMM_WORLD,&estado);

	/*Se envian/reciben los mensajes*/
	/*         Descendentes         */
	MPI_Send(&r_msj_forward,1,MPI_INT,r_next,r_tag,
			MPI_COMM_WORLD);
	MPI_Recv(&r_bzn_forward,1,MPI_INT,r_prev,r_tag,
			MPI_COMM_WORLD,&r_estado);

	cout << "Soy "<<rank<<" y recibi"
	<<" el msj "<<bzn_forward<<" de "
	<<estado.MPI_SOURCE<<", ademas, "
	<<"recibi el msj "<<r_bzn_forward
	<<" de "<<r_estado.MPI_SOURCE<<endl;

	MPI_Finalize();
	return 0;

}
