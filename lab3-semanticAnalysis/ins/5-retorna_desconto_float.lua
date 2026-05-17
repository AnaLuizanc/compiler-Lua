function descontar(preco:float, taxa:float)
  local final:float
  final = preco * (1.0 - taxa)
  return final
end

