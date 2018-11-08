-- Punto 1: Funcion que devuelve el doble de un numero.
doble :: Integer  -> Integer
doble x = x*2

-- Punto 2: Funcion recursiva que devuelve el factorial de un numero.
factorial :: Integer -> Integer
factorial x = if x==1 then 1 else x * factorial(x-1)

-- Punto 3: Modificar la funcion anterior aplicando ajuste de patrones.
factorial_ap 1 = 1
factorial_ap x = x * factorial_ap(x-1)

-- Punto 4: Funcion que calcule la potencia de un numero.
potencia x y = x ^ y

---- Punto 4 con tuplas
potencia_t :: (Integer, Integer) -> Integer
potencia_t (x, y) = x ^ y

---- Punto 4 en forma recursiva
potencia_r :: (Integer, Integer) -> Integer
potencia_r (x, y) = if y==1 then x else x * potencia_r(x, y-1)

-- Punto 5: Funcion que devuelva un booleano indicando si un numero pasado como parametro es par.
es_par :: Integer -> Bool
es_par x = x `rem` 2 == 0

-- Punto 6: Investigue la importancia de las Listas
--

-- Punto 7: Dada una lista de enteros devuelva la cantidad de elementos
tamanio_lista :: [Int] -> Int
tamanio_lista [x] = length [x]

---- Punto 7 ( clase )
tamanio_lista_c :: [a] -> Integer
tamanio_lista_c [] = 0
tamanio_lista_c (x:xs) = 1 + tamanio_lista_c(xs)

