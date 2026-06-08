function classificaNumero(x:int):int
  local res:int
  if x > 0 then
    res = 1
  elseif x < 0 then
    res = -1
  else
    res = 0
  end
  return res
end