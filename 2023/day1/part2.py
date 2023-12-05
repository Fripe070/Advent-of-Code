import re

with open("input.txt") as file:
    lines = file.read().splitlines()

nums = {
    "0": 0,
    "1": 1, "one": 1,
    "2": 2, "two": 2,
    "3": 3, "three": 3,
    "4": 4, "four": 4,
    "5": 5, "five": 5,
    "6": 6, "six": 6,
    "7": 7, "seven": 7,
    "8": 8, "eight": 8,
    "9": 9, "nine": 9,
}
forwards_regex = re.compile("|".join(nums.keys()))
backwards_regex = re.compile("|".join(key[::-1] for key in nums.keys()))

out = 0
for line in lines:
    num1 = nums[forwards_regex.search(line).group()]
    num2 = nums[backwards_regex.search(line[::-1]).group()[::-1]]

    out += int(str(num1) + str(num2))
    
print(out)
