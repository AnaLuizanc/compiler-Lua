function calcularTaxa(tipo:int):float
    if estaAtivo(tipo) then
        if obterDesconto() > 50 then
            return aplicarBonus(total() + 10)
        end
    end
end
