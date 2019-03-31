-- ナイト巡回問題

-- 盤面の大きさ N 行 M 列
N = 8
M = 8

-- 初期位置の行番号と列番号
INI_ROW = 2
INI_COL = 2 

-- すべてのマスがfalseかつ初期位置に戻れる場合クリア
function check_all(brd, row, col)
    for i=1,N do
        for j=1,M do
            if brd[i][j] then
                return false
            end
        end
    end
    
    if ((row+2 == INI_ROW) and (col+1 == INI_COL)) or
       ((row+1 == INI_ROW) and (col+2 == INI_COL)) or
       ((row+2 == INI_ROW) and (col-1 == INI_COL)) or
       ((row+1 == INI_ROW) and (col-2 == INI_COL)) or
       ((row-2 == INI_ROW) and (col+1 == INI_COL)) or
       ((row-1 == INI_ROW) and (col+2 == INI_COL)) or
       ((row-2 == INI_ROW) and (col-1 == INI_COL)) or
       ((row-1 == INI_ROW) and (col-2 == INI_COL)) then
        return true
    else
        return false
    end
end

function print_ans(ans, ans_index)
    for i=1, ans_index do
        io.write(i, "回目の移動", ans[i], "時の方向\n") 
    end
end

-- 再帰関数
-- col, row の位置から、行けるパターンすべて試す
function move_night(brd, row, col, ans, ans_index)
    if check_all(brd, row, col) then
        io.write("クリア\n")
        print_ans(ans, ans_index)
        return true
    end

    brd[row][col] = false
    ans_index = ans_index + 1

    for i=-2, 2 do
        if i ~= 0 then
            for j=-2,2 do
                if (j ~= 0) and (i ~= j) and (i ~= -j) then
                    if (row+i > 0) and (row+i < N+1) and
                        (col+j > 0) and (col+j < M+1) and
                        (brd[row+i][col+j]) then
                        move_night(brd, row+i, col+j, ans, ans_index)
                    end
                end
            end
        end
    end
    brd[row][col] = true
end

function init()
    brd = {}
    for i=1,N do
        brd[i] = {}
        for j=1,M do
            brd[i][j] = true
        end
    end
    return brd
end

function init_ans()
    ans = {}
    for i=1,N*M do
        ans[i] = 0
    end
    return ans
end

brd = init()
ans = init_ans()
ans_index = 1
move_night(brd, INI_ROW, INI_COL, ans, ans_index)
