function f()
  local a
  local b
  local c
  local d

  a = 10
  b = 25
  c = 17
  d = b * b - 4 * a * c
  return d
end

function f(a, b, c)
  local d
  d = b * b - 4 * a * c
  return d
end

function f(a, b, c)
  local d
  d = b * b - 4 * a * c
  return d
end

function F4()
  local x = 10
  x = x + 5
end

function F5()
  local x = 5
  local y = 0
  if x > 2 then
    y = 1
  end
end

function F6()
  local x = 4
  local y
  if x < 3 then
    y = 0
  else
    y = 1
  end
end

function F7()
  local i = 0
  local sum = 0
  while i < 5 do
    sum = sum + i
    i = i + 1
  end
end

function F8()
  local i
  local total = 0
  i = 0
  while i < 4 do
    total = total + i
    i = i + 1
  end
end

function F9()
  local r = square(5)
end

function fact(n)
  if n <= 1 then
    return 1
  end

  return n * fact(n - 1)
end

function F11()
  local a = 1
  local b = 0
  local result = a and b
end

function F12()
  local x = 5
  do
    local x = 10
    x = x + 1
  end
end

function F13(a)
  local x = a
  x = x + 5
end

function F14(x)
  local y = 0
  if x > 2 then
    y = 1
  end
end

function F15(x)
  local y
  if x < 3 then
    y = 0
  else
    y = 1
  end
end

function F16(limit)
  local i = 0
  local sum = 0
  while i < limit do
    sum = sum + i
    i = i + 1
  end
end

function F18(max)
  local i
  local total = 0
  i = 0
  while i < max do
    total = total + i
    i = i + 1
  end
end

function F19(a)
  local r = square(a)
end

function F20(a, b, c)
  local x = a + b + c
  x = x + 5
end

function F21(x, y, z)
  local r = 0
  if x > y + z then
    r = 1
  end
end

function F22(a, b, c)
  local flag
  if a < b + c then
    flag = 0
  else
    flag = 1
  end
end

function F23(start, limit, step)
  local i = start
  local total = 0
  while i < limit do
    total = total + i
    i = i + step
  end
end

function F24(from, to, step)
  local i
  local product = 1
  i = from
  while i < to do
    product = product * i
    i = i + step
  end
end

function F25(val, times, factor)
  local i = 0
  local result = val
  repeat
    result = result * factor
    i = i + 1
  until i >= times
end

function power(base, exp)
  if exp == 0 then
    return 1
  end

  return base * power(base, exp - 1)
end

function F27(base, exp, offset)
  local result = power(base, exp) + offset
end

function F28(n, a, b)
  local sum = 0

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

  local i = 0
  while i < 3 do
    sum = sum + i
    i = i + 1
  end

  if sum > 10 then
    return F50(sum / 3, a, b)
  end

  return sum
end

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