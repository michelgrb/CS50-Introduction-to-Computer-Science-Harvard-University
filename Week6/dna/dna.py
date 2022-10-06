import csv
import sys


def main():

    # TODO: Check for command-line usage
    try:
        db = open(sys.argv[1])
        s = open(sys.argv[2])
    except FileNotFoundError:
        print("File not found")
    finally:
        db.close()
        s.close()

    # TODO: Read database file into a variable
    with open(sys.argv[1], "r") as file:
        first_line = file.readline()

    dnacount = []
    sqrs = []
    temp = []
    datasize = 0

    for i in range(5, len(first_line)):
        if first_line[i] == "," or i == (len(first_line)-1):
            datasize += 1
            sqrs.append(''.join(temp))
            temp.clear()
        else:
            temp.append(first_line[i])

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file:
        liness = file.readline()

    # TODO: Find longest match of each STR in DNA sequence

    dnacur = 0
    dnamax = 0
    truec = 0
    row = 0

    for sqr in range(len(sqrs)):

        count = 0
        while count in range(len(liness)-len(sqrs[sqr])-1):

            if liness[count] == sqrs[sqr][0] or dnacur >:
                truec = 0
                for x in range(len(sqrs[sqr])):
                    if liness[count + x] != sqrs[sqr][x] and truec == 0:
                        truec -= 1

                if truec >= 0:
                    dnacur += 1
                    truec = 0
                    count = count + (len(sqrs[sqr])-1)
                else:
                    if dnamax > dnacur:
                        dnacur = 0
                    else:
                        dnamax = dnacur
                        dnacur = 0

                    truec = 0
            count += 1

        dnacount.append(dnamax)
        dnamax = 0
        dnacur = 0

    with open(sys.argv[1], "r") as file:
        text = file.readlines()[1:]

    profiles = []
    temppro = []
    tempname = []

    for i in range(len(text)):

        for x in range(len(text[i])-1):
            if ((text[i][x].isnumeric()) != True) and (text[i][x] != ","):
                tempname.append(text[i][x])

            if ((text[i][x].isnumeric()) == True) or text[i][x] == ",":
                temppro.append(text[i][x])

        temppro.remove(",")
        profiles.append(''.join(tempname))
        profiles.append(''.join(temppro))
        temppro.clear()
        tempname.clear()

    liste = ""
    for i in range(len(dnacount)):
        liste = liste + str(dnacount[i])
        if i+1 != len(dnacount):
            liste = liste + ","
    # TODO: Check database for matching profiles
    if liste in profiles:
        name = profiles.index(liste) - 1
        print(profiles[name])
    else:
        print("No match")

    return


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
