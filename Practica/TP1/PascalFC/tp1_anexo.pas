program gardens1;
var
	count: integer;
process turnstile1;
var
	loop: integer;
begin
	for loop := 1 to 5 do
	begin
		count := count + 1;
	end;
end; (* turnstile1 *)
	process turnstile2;
var
	loop: integer;
begin
	for loop := 1 to 5 do
	begin
		count := count + 1;
	end;
end; (* turnstile2 *)
begin
	count := 0;
	cobegin
		turnstile1;
		turnstile2;
	coend;
	writeln('Total admitted: ',count)
end.

