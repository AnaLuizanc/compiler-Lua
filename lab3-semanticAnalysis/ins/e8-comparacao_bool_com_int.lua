-- ERRO DE TIPO: operador < aplicado a BOOL e INT
function erroMenorBool(ativo:bool, limite:int)
  local resultado:bool
  resultado = ativo < limite
  return resultado
end

