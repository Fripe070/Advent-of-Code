print((lists:=tuple(zip(*(map(int,line.split(" "*3))for line in open("input.txt").read().splitlines())))),sum(n1*lists[1].count(n1)for n1, n2 in lists[0]))
