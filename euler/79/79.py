codes = [list(x) for x in file('keylog.txt').read().split('\n') if x]
password = []
while codes:
    scores = {}
    for code in codes:
        for i, digit in enumerate(code):
            scores[digit] = max(m.get(digit, -1), i)

    score, letter = min((v, k) for k, v in scores.iteritems())
    password.append(letter)
    codes = [[d for d in code if d not in password] for code in codes]
    codes = [x for x in codes if x]

print ''.join(password)
