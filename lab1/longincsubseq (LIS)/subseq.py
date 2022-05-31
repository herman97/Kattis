"""
    Author: Herman Nordin
    Problem: Find the longest strictly increasing subset in a sequence of numbers and output the indexes of the numbers in that sequence
    Time complexity: O(n log n), looping through all elements = n, binary search to find place = log n

"""
from sys import argv, stdin


class elem:
    def __init__(self, value, index, prev):
        self.index = index
        self.value = value
        self.prev_elem = prev

    def __str__(self) -> str:
        return "value: " + str(self.value) + " index: " + str(self.index)


def elemprint(elem):
    l = []
    while(True):
        if not elem or isinstance(elem, int):
            break
        l.append(elem.index)
        elem = elem.prev_elem
    if l:
        print(*reversed(l))


# https://www.cs.princeton.edu/courses/archive/spring13/cos423/lectures/LongestIncreasingSubsequence.pdf
# Solved using patience sort. Places values in piles where each pile is decreasing in value, if a value is bigger than a previous piles top value it is put in a new pile
# with a pointer to the pile befores lowest value (the one on the top of the pile).
# When all cards are values are sorted into piles the number of piles represent the length of the sequence
# and the sequence itself (or one sequence) is following the last piles top card pointers to the first pile.
def solve2(seq):
    lista = [elem(None, None, None)] * (len(seq) + 1)
    size = 0

    for x in range(len(seq)):
        low = 0
        high = size

        # Binary search to find where to insert elem in lista
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
        print(e)
        if e.value == None:
            continue
        if biggest.value == None or (not isinstance(e, int) and e.value > biggest.value):
            biggest = e
    print(size)
    elemprint(biggest)


def main():
    # Open used to read file locally or as input
    if len(argv) != 2:
        input = stdin.readlines()
    else:
        with open(argv[1], 'r') as f:
            input = f.read().splitlines()

    inputs = []
    num = -1
    for inp in input:
        inputs = [i for i in map(int, inp.split())]
        if num == -1:
            num = 0
        else:
            solve2(inputs)
            inputs = []
            num = -1


if __name__ == "__main__":
    main()
