function calcular():int
  local a:int
  a = 5
  do
    local b:int
    b = a * 3
    do
      local c:int
      c = b + 1
      return c
    end
  end
end

