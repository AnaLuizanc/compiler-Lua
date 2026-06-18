function validarFluxo(status:int):bool
    local estadoAtual:int
    estadoAtual = status
    while verificarStatus(estadoAtual) do
        if not validarToken(gerarToken()) then
            estadoAtual = atualizar(estadoAtual, falha())
        else
            return proximaEtapa()
        end
    end
end
