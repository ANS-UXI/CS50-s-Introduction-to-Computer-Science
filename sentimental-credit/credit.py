# TODO
import sys
from cs50 import get_int
num = get_int("Number: ")
sum = 0

for i in range(0, len(str(num))):
    if i % 2 == 0:
        sum += int(str(num)[(len(str(num)) - 1) - i])
    else:
        x = int(str(num)[(len(str(num)) - 1) - i]) * 2
        if x >= 10:
            sum = sum + int(str(x)[0]) + int(str(x)[1])
        else:
            sum = sum + x

if sum % 10 != 0:
    print("INVALID")
    sys.exit(1)

amex = [34, 37]
master = [51, 52, 53, 54, 55]
if len(str(num)) == 15 and int(str(num)[:2]) in amex:
    print("AMEX")
    sys.exit(1)
elif len(str(num)) == 16 and int(str(num)[:2]) in master:
    print("MASTERCARD")
    sys.exit(1)
elif (len(str(num)) == 16 or len(str(num)) == 13) and int(str(num)[0]) == 4:
    print("VISA")
    sys.exit(1)
else:
    print("INVALID")
    sys.exit(1)