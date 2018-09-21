program tp1_ej4;
{
 @return true si el valor de numero es primo
 @return false si el valor de numero no es primo
}
function esprimo(numero : integer):boolean
var
	cantDiv : integer;
	i : integer;
begin
	for i:=2 to numero-1 do
	begin
		if (numero mod i = 0) then
		begin
			cantDiv:=cantDiv+1;
		end;
	end;
	esprimo := (cantDiv = 0);
end;

{
 Evalua un rango de numeros y devuelve los numeros
   primos dentro del rango.
 @param id Identificador del proceso.
 @param limInferior limite establecido para el valor
                    inferior del intervalo.
 @param limSuperior limite establecido para el valor
                    superior del intervalo.
}
process type primos (
			id : integer;
			limInferior : integer;
			limSuperior : integer;
			var s : semaphore
		    );
	var
		i : integer; {Indice para recorrer}
	begin
		for i:=limInferior to limSuperior do
		begin
			if (esprimo(i)) then
			begin
				wait(s);
				writeln('El proceso ',id,
					' encontro a: ', i);
				signal(s);
			end;
		end;
	end;
var
	p1, p2, p3, p4 : primos;
	s : semaphore;
begin
	initial(s,1);
	cobegin
		p1 (1, 1, 25, s);
		p2 (2, 26, 50, s);
		p3 (3, 51, 75, s);
		p4 (4, 76, 100, s);
	coend;
end.

