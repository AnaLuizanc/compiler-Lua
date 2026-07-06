function f():int
    local a:int
    local b:int
    local c:int
    local d:int
    a = 10
    b = 25
    c = 17
    d = b * b - 4 * a * c
    return d
end

function f(a:int, b:int, c:int):int
    local d:int
    d = b * b - 4 * a * c
    return d
end

function f(a:int, b:int, c:int):int
    local d:int
    d = b * b - 4 * a * c
    return d
end

function F4():int
    local x:int
    x = 10
    x = x + 5
end

function F5():int
    local x:int
    x = 5
    local y:int
    y = 0
    if x > 2 then
        y = 1
    end
end

function F6():int
    local x:int
    x = 4
    local y:int
    if x < 3 then
        y = 0
    else
        y = 1
    end
end

function F7():int
    local i:int
    i = 0
    local sum:int
    sum = 0
    while i < 5 do
        sum = sum + i
        i = i + 1
    end
end

function F8():int
    local i:int
    local total:int
    total = 0
    i = 0
    while i < 4 do
        total = total + i
        i = i + 1
    end
end

function F9():int
    local r:int
    r = square(5)
end

function fact(n:int):int
    if n <= 1 then
        return 1
    end
    return n * fact(n - 1)
end

function F11():int
    local a:int
    a = 1
    local b:int
    b = 0
    local result:int
    result = a and b
end

function F12():int
    local x:int
    x = 5
    do
        local x:int
        x = 10
        x = x + 1
    end
end

function F13(a:int):int
    local x:int
    x = a
    x = x + 5
end

function F14(x:int):int
    local y:int
    y = 0
    if x > 2 then
        y = 1
    end
end

function F15(x:int):int
    local y:int
    if x < 3 then
        y = 0
    else
        y = 1
    end
end

function F16(limit:int):int
    local i:int
    i = 0
    local sum:int
    sum = 0
    while i < limit do
        sum = sum + i
        i = i + 1
    end
end

function F18(max:int):int
    local i:int
    local total:
    total = 0
    i = 0
    while i < max do
        total = total + i
        i = i + 1
    end
end

function F19(a:int):int
    local r:int
    r = square(a)
end

function F20(a:int, b:int, c:int):int
    local x:int
    x = a + b + c
    x = x + 5
end

function F21(x:int, y:int, z:int):int
    local r:int
    r = 0
    if x > y + z then
        r = 1
    end
end

function F22(a:int, b:int, c:int):int
    local flag:int
    if a < b + c then
        flag = 0
    else
        flag = 1
    end
end

function F23(start:int, limit:int, step:int):int
    local i:int
    i = start
    local total:int
    total = 0
    while i < limit do
        total = total + i
        i = i + step
    end
end

function F24(from:int, to:int, step:int):int
    local i:int
    local product:int
    product = 1
    i = from
    while i < to do
        product = product * i
        i = i + step
    end
end

//TODO: REVISAR AQUI
function F25(val:int, times:int, factor:int):int
    local i:int = 0
    local result:int = val
    repeat
    result = result * factor
    i = i + 1
    until i >= times
end

function power(base:int, exp:int):int
    if exp == 0 then
        return 1
    end
    return base * power(base, exp - 1)
end

function F27(base:int, exp:int, offset:int):int
    local result:int
    result = power(base, exp) + offset
end

function F28(n:int, a:int, b:int):float
    local sum:float
    sum = 0
    
    if n <= 0 then
        return 0
    end
    
    if a > b then
        sum = a - b
    else
        sum = b - a
    end
    
    while n > 0 do
        sum = sum + n
        n = n - 1
    end
    
    local i:int
    i = 0
    while i < 3 do
        sum = sum + i
        i = i + 1
    end
    
    if sum > 10 then
        return F50(sum / 3, a, b)
    end
    
    return sum
end

function F50(n:int, a:int, b:int):float
    local sum:float
    sum = 0
    local temp:float
    temp = (a * b) - (a + b) / 2
    
    if (n % 2 == 0) and (a + b > 0) then
        sum = (n * n) + (a * 2) - (b / 2)
    end
    
    if ((a * a + b * b) % 3) == 0 then
        sum = sum + (a + b) * (a - b)
    else
        sum = sum - (((a + b) * (a + b)) / (n + 1))
    end
    
    while n > 1 do
        sum = sum + (n * temp) - (n % 3) + (a + b)
        n = n - ((n % 2) + 1)
    end
    
    n = 0
    while n < 4 do
        sum = sum + (n * n) - (a - b) * (n + 1)
        n = n + 1
    end
    
    if sum > 100 then
        local r:float
        r = ((sum / 3) - F50(n + 1, a - 1, b + 2)) * 2 + (a % 3)
        sum = sum + r
    end
    
    return sum + ((a * b) % (n + 2)) - temp
end

function F50(n:int, a:int, b:int):float
    local sum:float
    sum = 0
    local temp:float
    temp = (a * b) - (a + b) / 2

    if (n % 2 == 0) and (a + b > 0) then
        local x:float
        x = (n * n) + (a * 2)
        do
            local y:float
            y = x - (b / 2)
            sum = y + helper(a, b, n)
        end
    end

    if ((a * a + b * b) % 3) == 0 then
        local y:float
        y = (a + b) * (a - b)
        do
            sum = sum + y
        end
    else
        local d:float = (((a + b) * (a + b)) / (n + 1))
        do
            sum = sum - d
        end
    end

    while n > 1 do
        local step:int
        step = (n % 3) + 1
        do
            sum = sum + (n * temp) - step + (a + b)
            n = n - ((n % 2) + 1)
        end
    end

    n = 0
    while n < 4 do
        local v:float
        v = (n * n) - (a - b) * (n + 1)
        do
            sum = sum + v
        end
        n = n + 1
    end

    if sum > 100 then
        do
            local r:float
            r = ((sum / 3) - F50(n + 1, a - 1, b + 2)) * 2 + (a % 3)
            sum = sum + r
        end
    end

    local tail:float
    tail = ((a * b) % (n + 2)) - temp
    sum = sum + tail
    return sum
end