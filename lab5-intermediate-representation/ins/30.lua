function F50(n, a, b)
  local sum = 0
  local temp = (a * b) - (a + b) / 2

  if (n % 2 == 0) and (a + b > 0) then
    local x = (n * n) + (a * 2)
    do
      local y = x - (b / 2)
      sum = y + helper(a, b, n)
    end
  end

  if ((a * a + b * b) % 3) == 0 then
    local y = (a + b) * (a - b)
    do
      sum = sum + y
    end
  else
    local d = (((a + b) * (a + b)) / (n + 1))
    do
      sum = sum - d
    end
  end

  while n > 1 do
    local step = (n % 3) + 1
    do
      sum = sum + (n * temp) - step + (a + b)
      n = n - ((n % 2) + 1)
    end
  end

  n = 0
  while n < 4 do
    local v = (n * n) - (a - b) * (n + 1)
    do
      sum = sum + v
    end
    n = n + 1
  end

  if sum > 100 then
    do
      local r = ((sum / 3) - F50(n + 1, a - 1, b + 2)) * 2 + (a % 3)
      sum = sum + r
    end
  end

  local tail = ((a * b) % (n + 2)) - temp
  sum = sum + tail

  return sum
end