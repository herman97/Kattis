"""
    Author: Herman Nordin
    Problem: Find the longest increasing subset in a sequence
    Time complexity: O(n log n), looping through all elements = n, binary search to find place = log n

"""
from sys import argv, stdin


class elem:
    def __init__(self, value, index, prev):
        self.index = index
        self.value = value
        self.prev_elem = prev


def solve(seq):
    lista = [elem(None, None, None)] * (len(seq) + 1)
    size = 0

    for x in range(len(seq)):
        low = 0
        high = size

        while low != high:
            mid = (low + high) // 2
            if lista[mid].value == None:
                high = mid
            if lista[mid].value < seq[x]:
                low = mid + 1
            else:
                high = mid

        if low == 0:
            e = elem(seq[x], x, None)
        else:
            e = elem(seq[x], x, lista[low-1])

        lista[low] = e
        size = max(low+1, size)

    biggest = elem(None, None, None)

    for e in lista:
        if e.value == None:
            continue
        if biggest.value == None or (not isinstance(e, int) and e.value > biggest.value):
            biggest = e
    print(26-size)


def main():
    if len(argv) != 2:
        input = stdin.readlines()
    else:
        with open(argv[1], 'r') as f:
            input = f.read().splitlines()

    inputs = [i for i in input[0]]
    solve(inputs)


if __name__ == "__main__":
    main()
