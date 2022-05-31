import sys

"""
    Find the shortest path for a knight to the edge of a chess board.
    Uses search algorithm.
"""

converter = {"a": 0, "b": 1, "c": 2, "d": 3, "e": 4, "f": 5, "g": 6, "h": 7}
reconverter = {0: "a", 1: "b", 2: "c", 3: "d", 4: "e", 5: "f", 6: "g", 7: "h"}


def solver(nodes):

    for n in nodes:
        cost = []
        prev = []
        q = []
        for x in range(8):
            tempc = []
            tempp = []
            for y in range(8):
                tempc.append(sys.maxsize)
                tempp.append(None)
                q.append((x, y))
            cost.append(tempc)
            prev.append(tempp)

        cost[n[0]][n[1]] = 0

        while q:
            u = None
            for t in q:
                if u == None or cost[t[0]][t[1]] < cost[u[0]][u[1]]:
                    u = t

            q.remove(u)

            for n in get_neighbour(u):
                alt = cost[u[0]][u[1]] + 1
                if alt < cost[n[0]][n[1]]:
                    cost[n[0]][n[1]] = alt
                    prev[n[0]][n[1]] = u

        d = {}
        ma = -1
        for x in range(8):
            for y in range(8):
                a = cost[x][y]
                if a >= ma:
                    ma = a
                else:
                    continue
                if not a in d.keys():
                    d[a] = [(reconverter[x], y+1)]
                else:
                    d[a].append((reconverter[x], y+1))

        a = d[ma]

        a.sort(key=lambda x: (-x[1], x[0]))
        print(ma, end=" ")
        for e in a:
            s = e[0] + str(e[1])
            print(s, end=" ")
        print()


def get_neighbour(node):
    nx = node[0]
    ny = node[1]
    neigh = []

    for x in range(-2, 3):
        for y in range(-2, 3):
            if ((x == -2 or x == 2) and (y == -1 or y == 1)) or ((y == -2 or y == 2) and (x == -1 or x == 1)):
                tx = nx + x
                ty = ny + y
                if tx > 7 or tx < 0 or ty < 0 or ty > 7:
                    continue
                neigh.append((tx, ty))

    return neigh


def main():
    if len(sys.argv) != 2:
        input = sys.stdin.readlines()
    else:
        with open(sys.argv[1], 'r') as f:
            input = f.read().splitlines()

    num_probs = input.pop(0)
    nodes = []

    while(input):
        s = [a for a in input.pop(0)]
        nodes.append((int(converter[s[0]]), int(s[1])-1))

    solver(nodes)


if __name__ == "__main__":
    main()
