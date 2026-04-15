ponto_t = {}
ponto_t.__index = ponto_t

function ponto_t:new(x, y)
    local obj = {
        x = x,
        y = y
    }
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
    if n <= 0 then
        return 1.0
    elseif n == 1
    then
        return 1.01 + v[1].x / 1.e2 + v[1].y / 0.1e-2 - T.a.x * T.a.x + T.b.y * T.c.x
    end
    local res = 0.25e-13
    local i = n - 1
    while i >= 1 and v[i].x > 0 do
        local temp = v[i].y * v[i].x % 123
        if (temp < 0.0)
        then
            res = res - res * 2.e-2 + func(v, n - 1, T) * temp - T.a.y * T.cor
        else
            res = res + res * 0.3e3 + func(v, n - 2, T) * temp + T.c.x * T.cor
            print("Estranho, ne?\n")
        end
        i = i - 1
    end
    return res
end

function F2(T)
    local A = 0
    local soma = {}
    if (T.a.x >= 10 or T.b.y > 20 or T.a.y < 30 or T.b.x <= 50) and (not (T.c.x ~= 90 or T.c.y == 0))
    then
        return 10 % 3
    else
        A = 1
    end

    while A < 10 do
        local total = 0
        total = total + T.c.x * T.c.y
        total = total + T.b.x * T.a.y
        total = total + T.a.x * T.b.y
        soma[A] = total % 100
        A = A + 1
    end
end

function fatorialA(n)
    if (n <= 1) then
        return 1
    end
    return n * fatorialA(n - 1)
end

function fatorialB(n)
    local a = n - 1
    if (n <= 1) then
        return 1
    end
    return n * fatorialB(a)
end

function fatorialC(n, P)
    if (n <= 1) then
        return 1
    end
    return fatorialC(n - 1, P * n)
end

function fatorialD(n, P)
    local a = n - 1
    local b = P * n
    if (n <= 1) then
        return 1
    end
    return fatorialD(a, b)
end

function fatorialE(n, P)
    if (n <= 1)
    then
        return 1
    else
        local a = n - 1
        local b = P * n
        return fatorialD(a, b)
    end
end

function C1(a, b)
    if (a < b) then
        return 1
    end
    return 2
end

function C2(a, b)
    if (a <= b) then
        return 1
    end
    return 2
end

function C3(a, b)
    if (a > b) then
        return 1
    end
    return 2
end

function C4(a, b)
    if (a >= b) then
        return 1
    end
    return 2
end

function C5(a, b)
    if (a == b) then
        return 1
    end
    return 2
end

function C5(a, b)
    if (a ~= b) then
        return 1
    end
    return 2
end

function D1(a, b)
    if (a ~= b and a < b) then
        return 1
    end
    return 2
end

function D2(a, b)
    if (not (a ~= b and a < b)) then
        return 1
    end
    return 2
end

function D3(a, b)
    if ((not (a ~= b and a < b)) or (a + 2 == b)) then
        return 1
    end
    return 2
end

function E1(a, b)
    local bool
    local X = ((not (a ~= b and a < b)) or (a + 2 == b))
    if (a ~= b or X or a + 5 == b)
    then
        a = a + 1
        return 2
    end
end

function E2(a, b)
    local bool
    local X = ((not (a ~= b and a < b)) or (a + 2 == b))
    while (a ~= b or X or a + 5 == b) do
        a = a + 1
        while (a < b) do
            b = b - 1
        end
    end
    return 2
end

function E2(a, b)
    local bool
    local X = ((not (a ~= b and a < b)) or (a + 2 == b))
    while (a ~= b or X or a + 5 == b) do
        a = a + 1
        while (fatorialA(a) < b) do
            b = b - 1
        end
    end
    return X or a > 0
end

ponto_2d_t = {}
ponto_2d_t.__index = ponto_2d_t

function ponto_2d_t:new(x, y)
    local obj = {
        x = x,
        y = y
    }
    setmetatable(obj, ponto_2d_t)
    return obj
end

ponto_3d_t = {}
ponto_3d_t.__index = ponto_3d_t

function ponto_3d_t:new(x, y, z)
    local obj = {
        x = x,
        y = y,
        z = z
    }
    setmetatable(obj, ponto_3d_t)
    return obj
end

segmento_2d_t = {}
segmento_2d_t.__index = segmento_2d_t

function segmento_2d_t:new(ini, fim)
    local obj = {
        ini = ini,
        fim = fim
    }
    setmetatable(obj, segmento_2d_t)
    return obj
end

segmento_3d_t = {}
segmento_3d_t.__index = segmento_3d_t

function segmento_3d_t:new(ini, fim)
    local obj = {
        ini = ini,
        fim = fim
    }
    setmetatable(obj, segmento_3d_t)
    return obj
end

function F1(seg, p)

    local ax = seg.ini.x
    local ay = seg.ini.y

    local bx = seg.fim.x
    local by = seg.fim.y

    local px = p.x
    local py = p.y

    local abx = bx - ax
    local aby = by - ay

    local apx = px - ax
    local apy = py - ay

    local ab2 = abx * abx + aby * aby

    local t = (apx * abx + apy * aby) / ab2

    if (t < 0.0) then
        t = 0.0
    end
    if (t > 1.0) then
        t = 1.0
    end

    local qx = ax + t * abx
    local qy = ay + t * aby

    local dx = px - qx
    local dy = py - qy

    return sqrt(dx * dx + dy * dy)
end

function dist2(a, b)
    local dx = a.x - b.x
    local dy = a.y - b.y
    return dx * dx + dy * dy
end

function F2(seg, p)

    local ax = seg.ini.x
    local ay = seg.ini.y
    local bx = seg.fim.x
    local by = seg.fim.y

    local px = p.x
    local py = p.y

    local abx = bx - ax
    local aby = by - ay

    local apx = px - ax
    local apy = py - ay

    local bpx = px - bx
    local bpy = py - by

    local dot1 = apx * abx + apy * aby
    local dot2 = bpx * abx + bpy * aby

    if (dot1 <= 0) then
        return dist2(p, seg.ini)
    end

    if (dot2 >= 0) then
        return dist2(p, seg.fim)
    end

    local cross = abx * apy - aby * apx

    return (cross * cross) / (abx * abx + aby * aby)

end

function area_poligono(p, n)
    local soma = 0
    local i = 1
    while i <= n do
        local j = (i % n) + 1
        soma = soma + p[i].x * p[j].y - p[j].x * p[i].y
        i = i + 1
    end

    if (soma < 0) then
        soma = 0 - soma
    end
    return soma / 2.0
end

function area_pol()
    local poli = {}
    return area_poligono(poli, 150)
end