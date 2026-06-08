function sombraTresNiveis(x:int):int
  local v:int
  v = x * 2
  do
    local v:int
    v = v * 3
    do
      local v:int
      v = v + 1
      return v
    end
  end
end

