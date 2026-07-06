function F50(n, a, b)
  local sum = 0
  local temp = (a * b) - (a + b) / 2

  if (n % 2 == 0) and (a + b > 0) then
    sum = (n * n) + (a * 2) - (b / 2)
  end

  if ((a * a + b * b) % 3) == 0 then
    sum = sum + (a + b) * (a - b)
  else
    sum = sum - (((a + b) * (a + b)) / (n + 1))
  end

  while n > 1 do
    sum = sum + (n * temp) - (n % 3) + (a + b)
    n = n - ((n % 2) + 1)
  end

  n = 0
  while n < 4 do
    sum = sum + (n * n) - (a - b) * (n + 1)
    n = n + 1
  end

  if sum > 100 then
    local r = ((sum / 3) - F50(n + 1, a - 1, b + 2)) * 2 + (a % 3)
    sum = sum + r
  end

  return sum + ((a * b) % (n + 2)) - temp
end