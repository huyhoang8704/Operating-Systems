separateSigns :: [Int] -> ([Int], [Int])
separateSigns lst = (negative, positive)
    where
        negative = [a | a <- lst, a < 0]
        positive = [b | b <- lst, b > 0]

daysInMonth :: Int -> Int -> Int
daysInMonth a b = if a == 2 then if checking then 29 else 28 else if a `elem` [1, 3, 5, 7, 8, 10, 12] then 31 else 30
    where checking = if b `mod` 4 == 0 then if b `mod` 100 == 0 then if b `mod` 400 == 0 then True else False else True else False

transform :: [Int] -> [Int]
transform lst = map (*3) [x | x <- lst , even x]

specialNumbers :: [Int]
specialNumbers = [x |x <- [1..100], x `mod` 7 == 0 , x `mod` 5 /= 0 ]

pairsWithSum :: Int -> [Int] -> [(Int, Int)]
pairsWithSum total xs = [(x, y) | x <- xs, y <- xs, x + y == total]
