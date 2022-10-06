import cs50

# try get input else ask again must be between 1 and 8
while True:
    try:
        height = int(cs50.get_int("Height:"))
        if 1 <= height <= 8:
            break
    except ValueError:
        print("Input must be an integer between 1 and 8.")

# num of spaces befor #
space = height - 1

for h in range(height):

    for x in range(space):
        print(" ", end='')
        x += 1
    for x in range(height - space):
        print("#", end='')
        x += 1

    print("  ", end='')

    for x in range(height - space):
        print("#", end='')
        x += 1

    # new height and print new line
    h += 1
    print("")

    # also 1 less space
    space -= 1