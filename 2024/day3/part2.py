with open("input.txt") as file:
    text = file.read()

i = 0
# I knew crafting interpreters was worth reading
def consume(txt: str) -> str | None:
    global i
    sliced = text[i:i+len(txt)]
    if sliced == txt:
        i += len(txt)
        return sliced

out = 0
on = True
while i < len(text):
    if consume("do()"):
        on = True
        continue
    if consume("don't()"):
        on = False
        continue

    if not on or not consume("mul("):
        i += 1
        continue

    a = ""
    for _ in range(3):
        if text[i] in map(str, range(10)):
            a += text[i]
            i += 1
    if not consume(","):
        continue
    b = ""
    for _ in range(3):
        if text[i] in map(str, range(10)):
            b += text[i]
            i += 1
    if not consume(")"):
        continue

    out += int(a) * int(b)

print(out)
