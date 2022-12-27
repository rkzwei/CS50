import csv
import sys
import re


def clcheck():
    # evaluates if correct number of files went it
    if len(sys.argv) != 3:
        print(len(sys.argv))
        print("Usage: python dna.py database.csv DNAsequence.txt")
        return 1
    # tries to match filename to check if database
    elif not re.search(r"(\.csv)$", sys.argv[1]):
        print("First file is not CSV database")
        return 2
    # same but sequence
    elif not re.search(r"(\.txt)$", sys.argv[2]):
        print("Second file is not a text file")
        return 3
    else:
        # print("Great Success, very good, very good")
        return


def main():

    # checks for proper command line usage
    if clcheck():
        return 4

    # prototyping some variables
    data = {}
    fields = []
    strs = {}

    # opens database file using with, so it'll close
    with open(sys.argv[1], "r") as fdb:
        dbreader = csv.DictReader(fdb)
        # sets fieldnames for later use
        fields = dbreader.fieldnames
        # iterates through rows, adding the row as value in a dictionary, with the name as a key
        for row in dbreader:
            data[row['name']] = row

    # removes the name column
    fields.remove('name')

    # reads sequence into memory
    with open(sys.argv[2], "r") as fseq:
        seq = fseq.read()

    # finds longest match for each of the DNA STRs, converts them to int and stores it in dictionary with the subseq as key
    for i in range(len(fields)):
        strs[fields[i]] = int(longest_match(seq, fields[i]))

    # iterates through our dictionaries and list to match whoever has the DNA match
    for name in data:
        # sets boolean to true

        match = True
        for field in fields:
            # if does not match -> sets match to false -> breaks loop, avoiding iterating over unnecesary data
            if int(data[name][field]) != strs[field]:
                match = False
                break
        # after iterating, checks if match is true, printing the name and ending the loop, otherwise prints no match
        if match:
            print(f"{data[name]['name']}")
            break

    # checks conditional which was left as false if the loop ran out of bounds
    if match == False:
        print("No match")
    return


"""
    #original solution, using nested for loops

    match = False
    for name in data:
        for i in range(len(fields)):
            data[name][fields[i]] = int(data[name][fields[i]])
            if data[name][fields[i]] == strs[fields[i]]:
                data[name][fields[i+1]] = int(data[name][fields[i+1]])
                if data[name][fields[i+1]] == strs[fields[i+1]]:
                    data[name][fields[i+2]] = int(data[name][fields[i+2]])
                    if data[name][fields[i+2]] == strs[fields[i+2]]:
                        print(f"{data[name]['name']}")
                        match = True
                        break
        if match == True:
            break
    if not match == True:
        print("No match") """


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
