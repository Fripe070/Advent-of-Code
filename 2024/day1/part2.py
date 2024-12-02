with open("input.txt") as file:
    lines = file.read().splitlines()

left_list = []
right_list = []

for line in lines:
    n1, n2 = map(int, line.split(" "*3))
    left_list.append(n1)
    right_list.append(n2)

summed = 0
for num in left_list:
    summed += num * right_list.count(num)

print(summed)
