from collections import defaultdict


def getInput():
    f = open("input", "r")

    board = []

    for line in f:
        board.append(list(line[: len(line) - 1]))

    f.close()
    return board


def getPos(input):
    for r in range(len(input)):
        for c in range(len(input[0])):
            if input[r][c] == "^":
                return [r, c]

    return [-1, -1]


def getMoveSum(input):
    sum = 0
    for r in range(len(input)):
        for c in range(len(input[0])):
            if input[r][c] == "X":
                sum += 1

    return sum


def part1(input):
    pos = getPos(input)
    direction = 0
    m, n = len(input), len(input[0])

    while pos[0] >= 0 and pos[0] < m and pos[1] >= 0 and pos[1] < n:
        input[pos[0]][pos[1]] = "X"

        match direction:
            case 0:
                if pos[0] - 1 >= 0 and input[pos[0] - 1][pos[1]] == "#":
                    direction = 1
                else:
                    pos[0] -= 1
            case 1:
                if pos[1] + 1 < n and input[pos[0]][pos[1] + 1] == "#":
                    direction = 2
                else:
                    pos[1] += 1
            case 2:
                if pos[0] + 1 < m and input[pos[0] + 1][pos[1]] == "#":
                    direction = 3
                else:
                    pos[0] += 1
            case 3:
                if pos[1] - 1 >= 0 and input[pos[0]][pos[1] - 1] == "#":
                    direction = 0
                else:
                    pos[1] -= 1

    return getMoveSum(input)


def part2(input):
    m, n = len(input), len(input[0])
    startPos = getPos(input)

    sum = 0
    for r in range(m):
        for c in range(n):
            if input[r][c] == "#" or (r == startPos[0] and c == startPos[1]):
                continue

            input[r][c] = "O"
            count = 0
            direction = 0
            pos = [startPos[0], startPos[1]]

            while (
                pos[0] >= 0
                and pos[0] < m
                and pos[1] >= 0
                and pos[1] < n
                and count < m * n
            ):
                count += 1

                match direction:
                    case 0:
                        if pos[0] - 1 >= 0 and input[pos[0] - 1][pos[1]] in "#O":
                            direction = 1
                        else:
                            pos[0] -= 1
                    case 1:
                        if pos[1] + 1 < n and input[pos[0]][pos[1] + 1] in "#O":
                            direction = 2
                        else:
                            pos[1] += 1
                    case 2:
                        if pos[0] + 1 < m and input[pos[0] + 1][pos[1]] in "#O":
                            direction = 3
                        else:
                            pos[0] += 1
                    case 3:
                        if pos[1] - 1 >= 0 and input[pos[0]][pos[1] - 1] in "#O":
                            direction = 0
                        else:
                            pos[1] -= 1

            print(count)
            if count >= m * n:
                sum += 1

            input[r][c] = "."

    return sum


def main():
    board = getInput()

    # print(part1(board))
    print(part2(board))


main()
