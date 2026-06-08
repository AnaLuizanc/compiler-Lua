function triplo_aninhado():int
  local a:int
  a = 1
  do
    local b:int
    b = a + 2
    do
      local c:int
      c = b * 3
      do
        local d:int
        d = c - 1
        return d
      end
    end
  end
end

