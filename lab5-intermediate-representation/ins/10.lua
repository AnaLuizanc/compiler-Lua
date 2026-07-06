function fact(n:int):int
  if n <= 1 then
    return 1
  end
  return n * fact(n - 1)
end