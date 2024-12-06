f = open("input", "r")

input = []

for line in f:
    input.append([int(x) for x in line.split()])

f.close()


sum = 0


def checkSafe(level):
    increasing = True
    if level[0] > level[1]:
        increasing = False

    for i in range(1, len(level)):
        if (increasing and level[i] < level[i - 1]) or (
            not increasing and level[i] > level[i - 1]
        ):
            return False

        diff = abs(level[i] - level[i - 1])
        if diff < 1 or diff > 3:
            return False
    return True


for level in input:
    for i in range(len(level)):
        newLev = level[::]
        del newLev[i]
        if checkSafe(newLev):
            sum += 1
            break


print(sum)
