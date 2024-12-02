with open("input.txt") as file:
    lines = file.read().splitlines()

left_list = []
right_list = []


for line in lines:
    n1, n2 = map(int, line.split(" "*3))
    left_list.append(n1)
    right_list.append(n2)

left_list.sort()
right_list.sort()

pairs = zip(left_list, right_list)

summed = sum(abs(n1 - n2) for n1, n2 in pairs)

print(summed)
