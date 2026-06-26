function simular(passos:int):float
    local contadorPassos:int
    contadorPassos = passos
    while (contadorPassos > obterMinimo()) do
        if (checarCondicao(contadorPassos + calcularDelta())) then
            contadorPassos = contadorPassos - extrairPasso()
        else
            contadorPassos = contadorPassos / aplicarFator(obterDivisor(contadorPassos), retornarInercia())
        end
    end
    return obterResultadoFinal()
end
