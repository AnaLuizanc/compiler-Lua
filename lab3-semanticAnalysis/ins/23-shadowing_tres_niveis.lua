-- SHADOWING — nível 3 de complexidade
-- Três níveis de aninhamento, cada um com sua própria 'v'.
function sombraTresNiveis(x:int)
  local v:int
  v = x * 2
  do
    local v:int
    v = v * 3
    do
      local v:int
      v = v + 1
      return v
    end
  end
end

