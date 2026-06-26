function motorDeBusca(chave:int):int
    local chaveBusca:int
    chaveBusca = chave
    while (iterarDados()) do
        if (comparar(chaveBusca, obterChaveAtual()) == 0) then
            while (extrairMetadados(chaveBusca)) do
                chaveBusca = incrementarChave(chaveBusca, calcularSalto(chaveBusca))
            end
            return formatarResultado(chaveBusca)
        end
    end
end
