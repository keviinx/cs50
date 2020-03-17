from cs50 import get_float

while True:
    change = get_float("Change owed: ")  # keep asking if not more than 0
    if change > 0:
        break  # get out if more than 0

change_in_cents = round(change * 100)  # convert to cents
coins = 0  # coins variable
coins += change_in_cents // 25  # process to breaks into coins
change_in_cents %= 25
coins += change_in_cents // 10
change_in_cents %= 10
coins += change_in_cents // 5
change_in_cents %= 5
coins += change_in_cents // 1

print(int(coins))  # print out the coins