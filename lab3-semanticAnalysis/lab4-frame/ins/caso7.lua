function buscar():int
    local sinalizador:int
    while lerProximo() do
        if extrairValor() == 0 then
            return obterPadrao()
        end
    end
end
