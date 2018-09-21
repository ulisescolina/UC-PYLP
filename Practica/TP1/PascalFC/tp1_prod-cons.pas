program tp1_prod_cons;
var
	inp, out: channel of char;

process buffer;
const
	buffmax = 1;
var
	store: array[0..buffmax] of char;
	nextin, nextout, count: integer;
begin
	nextin := 0;
	nextout := 0;
	count := 0;
	repeat
		select
		when count <> 0 =>
			out ! store[nextout];
			count := count - 1;
			nextout := (nextout + 1) mod (buffmax + 1);
		or
		when count < buffmax =>
			inp ? store[nextin];
			count := count + 1;
			nextin := (nextin + 1) mod (buffmax + 1 );
		end (* select *)
	forever
end; (* buffer *)

process producer;
var
	local: char;
begin
	for local := 'a' to 'z' do
		inp ! local
end; (* producer *)

process consumer;
var
	local: char;
begin
	repeat
		out ? local;
		write(local);
	until local = 'z';
	writeln
end; (* consumer *)

begin
	cobegin
		producer;
		consumer;
		buffer
	coend
end.
