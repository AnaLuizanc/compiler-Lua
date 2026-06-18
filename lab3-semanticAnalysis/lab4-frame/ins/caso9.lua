function formula(base:int):int
    local res:int
    res = not estaVazio() + (calcular(base) * obterMultiplicador(ajustar(base)))
    return res
end
