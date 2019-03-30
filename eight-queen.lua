-- The Eight Queen Puzzle

--[[
各行に1つしかクイーンを置けないから
要素数8の配列で各行のクイーンが何列目にあるかを表すことができる。
--]]

-- (i,j)にあるとき(j,j),(i+a,j+a),(i-a,j-a)には置けない

N = 8 -- board size

function isplaceok(brd, row, pos)

    -- row 以下の行をすべて調べる
    for i=1,row-1 do
        -- 1,row-1 に pos があったらだめ
        if (brd[i] == pos) or 
           (brd[i] == pos - row + i ) or
           (brd[i] == pos + row - i ) then
           return false
        end
    end

    -- 置ける
    return true
end

-- 8x8 のbrd の row 行目にクイーンを配置する
-- 再帰関数
function addqueen(brd, row)
    if row == N+1 then
        return true
    end

    -- row のどこに置けるか順に確かめる 
    for pos=1,N do 
        -- 条件を満たしたら置く。
        if isplaceok(brd, row, pos) then
            brd[row] = pos
            if addqueen(brd, row+1) then
                return brd -- ここでリターンする＝＝最初に見つけた答えだけ出す
            end
        end
    end
    
    -- 置ける場所がなかった。
    return false
end

SOLCNT = 1

function printbrd(brd)
    io.write("solution ", SOLCNT, "\n")
    for i=1,N do
        for j=1,N do
            io.write(brd[i] == j and "X" or "-", " ")
        end
        io.write("\n")
    end
    io.write("\n")
    SOLCNT=SOLCNT+1
end

function main()
    printbrd(addqueen({},1))
end

main()
