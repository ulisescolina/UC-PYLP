program diapositiva10;

function sumar(a, b:integer):integer;
begin
	sumar:=a+b;
end;

function multiplicar(a, b:integer):integer;
begin
	multiplicar:=a*b;
end;

process type mescalar (v1: array of integer, v2 : array of integer);
var 
	i : integer;
begin
	if (length(v1) = length(v2)) then
	begin
		for i := 0 to length(v1) do
		   res := res + multiplicar(v1[i], v2[i]);
	end
	else writeln('El tamanio de los vectores debe ser igual');
end;

var
	res : integer ;
	p1 : mescalar ;
	p2 : mescalar ;
	p3 : mescalar ;
	p4 : mescalar ;
begin
	res := 0;
	cobegin
		res := res + p1([1,2],[3,4]);
		res := res + p2([5,6],[7,8]);
		res := res + p3([9,10],[11,12]);
		res := res + p4([13,14],[15,16]);
	coend;
end.
{program print ;
process type print (i : integer);
begin
write( 'Soy el proceso ', i);
end;
var
p1 , p2 : print ;
begin
cobegin
p1 (1) ;
p2 (2) ;
coend ;
end.}
