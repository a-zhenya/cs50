txt = input("Input text: ")

w = l = s = 0
in_w = False
for t in txt:
    if not t in " \t":
        in_w = True
    else:
        if in_w:
            w += 1
        in_w = False
    if t in 'abcdefghijklmnopqrstuvwxyz' or t in 'abcdefghijklmnopqrstuvwxyz'.upper():
        l += 1
    if t in '.!?':
        s += 1
if s == 0:
    s = 1
if in_w:
    w += 1
L = l*100.0 / w
S = s*100.0 / w
score = 0.0588 * L - 0.296 * S - 15.8
grade = int(score + 0.5)
if grade >= 16:
    grade = "Grade 16+"
elif grade < 1:
    grade = "Before Grade 1"
else:
    grade = "Grade " + str(grade)
print(grade)
