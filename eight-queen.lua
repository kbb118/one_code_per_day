-- The Eight Queen Puzzle

--[[
各行に1つしかクイーンを置けないから
要素数8の配列で各行のクイーンが何列目にあるかを表すことができる。
--]]

-- (i,j)にあるとき(j,j),(i+a,j+a),(i-a,j-a)には置けない

N = 8 -- board size

function laceok(board, i, j)
    for k = 1, i - 1 do
        io.write(k, "行目", j,"列チェック")
        if board[k] == j then
            io.write("縦あうと\n")
            return false
        elseif board[k] == j - (i - k) then
            io.write("左ななめアウト\n")
            return false
        elseif board[k] == j + (i - k) then
            io.write("みぎななめアウト\n")
            return false
        end
    end

    io.write(i, "行目", j,"列に置けた\n")
    return true
end

function printsolution (board)
    for i = 1, N do
        io.write(board[i])
        for j = 1, board[i]-1 do
            io.write(" ")
        end
        io.write("x\n")
    end
    io.write("\n")
end

function solveeightqueen(a)
    board = {a}
    for i = 2, N do
        for j = 1, N do
           if isplaceok(board, i, j) then
               board[i] = j
               break
           elseif j == N then
               print("fuck!!")
               i = i - 2
               j = board[i] + 1
           end
        end
    end
    printsolution(board)
end

-- solveeightqueen(3)

function isplaceok(a, n, c)
    for i = 1, n - 1 do
        if (a[i] == c ) or
            (a[i] - i == c - n) or
            (a[i] + i == c + n) then
            return false
        end
    end
    return true
end

function addqueen(a, n)
    if n > N then
        printsolution(a)
    else
        for c = 1, N do
            if isplaceok(a, n, c) then
                a[n] = c
                addqueen(a, n+1)
            end
        end
    end
end

addqueen({},1)
