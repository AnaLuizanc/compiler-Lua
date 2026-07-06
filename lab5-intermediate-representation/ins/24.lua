function F24(from, to, step)
  local i
  local product = 1
  i = from
  while i < to do
    product = product * i
    i = i + step
  end
end