-- SHADOWING — nível 2 de complexidade
-- 'resultado' é declarada e atribuída no escopo externo (x * 100).
-- O bloco interno declara sua PRÓPRIA 'resultado' e a altera (x * 1),
-- mas o return está FORA do bloco interno, no escopo externo.
-- O valor correto de retorno é o da 'resultado' EXTERNA: x * 100.
function sombraRetornoExterno(x:int)
  local resultado:int
  resultado = x * 100
  do
    local resultado:int
    resultado = x * 1
  end
  return resultado
end

