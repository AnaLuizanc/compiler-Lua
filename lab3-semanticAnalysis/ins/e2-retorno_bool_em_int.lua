-- ERRO DE TIPO: função declarada como int, mas retorna BOOL_VAL
function erroRetornoBool(x:int):int
  local flag:bool
  flag = x < 0
  return flag
end

