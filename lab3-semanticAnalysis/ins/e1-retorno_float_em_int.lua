-- ERRO DE TIPO: função declarada como int, mas retorna FLOAT_VAL
function erroRetornoFloat(a:int)
  local resultado:float
  resultado = a * 1.5
  return resultado
end

