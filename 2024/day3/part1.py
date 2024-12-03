with open("input.txt") as file:
    text = file.read()

out = 0
i = 0
while i < len(text):
    if text[i:i+4] != "mul(":
        i += 1
        continue
    i += 4
    a = ""
    for _ in range(3):
        if text[i] in map(str, range(10)):
            a += text[i]
            i += 1
    if text[i] != ",":
        continue
    i += 1
    b = ""
    for _ in range(3):
        if text[i] in map(str, range(10)):
            b += text[i]
            i += 1
    if text[i] != ")":
        continue

    out += int(a) * int(b)

print(out)
