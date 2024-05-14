-- import Data.Bits (abs)
abs :: Int -> Int
abs x = if x < 0 then -x else x

a = [1..5]
firstRest :: [Int] -> (Int, [Int])
firstRest [x] = (x, [])
firstRest (x:xs) = (x, xs)

--  firstRest [1..5] => (1,[2,3,4,5])

-- ! Lambda Expression
addThree = \x -> x + 3 -- 8
