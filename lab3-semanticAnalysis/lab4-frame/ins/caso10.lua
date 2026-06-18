function processarMatriz():int
    local celula:int
    while possuiLinha() do
        while possuiColuna() do
            celula = processarCelula(obterX(), obterY(maximo()))
        end
    end
end
