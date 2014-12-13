-- Sample variables --
a=7
b=8
c="Hello"

-- Write data to a file --
file.open("data.lua","w")
file.writeline("a="..a)
file.writeline("b="..b)
file.writeline("c=\""..c.."\"")
file.close()

---------------------------------------

node.restart()

---------------------------------------

-- All gone! --
print(a)
print(b)
print(c)

-- Read data from a file --
-- pcall(loadstring(x)) executes the string as if we typed it! -- 
file.open("data.lua","r")
repeat
 line = file.readline()
 if line ~= nil then pcall(loadstring(line)) end
until line == nil
file.close()

-- We're back! --
print(a)
print(b)
print(c)
