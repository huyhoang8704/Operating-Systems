data Number = N Int deriving Show
data Op = Add | Sub | Mul | Div

apply :: Op -> Number -> Number -> Number
apply Add (N x) (N y) = N (x + y)
apply Sub (N x) (N y) = N (x - y)
apply Mul (N x) (N y) = N (x * y)
apply Div (N x) (N y) = N (x `div` y)


-- isValid :: Expression -> Bool
-- isValid (Add n1 n2) = True
-- isValid (Sub n1 n2) = n1 >= n2
-- isValid (Mul n1 n2) = n1 /= 0 && n2 /= 0
-- isValid (Div n1 n2) = n2 /= 0

main :: IO ()
main = do
    let resultAdd = apply Add (N 5) (N 3)
    let resultSub = apply Sub (N 10) (N 4)
    let resultMul = apply Mul (N 6) (N 7)
    let resultDiv = apply Div (N 20) (N 5)
    print resultAdd  -- Output: N 8
    print resultSub  -- Output: N 6
    print resultMul  -- Output: N 42
    print resultDiv  -- Output: N 4
