function multiplicar(a:int, b:int) :int
    local temp:int
    temp = a * b
    return temp
end

function principal(x:int) :int
    local y:int
    local resultado:int  
    y = 10
    resultado = multiplicar(x, y) + 5
    return resultado
end