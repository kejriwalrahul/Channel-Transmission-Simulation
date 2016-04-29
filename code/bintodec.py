inp = open("./output/out","r")
out = open("./output/converted","w")

temp = ""
char = "a"
while char:
	char = inp.read(1)
	if len(char) == 0:
		break
	out.write(str(ord(char)))
	out.write("\n")
