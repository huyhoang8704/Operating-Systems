-- ! List comprehension
-- Tưởng tượng nó như vòng lặp
squaredNumbers = [x * x | x <- [1..5]]
-- [1, 4, 9, 16, 25]
-- Tính ngắn gọn , Tính lười biếng , Tính linh hoạt

-- ? Đếm số phần tử giống x trong xs
count x xs = length [x2 | x2 <- xs, x == x2]
count 's' "Mississippi" -- 4