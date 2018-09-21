program tp1_ej2_semaforo;

process type imprimir (
			id : integer;
			var s : semaphore
		      );
begin
	wait(s);
	writeln( 'ID de proceso: ', id);
	signal(s);
end;
var
	p1, p2 : imprimir;
	s : semaphore;
begin
	initial(s, 1);
	cobegin
		p1 (1, s) ;
		p2 (2, s) ;
	coend;
end.

