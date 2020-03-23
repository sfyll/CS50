from cs50 import get_int
from cs50 import get_float

quarters, dimes, nickels, pennies = 25, 10, 5, 1
while True:
    print("how much change do we how you")
    print("Change:")
    change = get_float()
    if change > 0:
        break
last_change = round((change *100),1)
coin = 0
while last_change >= quarters:
    coin += 1
    last_change -= quarters
while last_change >= dimes:
    coin += 1
    last_change -= dimes
while last_change >= nickels:
    coin += 1
    last_change -= nickels
while last_change >= pennies:
    coin += 1
    last_change -= pennies
print("{}".format(last_change))
print("{}".format(coin))





