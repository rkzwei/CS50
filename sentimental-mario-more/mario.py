
def height():
    x = 0
    # requests height from user
    # loops until user inputs valid height
    while (x < 1 or x > 8):
        # handles non-integers
        try:
            x = int(input("Height: "))
        except ValueError:
            print("Not a number my man, try again")

    return x
# builds pyramid according to size input


def builder(size):
    space = 0
    width = 1
    blocks = 0

    while width <= size:
        # prints spaces for sides
        for space in range(size - width):
            print(" ", end="")
        # left side of build
        for blocks in range(width):
            print("#", end="")
        # prints space in the middle
        print("  ", end="")
        # right side of build
        for blocks in range(width):
            print("#", end="")
        print()
        width += 1


def main():
    h = height()
    builder(h)
    

main()