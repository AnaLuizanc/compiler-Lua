-- ERRO DE TIPO: função declarada como boolean, mas retorna FLOAT
function erroRetornoFloatEmBool(taxa:float, valor:int)
  local desconto:float
  desconto = valor * taxa
  return desconto
end

