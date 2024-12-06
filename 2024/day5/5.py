from collections import defaultdict


def getInput():
    f = open("input", "r")

    rules = []

    logs = []

    for line in f:
        if "|" in line:
            rules.append([int(x) for x in line.split("|")])
        if "," in line:
            logs.append([int(x) for x in line.split(",")])

    f.close()
    return rules, logs


def checkOrder(log, rules):
    indexMap = {}
    for i, l in enumerate(log):
        indexMap[l] = i

    for a, b in rules:
        if a in indexMap and b in indexMap and indexMap[b] < indexMap[a]:
            return False

    return True


def dfs(node, adj, visited, stack, log):
    if node in visited or node not in log:
        return

    visited.add(node)
    for a in adj[node]:
        dfs(a, adj, visited, stack, log)

    stack.append(node)


def topologicalSort(log, adj):
    stack = []

    visited = set()

    for l in log:
        dfs(l, adj, visited, stack, log)

    return [stack[i] for i in range(len(stack) - 1, -1, -1)]


def main():
    rules, logs = getInput()

    sum1 = 0
    sum2 = 0

    adj = defaultdict(list)
    for a, b in rules:
        adj[a].append(b)

    for a, b in adj.items():
        print(f"{a} {b}")

    for log in logs:
        if checkOrder(log, rules):
            sum1 += log[len(log) // 2]
        else:
            log = topologicalSort(log, adj)

            sum2 += log[len(log) // 2]

    print(sum1)
    print(sum2)


main()
