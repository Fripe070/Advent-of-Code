print(sum(abs(n1-n2)for n1,n2 in zip(*map(lambda x:sorted(map(int,x)),zip(*(line.split(" "*3)for line in open("input.txt").read().splitlines()))))))
