from cs50 import get_int


while True:
    print("How high should the half pyramid be considered that it must be above an height of 0 and no greater than a height of 23")
    #print("height:")
    height = get_int()
    if ( height >= 0 and height < 24 ):
        break
for i in range(height):
    for v in range (height -1 - i):
        print(" ", end="")
    for y in range(i+2):
        print("#", end="")
    print("")