# TODO
import cs50
height = cs50.get_int("Height: ")
if height <= 0 or height >= 9:
    height = cs50.get_int("Height: ")
for i in range(height):
    print(" " * (height - (i + 1)), end="")
    print("#" * (i + 1), end="")
    print(" " * 2, end="")
    print("#" * (i + 1))