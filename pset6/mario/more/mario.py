from cs50 import get_int

while True:  # keep repeating
    height = get_int("Height: ")  # ask for height
    if height >= 1 and height <= 8:  # get out if more than 1 or 8
        break  # get out from while

for i in range(1, height + 1):  # for row, have to +1 because it will exit at height
    for j in range(height, i, -1):  # loop for printing spaces
        print(" ", end="")
    for j in range(0, i):  # loop for printing the #
        print("#", end="")
    for gap in range(0, 2):  # loop for printing the gap
        print(" ", end="")
    for j in range(0, i):  # loop for the second #
        print("#", end="")
    print()  # print new line