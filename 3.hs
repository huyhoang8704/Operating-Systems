-- ! Recursive
fac 0 = 1
fac n = n * fac(n-1)

-- ? recursive tính length của list
size [] = 0
size (x:xs) = 1 + size xs
-- ? reverse with recursive
reverse [] = []
reverse (x:xs) = reverse xs ++ [x]