function testeParametros(x:int):int
    local a:int
    local b:int
    local c:int
    local d:int
    a = 1
    b = 2
    c = 3
    d = 4
    a = funcMenor(a, b)
    d = funcMaior(a, b, c, d)
    return d
end