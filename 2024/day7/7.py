import sys
from collections import defaultdict


def getInput(filename):
    f = open(filename, "r")

    result = []
    equation = []

    for line in f:
        index = line.index(":")
        result.append(int(line[:index]))
        equation.append([int(i) for i in line[index + 1 :].split()])

    f.close()
    return result, equation


def backtrack(index, total, result, equation):
    if index == len(equation):
        return total == result

    add = backtrack(index + 1, total + equation[index], result, equation)
    mult = backtrack(index + 1, total * equation[index], result, equation)

    concantTotal = int(str(total) + str(equation[index]))
    concant = backtrack(index + 1, concantTotal, result, equation)

    return add or mult or concant


def part1(result, equation):
    sum = 0

    for i in range(len(result)):

        index = 0
        total = 0
        if backtrack(index, total, result[i], equation[i]):
            sum += result[i]

    return sum


def main():
    if len(sys.argv) != 2:
        print("Must add file")
        exit()

    result, equation = getInput(sys.argv[1])

    print(part1(result, equation))


main()
