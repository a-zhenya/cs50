while 1:
    h = input("Cash owed: ")
    try:
        h = float(h)
        if h >= 0:
            h = round(100*h)
            break
    except ValueError:
        continue
cnt = 0
for coin in (25, 10, 5, 1):
    while h >= coin:
        cnt += 1
        h -= coin
print(cnt)
