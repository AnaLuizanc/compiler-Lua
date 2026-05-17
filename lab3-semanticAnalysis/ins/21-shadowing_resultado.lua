-- A variável 'resultado' é declarada no escopo externo com valor 100.
-- No bloco interno, uma NOVA 'resultado' é declarada (shadowing) e
-- recebe o valor 1. O return está dentro do bloco interno, então
-- deve retornar 1, e NÃO 100.
function sombra(x:int)
  local resultado:int
  resultado = x * 100
  do
    local resultado:int
    resultado = x * 1
    return resultado
  end
end

