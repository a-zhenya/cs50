import csv
import sys
from collections import defaultdict

if len(sys.argv) != 3:
    print("usage:", sys.argv[0], "database", "sample")
    exit(1)

# reading DNA database
dbseqs = []
db = []
with open(sys.argv[1]) as dbfile:
    dbreader = csv.reader(dbfile, delimiter=',')
    for row in dbreader:
        if not dbseqs:
            dbseqs = row[1:]
        else:
            db.append({
                "name": row[0],
                "signature": [x for x in map(int, row[1:])],
            })

samplefile = open(sys.argv[2])
sample = samplefile.readline()

# calculating signature for sample
signature = defaultdict(int)
for seq in dbseqs:
    for j in range(len(sample) - len(seq)):
        matches = 0
        start = j
        while seq == sample[start: start + len(seq)]:
            start += len(seq)
            matches += 1
        if matches > signature[seq]:
            signature[seq] = matches

# check sample agaings every db entry
for dbentry in db:
    for j in range(len(dbseqs)):
        if signature[dbseqs[j]] != dbentry["signature"][j]:
            break
    else:
        print(dbentry["name"])
        exit(0)
print("No match")

