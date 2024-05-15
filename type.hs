add :: Int -> Int -> Int
add x y = x + y
factorial n = product [1..n] -- Giai thừa

ghci> :t 'a'
'a' :: Char , 'abc' -> error , "abc" -> string


ghci> :t True
True :: Bool

ghci> :t (True, 'a')
(True, 'a') :: (Bool, Char)

:t ['a', 'b', 'c'] :: [char]

:t [tail , reverse] :: [[a] -> [a]]


ghci> :t 4 == 5
4 == 5 :: Bool