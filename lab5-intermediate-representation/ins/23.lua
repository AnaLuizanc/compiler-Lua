function F23(start, limit, step)
  local i = start
  local total = 0
  while i < limit do
    total = total + i
    i = i + step
  end
end