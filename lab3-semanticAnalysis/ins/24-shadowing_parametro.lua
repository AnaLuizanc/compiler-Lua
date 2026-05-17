-- SHADOWING — nível 4 de complexidade
-- O parâmetro 'x' da função é sombreado por uma variável local
-- declarada dentro do bloco interno com o mesmo nome.
function sombraParametro(x:int)
  local acum:int
  acum = x * 2
  do
    local x:int
    x = acum + 9
    local resultado:int
    resultado = x * x
    return resultado
  end
end

