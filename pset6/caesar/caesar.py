from cs50 import get_int
from cs50 import get_float
from cs50 import get_string

import sys

if len(sys.argv) != 2:
    print(sys.argv, len(sys.argv))
    print("please give us a figure")
    sys.exit(1)
else:
    key = int(sys.argv[1])
    print("what string would you like us to encrypt?")
    tb_encrypted = get_string()
    print("ciphertext:", end=" ")
    encrypted =""
    for character in tb_encrypted:
        x = ord(character)
        if character.isupper():
            y = ((((x - 64) + key) % 26) + 64)
            v = chr(y)
            encrypted += v
        elif character.islower():
            o = ((((x - 96) + key) % 26) + 96)
            v = chr(o)
            encrypted += v
        else:
            encrypted += character
print(encrypted)
