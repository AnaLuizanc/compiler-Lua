function F25(val:int, times:int, factor:int):int
  local i:int
  i = 0
  local result:int
  result = val
  repeat //TODO: PRECISO ADAPTAR AQUI
    result = result * factor
    i = i + 1
  until i >= times
end