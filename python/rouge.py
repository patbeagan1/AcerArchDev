from collections import namedtuple
struct = namedtuple("struct", "name health damage x y symbol")

print("\nhello")
print("welcome to the program.\ntoday we are playing rouge.")
	
def printMap():
	for x in range (0,6):
		for y in range (0,6):
			if y == character[4]:
				if x == character[3]:
					print("p"),
			else:
				print(map[y][x]),
		print("")
#declarations
map = [[0 for x in range(6)] for y in range(6)]
character = struct("patrick",10,1,0,5,'p')


from ImageLibrary import Image
myImage = Image.open("pandaSpeed.jpg");
myImage.show();
printMap()