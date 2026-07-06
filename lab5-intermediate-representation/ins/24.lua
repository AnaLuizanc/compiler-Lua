function F24(from:int, to:int, step:int):int
  local i:int
  local product:int
  product = 1
  i = from
  while i < to do
    product = product * i
    i = i + step
  end
end