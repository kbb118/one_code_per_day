-- 再帰関数を作るとき
-- 再帰呼出しをしないケースをつくる
-- 条件を変えながら再帰呼出しする
-- 再帰が深くなると、いつかは上のケースに行き当たる

function factorial(n)
    if (n == 0) then
        return 1
    else
        return n * factorial(n-1)
    end
end

print(factorial(6)) --> 720

function fibonacci(n)
    if (n == 0) then
        return 0
    elseif (n == 1) then
        return 1
    else
        return fibonacci(n-1) + fibonacci(n-2) 
    end
end

print(fibonacci(10)) -- フィボナッチ数列の11番目の項は?

-- 1 から n までの自然数の和を求める関数
function sum(n)
    if (n == 0) then
        return 0
    else 
        return n + sum(n-1)
    end
end

print(sum(10)) --> 55

-- N 個の数値の和の組み合わせで M と等しくなるのはいくつ？
N = 6
data = {1, 2, 2, 3, 5, 6}
M = 11
function f(n, sum)
    if (n > N) then
        if (sum == M) then
            return 1
        else
            return 0
        end
    end

    return f(n+1, sum + data[n]) + f(n+1, sum)
end

print(f(1,0)) 
