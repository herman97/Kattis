"""
    Author: Herman Nordin
    Problem: Find a minimal set of intervals that cover a given goal interval
    Time complexity: O(n log n)

"""
import sys


# Class for every interval
class inter:
    def __init__(self, a, b, index):
        self.min = a
        self.max = b
        self.index = index

    def __str__(self) -> str:
        return str(self.min) + " " + str(self.max) + " \n"

# Solve uses a greedy algorithm to find a interval that covers the previous min
# and so far to the right as possible (cover the largest interval)


def solve(intervals, goal):
    intervals.sort(key=lambda x: x.max)

    if intervals[-1].max < goal.max:
        print("impossible")
        return

    curr = []
    currel = None
    currmin = goal.min
    count_while = 0
    count_for = 0
    while(True):
        count_while += 1
        for elem in reversed(intervals):
            count_for += 1
            if elem.min <= currmin:
                currel = elem
                curr.append(currel)
                break

        if currel:
            intervals.remove(currel)
            currmin = currel.max
            if currmin >= goal.max:
                break
            currel = None
        else:
            break

    if not curr or curr[0].min > goal.min or curr[-1].max < goal.max:
        print("impossible")
    else:
        print(len(curr))
        for e in curr:
            print(e.index, end=" ")
        print()


def main():

    #input = sys.stdin.readlines()
    # Used to read from a file locally
    with open(sys.argv[1], 'r') as f:
        input = f.read().splitlines()

    lista = []
    c = -1
    num_inputs = 0
    goal = tuple()
    # Reads input, if c == -1 its the goal interval to cover
    # if c == 0 its the number of intervals we have
    # if c == num_inputs we are on the last interval we should read
    # else its a normal interval to read
    for line in input:
        if c == -1:
            a, b = line.split()
            goal = inter(float(a), float(b), None)

        elif c == 0:
            num_inputs = int(line)

        elif c == num_inputs:
            a, b = line.split()
            ival = inter(float(a), float(b), c-1)
            lista.append(ival)
            solve(lista, goal)
            goal = None
            lista = []
            c = -2
        elif len(line) != 1:
            a, b = line.split()
            ival = inter(float(a), float(b), c-1)
            lista.append(ival)

        c += 1


if __name__ == "__main__":
    main()
