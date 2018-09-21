program gardens1;
var
	count: integer;
	s : semaphore;
process turnstile1(var s:semaphore);
var
	loop: integer;
begin
	for loop := 1 to 5 do
	begin
		wait(s);
		count := count + 1;
		signal(s);
	end;
end; (* turnstile1 *)

process turnstile2(var s:semaphore);
var
	loop: integer;
begin
	for loop := 1 to 5 do
	begin
		wait(s);
		count := count + 1;
		signal(s);
	end;
end; (* turnstile2 *)

begin
	initial(s,1);
	count := 0;
	cobegin
		turnstile1(s);
		turnstile2(s);
	coend;
	writeln('Total admitted: ',count)
end.

