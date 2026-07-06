function F25(val, times, factor)
  local i = 0
  local result = val
  repeat
    result = result * factor
    i = i + 1
  until i >= times
end