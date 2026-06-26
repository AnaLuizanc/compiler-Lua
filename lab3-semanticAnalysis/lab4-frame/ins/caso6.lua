function avaliar(x:int):bool 
    local localX:int
    localX = x
    if checar(localX) < limite() then
        return verificarAtalho(localX)
    else
        localX = localX * recalcular(localX)
    end
end
