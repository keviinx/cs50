from cs50 import get_int

while True:  # keep asking for credit card number
    credit_card_number = get_int("Number: ")
    if credit_card_number > 0:  # get out if more than 0
        break

if len(str(credit_card_number)) != 13 and len(str(credit_card_number)) != 15 and len(str(credit_card_number)) != 16:  # invalid length check
    print("INVALID")

else:
    # splitting digits block
    digit_1 = credit_card_number % 10
    digit_2 = ((credit_card_number % 100) // 10) * 2
    digit_3 = (credit_card_number % 1000) // 100
    digit_4 = ((credit_card_number % 10000) // 1000) * 2
    digit_5 = (credit_card_number % 100000) // 10000
    digit_6 = ((credit_card_number % 1000000) // 100000) * 2
    digit_7 = (credit_card_number % 10000000) // 1000000
    digit_8 = ((credit_card_number % 100000000) // 10000000) * 2
    digit_9 = (credit_card_number % 1000000000) // 100000000
    digit_10 = ((credit_card_number % 10000000000) // 1000000000) * 2
    digit_11 = (credit_card_number % 100000000000) // 10000000000
    digit_12 = ((credit_card_number % 1000000000000) // 100000000000) * 2
    digit_13 = (credit_card_number % 10000000000000) // 1000000000000
    digit_14 = ((credit_card_number % 100000000000000) // 10000000000000) * 2
    digit_15 = (credit_card_number % 1000000000000000) // 100000000000000
    digit_16 = ((credit_card_number % 10000000000000000) // 1000000000000000) * 2

    # checksum block
    checksum = (digit_1 % 10) + ((digit_1 % 100) // 10)
    checksum += (digit_2 % 10) + ((digit_2 % 100) // 10)
    checksum += (digit_3 % 10) + ((digit_3 % 100) // 10)
    checksum += (digit_4 % 10) + ((digit_4 % 100) // 10)
    checksum += (digit_5 % 10) + ((digit_5 % 100) // 10)
    checksum += (digit_6 % 10) + ((digit_6 % 100) // 10)
    checksum += (digit_7 % 10) + ((digit_7 % 100) // 10)
    checksum += (digit_8 % 10) + ((digit_8 % 100) // 10)
    checksum += (digit_9 % 10) + ((digit_9 % 100) // 10)
    checksum += (digit_10 % 10) + ((digit_10 % 100) // 10)
    checksum += (digit_11 % 10) + ((digit_11 % 100) // 10)
    checksum += (digit_12 % 10) + ((digit_12 % 100) // 10)
    checksum += (digit_13 % 10) + ((digit_13 % 100) // 10)
    checksum += (digit_14 % 10) + ((digit_14 % 100) // 10)
    checksum += (digit_15 % 10) + ((digit_15 % 100) // 10)
    checksum += (digit_16 % 10) + ((digit_16 % 100) // 10)

    if checksum % 10 != 0:  # invalid checksum
        print("INVALID")

    else:
        if len(str(credit_card_number)) == 16:  # 16 digits card check
            if digit_16 // 2 == 4:  # valid visa
                print("VISA")
            else:
                mastercard_check = credit_card_number // 100000000000000

                if mastercard_check >= 51 and mastercard_check <= 55:  # valid mastercard
                    print("MASTERCARD")
                else:  # invalid card
                    print("INVALID")

        elif len(str(credit_card_number)) == 15:  # 15 digit card check
            amex_check = credit_card_number // 10000000000000
            if amex_check == 34 or amex_check == 37:  # valid amex card
                print("AMEX")
            else:  # invalid card
                print("INVALID")
        else:  # 13 digit card check
            if digit_13 == 4:  # valid visa
                print("VISA")
            else:  # invalid card
                print("INVALID")