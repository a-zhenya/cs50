while 1:
    h = input("Height:")
    try:
        h = int(h)
        if h > 0 and h <= 8:
            break
    except ValueError:
        continue
for k in range (h):
    s = ""
    for j in range(h - k - 1):
        s += " "
    for j in range(k + 1):
        s += "#"
    s += "  "
    for j in range(k + 1):
        s += "#"
    print(s)
