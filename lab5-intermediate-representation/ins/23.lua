function F23(start:int, limit:int, step:int):int
  local i:int
  i = start
  local total:int
  total = 0
  while i < limit do
    total = total + i
    i = i + step
  end
end