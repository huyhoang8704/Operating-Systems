-- ?map: Sử dụng hàm lên list và trả về danh sách mới với các phần tử đã biến đổi.
map f xs = [f x | x <- xs]

-- ? recursion
map f [] = []
map f (x:xs) = f x : map f xs

-- ?filter: Lọc các phần tử trong ds dựa trên đk
filter even [1..10]
-- [2,4,6,8,10]

-- ? Foldr : thay thế đệ quy
foldr (+) 0 [1..3] -- 6

foldr (^) 2 [1,2,3] -- 1
--  1^(2^(3^2))
foldl (^) 2 [1,2,3] -- 1
--  ((2^1)^2)^3