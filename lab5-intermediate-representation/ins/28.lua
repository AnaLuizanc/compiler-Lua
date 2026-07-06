function F28(n:int, a:int, b:int):int
  local sum:int
  sum = 0

  if n <= 0 then
    return 0
  end

  if a > b then
    sum = a - b
  else
    sum = b - a
  end

  while n > 0 do
    sum = sum + n
    n = n - 1
  end

  local i:int
  i = 0
  while i < 3 do
    sum = sum + i
    i = i + 1
  end

  if sum > 10 then
    return F50(sum / 3, a, b)
  end

  return sum
end