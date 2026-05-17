-- ERRO DE TIPO: variável declarada como int, mas recebe BOOL_VAL
function erroAtribuicaoBool(a:int)
  local x:int
  x = true
  return x + a
end

