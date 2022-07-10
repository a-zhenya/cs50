from cs50 import SQL
import csv
import sys

if len(sys.argv) != 2:
	print( "usage:", sys.argv[0], "csvfile" )
	exit(1)

db = SQL('sqlite:///students.db')

with open(sys.argv[1]) as dbfile:
    dbfile.readline()
    dbreader = csv.reader(dbfile, delimiter=',')
    for row in dbreader:
        names = row[0].split()
        if len(names) == 2:
        	n1 = names[0]
        	n2 = None
        	n3 = names[1]
        else:
        	n1 = names[0]
        	n2 = names[1]
        	n3 = names[2]
        db.execute('insert into students (first, middle,'
        	+ ' last, house, birth) values (?, ?, ?, ?, ?)',
        	n1, n2, n3, row[1], int(row[2]) )
