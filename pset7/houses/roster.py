from sys import argv, exit
import cs50

# check command line arguments
# ============================
if len(argv) != 2:  # not enough arguments
    print("Usage: python roster.py house")
    exit(1)

# query database for all stundent in house
# ========================================
house = argv[1]  # variable for house name
db = cs50.SQL("sqlite:///students.db")  # connect to the database

# students should be sorted alphabetically by last name and then first name
# =========================================================================
result = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", house)

# print out each students full name and birth year
# ================================================
for row in result:
    if row['middle'] is None:
        print(row['first'], row['last']+", born", row['birth'])
    else:
        print(row['first'], row['middle'], row['last']+", born", row['birth'])