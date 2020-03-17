from sys import argv, exit
import csv
import cs50

# check command line arguments
# ============================
if len(argv) != 2:  # not enough arguments
    print("Usage: python import.py characters.csv")
    exit(1)

# open csv file fiven by the command line argument
# ================================================
characters = open(argv[1], "r")
reader = csv.DictReader(characters)  # dict reader work, reader didn't

# for each row parse name
# =======================
db = cs50.SQL("sqlite:///students.db")  # connect to the database

# insert each student into the students table of student.db
# =========================================================
for row in reader:  # go thru each row
    name = row["name"].split()  # split the name
    if len(name) == 3:  # if have middle name
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                   name[0], name[1], name[2], row["house"], row["birth"])
    else:  # if no middle name
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, NULL, ?, ?, ?)",
                   name[0], name[1], row["house"], row["birth"])