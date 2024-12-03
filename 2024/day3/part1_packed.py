print(sum(map(lambda x:int(x[0])*int(x[1]),[f for f in __import__("re").findall(r"mul\((\d+),(\d+)\)",open("input.txt").read())])))
