function testaElseIf(x:int):int
  local res:int
  res = 0
  if x == 1 then
    res = 10
  elseif x == 2 then
    res = 20
  end
  return res
end