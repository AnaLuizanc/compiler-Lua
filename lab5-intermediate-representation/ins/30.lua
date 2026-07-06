function F50(n:int, a:int, b:int):int
  local sum:int
  sum = 0
  local temp:int
  temp = (a * b) - (a + b) / 2

  if (n % 2 == 0) and (a + b > 0) then
    local x:int
    x = (n * n) + (a * 2)
    do
      local y:int
      y = x - (b / 2)
      sum = y + helper(a, b, n)
    end
  end

  if ((a * a + b * b) % 3) == 0 then
    local y:int
    y = (a + b) * (a - b)
    do
      sum = sum + y
    end
  else
    local d:int
    d = (((a + b) * (a + b)) / (n + 1))
    do
      sum = sum - d
    end
  end

  while n > 1 do
    local step:int
    step = (n % 3) + 1
    do
      sum = sum + (n * temp) - step + (a + b)
      n = n - ((n % 2) + 1)
    end
  end

  n = 0
  while n < 4 do
    local v:int
    v = (n * n) - (a - b) * (n + 1)
    do
      sum = sum + v
    end
    n = n + 1
  end

  if sum > 100 then
    do
      local r:int
      r = ((sum / 3) - F50(n + 1, a - 1, b + 2)) * 2 + (a % 3)
      sum = sum + r
    end
  end

  local tail:int
  tail = ((a * b) % (n + 2)) - temp
  sum = sum + tail

  return sum
end