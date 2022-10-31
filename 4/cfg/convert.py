obst = []
sm = []
w, h = map(int, input().split())
for y in range(h - 1, -1, -1):
    line = input()
    for x in range(w):
        if line[x] == '#':
            obst.append((x, y))
        elif line[x] == 's':
            sm.append((x, y))

print(w, h)
print(*sm[0])
print(*sm[1])
print(len(obst))
for el in obst:
    print(*el)
    
