/*
	NUM_PROC=8
*/
#include <iostream>
#include <mpi.h>

using namespace std;
int main(int argc, char *argv[])
{
	int tamanio, id, buzon, mensaje=0, i, p_destino;
	MPI_Status estado;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &tamanio);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);

	if (id == 0) {
		for (i=0; i<2; i++) {
			mensaje += 11111;
			p_destino = i+1;
			MPI_Send(&mensaje, /* Mensaje a enviar */
				1, /*Cantidad de elementos*/
				MPI_INT, /* Tipo de dato del mensaje*/
				p_destino, /*Proceso receptor del mensaje*/
				0, /* Etiqueta del mensaje */
				MPI_COMM_WORLD /* Comunicador */);
			cout << "Soy el proceso 0, estoy enviando el valor "
			<< mensaje << " al proceso " << p_destino << endl;
		}
	} else {
		if (id==1 || id==2) {
			/*Recibo el mensaje de P0*/
			/*y lo guardo en buzon*/
			MPI_Recv(&buzon, 1, MPI_INT, 0,
				0,  MPI_COMM_WORLD, &estado);
			cout<<"Soy el proceso "<<id<<" recibi el valor "
			<<buzon<<" del proceso 0."<<endl;
			for (i=id+2; i < tamanio; i+=2) {
				/*Envio los mensajes a procesos*/
				/*pares e impares*/
				MPI_Send(&buzon,1,MPI_INT,i,0,MPI_COMM_WORLD);
				cout<<"P"<<id<<": envio el valor " <<
				buzon<<" a "<<i<<endl;
			}
		} else {
			if (id % 2 != 0) {
				/*Recibo el mensaje enviado*/
				/*por el proceso P1*/
				MPI_Recv(&buzon, 1, MPI_INT, 1,
					0,  MPI_COMM_WORLD, &estado);
				cout<<"P"<<id<<": recibo el valor " <<
				buzon<<" de 1."<<endl;
			} else {
				/*Recibo el mensaje enviado*/
				/*por el proceso P2*/
				MPI_Recv(&buzon, 1, MPI_INT, 2,
					0,  MPI_COMM_WORLD, &estado);
				cout<<"P"<<id<<": recibo el valor " <<
				buzon<<" de 2."<<endl;
			}
		}
	}
	MPI_Finalize();
	return 0;
}
