-- SHADOWING — nível 5 de complexidade (máximo)
-- Duas variáveis ('v' e 'w') são sombreadas simultaneamente em blocos aninhados.
function sombraDupla(a:int, b:int)
  local v:int
  v = a * 10
  local w:int
  w = b + 1
  do
    local v:int
    v = w * 2
    do
      local w:int
      w = v + v
      return w
    end
  end
end

