program tp1_ej2;

process type print (id : integer);
	begin
		writeln( 'ID de proceso: ', id);
	end;
var
	p1, p2 : print ;
begin
	cobegin
		p1 (1) ;
		p2 (2) ;
	coend;
end.

