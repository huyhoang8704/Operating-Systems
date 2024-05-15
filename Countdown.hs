-- ! Formalising The Problem (Công Thức Hóa Vấn Đề)
-- ?Hàm choices để trả về tất cả các cách chọn các phần tử từ một danh sách:
choices :: [a] -> [[a]]
choices []     = [[]]
choices (x:xs) = [x:ys | ys <- choices xs] ++ choices xs

-- ? Hàm values để lấy tất cả các giá trị trong một biểu thức:
values :: Expr -> [Int]
values (Val n)     = [n]
values (App _ l r) = values l ++ values r

-- ? Hàm solution để kiểm tra một biểu thức có phải là giải pháp cho bài toán:
solution :: Expr -> [Int] -> Int -> Bool
solution e ns n = elem (values e) (choices ns) && eval e == [n]


-- ! Brute Force Solution (Giải Pháp Dùng Sức Mạnh Thô)
-- ? Hàm split để chia một danh sách thành hai phần không rỗng:
split :: [a] -> [([a], [a])]
split []     = []
split [_]    = []
split (x:xs) = ([x], xs) : [(x:ls, rs) | (ls, rs) <- split xs]

-- ? Hàm exprs để trả về tất cả các biểu thức có giá trị là một danh sách các số cho trước:
exprs :: [Int] -> [Expr]
exprs []  = []
exprs [n] = [Val n]
exprs ns  = [e | (ls, rs) <- split ns, l <- exprs ls, r <- exprs rs, e <- combine l r]

-- ? Hàm combine để kết hợp hai biểu thức bằng mỗi phép toán:
combine :: Expr -> Expr -> [Expr]
combine l r = [App o l r | o <- [Add, Sub, Mul, Div]]

-- ? Hàm solutions để tìm tất cả các biểu thức giải bài toán:
solutions :: [Int] -> Int -> [Expr]
solutions ns n = [e | ns' <- choices ns, e <- exprs ns', eval e == [n]]


-- ! Hiệu năng
-- ? Hàm results tạo ra tất cả các biểu thức có thể từ một danh sách các số và trả về cả biểu thức và giá trị của nó nếu hợp lệ.
results :: [Int] -> [Result]
results []  = []
results [n] = [(Val n, n) | n > 0]
results ns  = [res | (ls, rs) <- split ns, lx <- results ls, ry <- results rs, res <- combine' lx ry]

-- ? Hàm combine' kết hợp hai kết quả thành các biểu thức mới và kiểm tra tính hợp lệ của chúng.
combine' :: Result -> Result -> [Result]
combine' (l, x) (r, y) = [(App o l r, apply o x y) | o <- [Add, Sub, Mul, Div], valid o x y]

-- ? Hàm solutions' tìm tất cả các biểu thức giải bài toán với hiệu năng tốt hơn bằng cách sử dụng results.
solutions' :: [Int] -> Int -> [Expr]
solutions' ns n = [e | ns' <- choices ns, (e, m) <- results ns', m == n]

-- Phương pháp tối ưu hóa này cho phép giảm đáng kể số lượng biểu thức cần xem xét, dẫn đến tốc độ tìm 
-- kiếm giải pháp nhanh hơn nhiều. Việc kết hợp quá trình tạo và đánh giá biểu thức giúp loại bỏ các biểu thức 
-- không hợp lệ ngay từ sớm, đồng thời tối ưu hóa dựa trên tính chất toán học giúp giảm không gian tìm kiếm.
