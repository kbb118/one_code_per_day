-- this is single line comment
print("hello, world!")
--[[
 this is multi line comment
]]

-- define a factorial function
function fact(n)
    if n == 0 then
        return 1
    else
        return n * fact(n-1)
    end
end

print('enter a number')
a = io.read("*n")
print(fact(a))
