
with open("input.txt") as file:
    lines = map(list, file.read().splitlines())

nums = set(map(str, range(10)))

out = 0
for og_line in lines:
    line = list(og_line)

    num1 = None
    for char in line:
        if char in nums:
            num1 = char
            break

    num2 = None
    for char in line[::-1]:
        if char in nums:
            num2 = char
            break

    out += int(num1 + num2)
    
print(out)
