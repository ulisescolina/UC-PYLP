program tp1_ej3;
const
	tamanio = 10;
	MAX_RANDOM  = 51;
type
	vector = array[1..tamanio] of integer;

{Carga el vector arr con valores aleatorios}
procedure cargarVector(var arr : vector);
var
	i: integer;
begin
	Randomize;
	for i:=1 to tamanio do
	begin
		arr[i] := Random(MAX_RANDOM);
	end
end;

{Utilidad que permite imprimir el vector arr}
procedure imprimir(arr : vector; id : integer);
var
	i: integer;
begin
	write('V', id, ': [');
	for i:=1 to tamanio-1 do
	begin
		write(arr[i],', ');
	end;
	write(arr[i],']');
	writeln;
end;

{Realiza la parte de la multiplicacion}
process type multiplicar (
			id : integer;
			var vec1 : vector;
			var vec2 : vector;
			p_ini : integer;
			p_fin : integer;
			var pescalar : integer
		   );

var
	suma, producto, i : integer;
begin
	suma := 0;
	for i:=p_ini to p_fin do
	begin
		producto := 0;
		producto := vec1[i]*vec2[i];
		suma := suma + producto;
	end;
	pescalar := pescalar + suma;
end;
var
	p1, p2, p3, p4, p5 : multiplicar;
	productoEscalar : integer;
	vec1, vec2: vector;
begin
	productoEscalar := 0;
	cargarVector(vec1);
	cargarVector(vec2);
	imprimir(vec1, 1);
	imprimir(vec2, 2);
	cobegin
	  p1 (1, vec1, vec2, 1, 2, productoEscalar);
	  p2 (2, vec1, vec2, 3, 4, productoEscalar);
	  p3 (3, vec1, vec2, 5, 6, productoEscalar);
	  p4 (4, vec1, vec2, 7, 8, productoEscalar);
	  p5 (5, vec1, vec2, 9, 10, productoEscalar);
	coend;
	writeln('El producto escalar de los vectores
		proporcionados es: ', productoEscalar);
end.

