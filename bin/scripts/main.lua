function main()
  print("Main called")
  local returnedValue = _G.interface.increment()
  print("Value returned by interface.increment: " .. returnedValue)
end
