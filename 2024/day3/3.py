f = open("input", "r")

input = []

for line in f:
    input.append(line)

f.close()


numList = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "0"]

mulList = []

for line in input:
    text = ""
    num1, num2 = "", ""
    i = 0
    while i < len(line) - 4:
        if line[i : i + 4] == "mul(":
            j = i + 4
            while j < len(line) and j - (i + 4) < 9:
                if line[j] == ")":
                    break
                j += 1
            if j - (i + 4) < 9:
                num1, num2 = "", ""
                comma = 0
                valid = True
                for k in range(i + 4, j):
                    if (line[k] not in numList and line[k] != ",") or (
                        line[k] == "," and len(num1) == 0
                    ):
                        valid = False
                        break
                    if line[k] == ",":
                        comma += 1
                    else:
                        if comma == 0:
                            num1 += line[k]
                        elif comma == 1:
                            num2 += line[k]
                        else:
                            valid = False
                            break

                if (
                    valid
                    and len(num1) > 0
                    and len(num2) > 0
                    and len(num1) <= 3
                    and len(num2) <= 3
                    and comma == 1
                ):

                    mulList.append([int(num1), int(num2)])
                    i = j

        i += 1

sum = 0

for num1, num2 in mulList:
    sum += num1 * num2

print(sum)
