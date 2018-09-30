/*
	NUM_PROC=4
*/
#include <iostream>
#include <mpi.h>

using namespace std;
int main(int argc, char *argv[])
{
	int tamanio, id, buzon, mensaje;
	bool realiza_envio = false;
	MPI_Status estado;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &tamanio);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);

	if (id == 0) {
		mensaje = 1000;
		MPI_Send(&mensaje, /* Mensaje a enviar */
			1, /*Cantidad de elementos*/
			MPI_INT, /* Tipo de dato del mensaje*/
			id+1, /*Proceso receptor del mensaje*/
			0, /* Etiqueta del mensaje */
			MPI_COMM_WORLD /* Comunicador */);
		cout << "Soy el proceso " << id << ", no recibo nada pero "
		<<"estoy enviando el valor "<< mensaje << " a " << id+1 << endl;
	} else {
		MPI_Recv(&buzon, /* Almacenamiento de msj */
			 1, /* Cantidad de elementos
			 	que se esta recibiendo */
			 MPI_INT, /* Tipo de dato a recibir*/
			 id-1, /* id del proceso origen */
			 0, /* Etiqueta esperada para msj */
			 MPI_COMM_WORLD, /* Comunicador utilizado */
			 &estado /* Info del estado */);
		if (id != tamanio-1) {
			mensaje = buzon+1;
			MPI_Send(&mensaje, /* Mando mensaje que recibo */
				1, /*Cantidad de elementos*/
				MPI_INT, /* Tipo de dato del mensaje*/
				id+1, /*Proceso receptor del mensaje*/
				0, /* Etiqueta del mensaje */
				MPI_COMM_WORLD /* Comunicador */);
			realiza_envio = true;
		}

		if (realiza_envio) {
			cout << "Soy el proceso " << id << ", recibi el valor "
			<< buzon <<" del proceso " << id-1<< " y estoy enviando el valor "
			<< mensaje << " al proceso " << id+1 << endl;
		} else {
			cout << "Soy el proceso " << id << ", recibi el valor "
			<< buzon <<" del proceso "<< id-1 <<" pero no tengo nada "
			<< "que enviar"<< endl;
		}
	}
	MPI_Finalize();
	return 0;
}
