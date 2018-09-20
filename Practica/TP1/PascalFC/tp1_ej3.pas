program tp1_ej3;
{
 @ Imprime una cantidad determinada de numeros pares que se encuentren
entre 0 y un limite establecido
 @param id Identificador del proceso
 @param cantidad cantidad de numeros pares a imprimir
 @param limSuperior limite establecido para el pool de numeros escogidos
}
process type pares (id : integer; cantidad : integer;
			limSuperior : integer);
	var
		cant : integer; {Cantidad de pares
				encontrados}
		par : integer; {Aux para guardar un
				numero temporalmente}
	begin
		Randomize;
		cant := 0;
		par := 0;
		while cant < cantidad do
		begin
			par:=Random(limSuperior)+1; {Se guarda el aleatorio
						     temporalmente}
			if par mod 2 = 0 then
			begin
				writeln( 'El proceso ', id, ' imprime ',par);
				cant := cant + 1;
				par:=0;
			end;
		end;
	end;
var
	p1, p2, p3 : pares;
begin
	cobegin
		p1 (1, 5, 100) ;
		p2 (2, 5, 40) ;
		p3 (3, 10, 35);
	coend;
end.

