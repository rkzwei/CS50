
# prototypes all the functions
def ask():
    # acquires numbers only
    return int(input("Insert card: "))


def iscard(card):
    # determines lenght of number
    lent = len(str(card))

    if lent != 13 and lent != 15 and lent != 16:
        print("INVALID")
        return 0
    else:
        return 1


def checksum(card):
    # check1 & 2 will do the sum
    check1 = 0
    check2 = 0
    # total will serve to add 1 & 2 for modulus
    total = 0
    # last will acquire the last digits using modulus
    last1 = 0
    last2 = 0
    # div will be used for check2 for Luhn
    div1 = 0
    div2 = 0
    # ye is arbitrary as our card operating number
    ye = card

    while ye > 0:
        # this will acquire the last digit
        last1 = ye % 10
        # this will remove the last digit, previously acquired
        ye = ye // 10
        # now we add the last digit to the first check
        check1 += last1

        # this will acquire the next last digit
        last2 = ye % 10
        # once again removing the last digit
        ye = ye // 10

        # as we have an acquirer
        # we now multiply or add according to Luhn
        # last2 is multiplied, as they are the second digits
        # div1 and 2 will individualize the digits
        last2 = last2 * 2
        div1 = last2 % 10
        div2 = last2 // 10
        # now add the individual digits to the check2 sum
        check2 += div1 + div2

    # total adds our sums and then modulus for remainder.
    total = check1 + check2
    if total % 10 != 0:
        print("INVALID")
        return 0
    return 1

# will acquire first digits and select appropriate brand


def brand(card):
    num = card
    # divides to acquire two digits
    fone = num // (10 ** (len(str(num)) - 1))
    ftwo = num // (10 ** (len(str(num)) - 2))

    # now that it's double digit
    # removes last and checks if VISA
    if fone == 4:
        print("VISA")
    # checks if dd is MASTERCARD
    elif ftwo >= 51 and ftwo <= 55:
        print("MASTERCARD")
    # checks if AMEX
    elif ftwo == 34 or ftwo == 37:
        print("AMEX")
    else:
        print("INVALID")

# main function


def main():
    num = ask()
    # checks if given number is a card, if not exit
    if iscard(num) == 0:
        return 0

    # performs Luhn Algorithm check
    if checksum(num) == 0:
        return 0

    # identifies and returns the brand
    brand(num)


main()
# although it may be the objective,
# I did not change any logic in the checksum,
# but did refactor main, brand and ask