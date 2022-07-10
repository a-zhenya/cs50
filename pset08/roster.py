from cs50 import SQL
import sys

if len(sys.argv) != 2:
	print( "usage:", sys.argv[0], "house" )
	exit(1)

db = SQL('sqlite:///students.db')

query = db.execute('select s.first, s.middle, s.last, s.birth from students s'
	+ ' where s.house = ? order by s.last, s.first, s.middle', sys.argv[1])
for line in query:
    name = f"{line['first']}{' ' + line['middle'] if line['middle'] else ''} {line['last']}"
    print( f"{name}, born {line['birth']}" )
