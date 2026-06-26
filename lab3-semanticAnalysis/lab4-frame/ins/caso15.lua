function pipelineComplexo(id:int, peso:float):boolean
    local estado:int
    local idInterno:int
    local pesoInterno:float
    idInterno = id
    pesoInterno = peso
    if (not sistemaIniciado() == checarTrava(obterSeguranca())) then
        return abortar()
    else
        while (atualizarCiclo(idInterno) < obterMaxCiclos(calcularEspera(idInterno))) do
            if (validarMetrica(pesoInterno + transformar(idInterno))) then
                while (lerBuffer()) do
                    pesoInterno = pesoInterno * fatorCorrecao(obterMetricaAtual())
                end
            else
                if (logarErro(gerarMensagem(idInterno))) then
                    idInterno = redefinirId(idInterno, puxarBackup())
                end
            end
        end
    end
    return verificarSucessoFinal(idInterno, finalizarPeso(pesoInterno))
end
