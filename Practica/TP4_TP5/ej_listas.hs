-- En este archivo se van detallando los ejemplos que fuimos haciendo en clases
---- para practicar las diferentes singularidades que aparecen en el tratamiento de
---- las listas en Haskell

-- Imprimir un caracter una cierta cantidad de veces.
imprimir :: (Char, Integer) -> [Char]
imprimir (c, i) = if i==1 then [c] else [c]++imprimir(c, i-1)

-- Imprimir la suma de los elementos de una lista.
sumar_lista :: [Integer] -> Integer
sumar_lista([]) = 0
sumar_lista(x:xs) = x + sumar_lista(xs)

-- Devolver el mayor elemento de una lista.
maximo :: [Integer] -> Integer
maximo [] = 0
maximo (x:xs) = if x > maximo(xs) then x else maximo(xs)

-- Devolver el minimo elemento de una lista.
minimo :: [Integer] -> Integer
minimo [] = 0
minimo (x:xs) = if x < minimo(xs) then x else minimo(xs)

-- Funcion filtro propuesta por Esteban en clases
-- Realizar una funcion que recibe una funcion y la aplica a cada elemento
---- de una lista luego devuelve los elementos de la lista que cumplen con
---- los criterios definidos en la funcion.

es_par :: Integer -> Bool
es_par x = x `mod` 2 == 0

filtrar f [] = [];
filtrar f (x:xs) = if f(x) then [x]++filtrar f (xs) else filtrar f (xs)

-- Funcion que dada una lista devuelve otra lista con los elementos que
---- cumplan que son mayor(es) a un valor x

--es_mayor_a x y = x < y
--filtrar_2 f [] = []
--filtrar_2 f (y:ys) = if f(y) then [y]++filtrar_2 f (ys) else filtrar_2 f (ys)
