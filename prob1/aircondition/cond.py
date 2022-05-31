"""
    Author: Herman Nordin

"""
from sys import argv, stdin


def solve(seq):
    lista = []

    for x in range(len(seq)):
        c = 0
        for i in range(len(lista)):
            if(min(lista[i][1], seq[x][1]) - max(lista[i][0], seq[x][0]) >= 0):
                a = max(lista[i][0], seq[x][0])
                b = min(lista[i][1], seq[x][1])
                lista[i] = (a, b)
                c = -1
                break

            c = 0

        if c == 0:
            lista.append(seq[x])
    print(len(lista))


def main():

    if len(argv) != 2:
        input = stdin.readlines()
    else:
        with open(argv[1], 'r') as f:
            input = f.read().splitlines()

    lista = []

    for i in input[1:]:
        a, b = map(int, i.split())
        lista.append((a, b))

    lista.sort(key=lambda k: k[0])
    solve(lista)


if __name__ == "__main__":
    main()
