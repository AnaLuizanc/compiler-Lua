function power(base, exp)
  if exp == 0 then
    return 1
  end

  return base * power(base, exp - 1)
end