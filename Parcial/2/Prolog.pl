%Alturas
altura(carlos, 1.90).
altura(maria, 1.70).
altura(roberto, 1.80).
altura(lucia, 1.56).
altura(norberto, 1.78).

%Pesos
peso(carlos, 86).
peso(maria, 66).
peso(roberto, 56).
peso(lucia, 58).
peso(norberto, 90).

imc(Altura, Peso, Vimc) :- Vimc is Peso/(Altura*Altura).


delgado(Persona) :- altura(Persona, Altura),
                    peso(Persona, Peso),
										imc(Altura, Peso, X),
										X < 18.5.

normal(Persona) :- peso(Persona, Peso),
	                 altura(Persona, Altura),
									 imc(Altura, Peso, X),
									 X > 18.5, X < 24.9.

sobrepeso(Persona) :- peso(Persona, Peso),
	                 altura(Persona, Altura),
									 imc(Altura, Peso, X),
									 X > 25, X < 30.

obeso(Persona) :- peso(Persona, Peso),
	                 altura(Persona, Altura),
									 imc(Altura, Peso, X),
									 X > 30.
