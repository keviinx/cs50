from sys import argv, exit
import csv

if len(argv) != 3:  # check for argument
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# opening the file
# ================
data = open(argv[1], "r")  # open the file of database
reader = csv.reader(data)  # read the data

table = []  # create a table array
for row in reader:
    table.append(row)  # append data into table

header = table[0]  # just get the top for the header
header.pop(0)  # remove the name in the array from header

STRs = {}  # dictionary for str

for index in header:  # go thru every array in the header
    STRs[index] = 0  # store the STRs

# computing str counts
# ====================
sequence = open(argv[2], "r").read()  # read the sequence directly and store the sequence

for bases in STRs:  # go thru each bases
    bases_length = len(bases)  # get the length of the base
    max_count = 0  # variable for maximum count
    temp_count = 0  # variable for temporary count

    for i in range(len(sequence)):  # go thru the whole dna sequence

        while temp_count > 0:  # as long as the temp more than 0
            temp_count -= 1  # reduce the counter to avoid counting again
            continue

        if sequence[i: i + bases_length] == bases:  # sequence matches with base
            temp_count += 1  # first match
            while sequence[i - bases_length: i] == sequence[i: i + bases_length]:  # if the next sequence matches
                temp_count += 1  # increase the temp counter
                i += bases_length  # move the index

            if temp_count > max_count:  # if the temp counter more than max counter
                max_count = temp_count  # set the new max

    STRs[bases] += max_count  # increase the value into the STR array

# comparing against data
# ======================

database = open(argv[1], "r", newline='')  # open the file again and remove newline
dict_reader = csv.DictReader(database)  # read using dictreader
for person in dict_reader:  # go thru the database
    matches = 0  # variable for matches

    for bases in STRs:
        if STRs[bases] == int(person[bases]):  # if the bases matches
            matches += 1  # increase the matches

        if matches == len(STRs):  # if all matches occurs
            print(person['name'])  # print the name of the person
            exit(0)  # exit successfully

print("No match")  # no match found