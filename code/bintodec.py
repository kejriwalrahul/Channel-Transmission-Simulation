inp = open("./output/out","r")
out = open("./output/converted","w")

temp = ""
char = "a"
while char:
	char = inp.read(1)
	# print char
	# print ord(char)
	if len(char) == 0:
		break
	out.write(str(ord(char)))
	out.write("\n")
