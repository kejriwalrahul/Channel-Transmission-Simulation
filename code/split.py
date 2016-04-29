import sys

inp = open(sys.argv[1],"r")
out = open(sys.argv[1]+"splitted","w")

count = 0
while True:
	print count
	count += 1
	c = inp.read()
	if len(c) == 0:
		break
	out.write(c)
	if count%100:
		out.write("\n")