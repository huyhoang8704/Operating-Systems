-- ! Type
type Pos = (Int,Int)
origin :: Pos
origin = (0,0)
left :: Pos -> Pos
left (x,y) = (x-1,y)  -- (5,4) -> (4,4)
-- ! Data
data Answer = Yes | No | Unknown
