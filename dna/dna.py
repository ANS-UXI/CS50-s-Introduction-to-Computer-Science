import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    data = []
    with open(sys.argv[1], "r") as file:
        r = csv.DictReader(file)
        for i in r:
            data.append(i)

    # TODO: Read DNA sequence file into a variable
    data_seq = ""
    with open(sys.argv[2], "r") as f:
        data_seq = f.read().rstrip()

    # TODO: Find longest match of each STR in DNA sequence
    match = []
    for i in data:
        x = {}
        for key in i:
            if key == "name":
                x[key] = i[key]
            else:
                x[key] = str(longest_match(data_seq, key))
        match.append(x)

    # TODO: Check database for matching profiles
    flag = False
    index = 0
    for i in data:
        for j in match:
            if i == j:
                print(i['name'])
                sys.exit(0)
            else:
                flag = True
    if flag:
        sys.exit("No match")


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
