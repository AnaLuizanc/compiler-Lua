
ponto_t = {}
ponto_t.__index = ponto_t

function ponto_t:new(x, y)
    local obj = {
        x = x,
        y = y
    };
    setmetatable(obj, ponto_t)
    return obj
end

triangulo_t = {}
triangulo_t.__index = triangulo_t

function triangulo_t:new(a, b, c, cor)
    local obj = {
        a = a,
        b = b,
        c = c,
        cor = cor
    }
    setmetatable(obj, triangulo_t)
    return obj
end

function func(v, n, T)
    if n<=0
        then return 1.0
    elseif n==1
        then return 1.01 + v[1].x / 1.e2 + v[1].y / 0.1e-2 - T.a.x * T.a.x + T.b.y*T.c.x
    end
    local res = 0.25e-13
    i = n-1
    while i >= 1 and v[i].x > 0 do
        temp = v[i].y * v[i].x % 123
        if (temp < 0.0)
            then res = res - res*2.e-2 +  func(v, n-1, T) * temp - T.a.y*T.cor
        else
            res = res + res*0.3e3 +func(v, n-2, T) * temp + T.c.x*T.cor
            print("Estranho, ne?\n")
        end
        i = i-1
    end
    return res
end

function F2(T)
    local A = 0
    soma = {}
    if (T.a.x >= 10 or T.b.y > 20 or T.a.y < 30 or T.b.x <= 50) and (not(T.c.x ~= 90 or T.c.y == 0))
        then return 10 % 3
    else
        A = 1
    end

    while A < 10 do
        local total = 0
        total = total + T.c.x * T.c.y;
        total = total + T.b.x * T.a.y;
        total = total + T.a.x * T.b.y;
        soma[A] = total % 100;
        A = A + 1;
    end
end
