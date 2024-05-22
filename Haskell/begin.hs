-- stack ghci
-- :l test.hs
double x = x*x
add x y = x + y
-- add (double 5) (double 3)

-- ! Hàm hằng a = 5
-- ! List
a = [1..5]
b = [6..10]
-- a ++ b : merge 2 list
-- head a : lấy ra phần tử đầu
-- last a : lưu ra phần tử cuối
-- tail a : lưu ra phần tử sau phần tử đầu [2,3,4,5]
-- init a : lưu ra phần tử trước phần tử cuối [1,2,3,4]
-- a !! 2 : lưu ra phần tử index = 2
-- length a : lấy ra số phần tử
-- reverse a : Đảo ngược
-- xs = [x*2 | x <- [1..10]] -- [2,4,6,8,10,12,14,16,18,20]
-- xs = [(a,b,c) | c<- [1..10], b<- [1..10] , a<- [1..10] , a + b + c == 24 , a^2 + b^2 == c^2] 

-- ! Bài 2
-- Function to double a number
double :: Int -> Int
double x = x * 2

-- Sample list of numbers
numbers = [1, 3, 5, 7]

-- Apply double to each element in numbers using map
doubledNumbers = map double numbers

print doubledNumbers  -- Output: [2,6,10,14]