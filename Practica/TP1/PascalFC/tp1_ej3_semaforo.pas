program tp1_ej3_semaforo;
{
 Imprime una cantidad determinada de numeros
 pares que se encuentren entre 0 y un limite
 establecido
 @param id Identificador del proceso
 @param cantidad cantidad de numeros pares a
  imprimir
 @param limSuperior limite establecido para
  el pool de numeros escogidos
}
process type pares (
			id : integer;
			cantidad : integer;
			limSuperior : integer;
			var s : semaphore
		   );
var
	cant : integer;
	par : integer;
begin
	Randomize;
	cant := 0;
	par := 0;
	while cant < cantidad do
	begin
		par:=Random(limSuperior)+1;
		if par mod 2 = 0 then
		begin
			wait(s);
			writeln( 'El proceso ',
		  		id, ' imprime ',par);
			signal(s);
			cant := cant + 1;
	  		par:=0;
		end;
	end;
end;
var
	p1, p2, p3 : pares;
	s : semaphore;
begin
	initial(s, 1);
	cobegin
		p1 (1, 5, 100, s) ;
		p2 (2, 5, 40, s) ;
		p3 (3, 10, 35, s);
	coend;
end.

