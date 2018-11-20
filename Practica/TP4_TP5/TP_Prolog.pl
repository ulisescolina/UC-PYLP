%% Punto 10: Construir construir una base del conocimiento con un conjunto de reglas y realizar consultas
% Hechos
padre(clara, pedro).
padre(pedro, jose).
padre(ana, clara).
padre(jose, clara).
padre(pepe, pepe2).

% Reglas
abuelo(X, Y) :- padre(X,Z), padre(Z,Y).
bisabuelo(X, Y) :- padre(X, Z), abuelo(Z, Y).
