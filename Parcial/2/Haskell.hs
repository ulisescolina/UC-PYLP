-- Ejercicio 1.a: Programa que recibe una tupla (x, n) y devuelve una lista con 'n' multiplos de 'x'.
n_multiplos :: (Integer, Integer) -> [Integer]
n_multiplos (x, 1) = [x]
n_multiplos (x, n) = x*n:n_multiplos(x,n-1)

-- Ejercicio 1.b: Programa que dada una oracion, devuelva la cantidad de vocales
es_vocal :: Char -> Bool
es_vocal(c) = c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
c_vocales :: [Char] -> Integer
c_vocales [] = 0
c_vocales (x:xs) = if es_vocal(x) then 1 + c_vocales(xs) else c_vocales(xs)
