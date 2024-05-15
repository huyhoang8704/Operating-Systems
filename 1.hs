-- import Data.Bits (abs)
abs :: Int -> Int
abs x = if x < 0 then -x else x

a = [1..5]
firstRest :: [Int] -> (Int, [Int])
firstRest [x] = (x, [])
firstRest (x:xs) = (x, xs)
--  firstRest [1..5] => (1,[2,3,4,5])
abc :: [Int] -> Int
abc (x:_) = x

-- ! Lambda Expression
-- Create Function need three things : name func , name para , operator

addTheer = \x -> x + 3 -- 8
add = \x y -> x + y
-- (\x -> x+1) 4  => 5
-- (\x y z ->x+y+z) 1 2 3

-- ! Nhân 2 với mảng
double :: [Int] -> [Int]
double xs = [x * 2 | x <- xs]  -- List comprehension

lst = [1..5]
result lst = map double lst