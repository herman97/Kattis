"""
    Author: Herman Nordin
    Problem:  Find the maximum money saved given a three for two deal.

"""
from sys import argv, stdin


def solve(items):
    saved = 0
    count = 1
    for i in range(len(items)):
        if count % 3 == 0:
            saved += items[i]
        count += 1

    print(saved)


def main():
    # Open used to read file locally or as input
    if len(argv) != 2:
        input = stdin.readlines()
    else:
        with open(argv[1], 'r') as f:
            input = f.read().splitlines()

    items = [i for i in map(int, input[1].split())]
    items.sort(reverse=True)
    solve(items)


if __name__ == "__main__":
    main()
