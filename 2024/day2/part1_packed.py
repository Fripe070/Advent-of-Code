print(sum(all(d*(((n:=report[0]-report[1])>0)-(n<0))in{1,2,3}for d in[a-b for a,b in zip(report,report[1:])])for report in[[*map(int,l.split())]for l in open("input.txt")]))
