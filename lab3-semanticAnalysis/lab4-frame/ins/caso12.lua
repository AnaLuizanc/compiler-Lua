function checarSensor(leitura:float):int
    local copiaLeitura:float
    copiaLeitura = leitura
    if (calibrar(copiaLeitura) == obterAlvo()) then
        if dispararAlarme() then
            return 1
        end
    end
    if(not estaPronto() < limiteCritico()) then
        copiaLeitura = lerSegundaOpcao(copiaLeitura * ajustar())
    end
    return verificarSistema()
end
