fac 0 = 1
fac n = if n == 1 then 1 else n * fac (n-1)

main = print(fac 4)
