import sys

"""
    Calculate the expected winnings of a player. The prize is doubled if an answer is correct and if wrong the player gets nothing.
    The probability of answering a question correctly is given with every question.
"""

# https://algorithmist.com/wiki/UVa_10900_-_So_you_want_to_be_a_2n-aire%3F


def solver2(n, t):
    next_win = 2**n
    for i in range(n-1, -1, -1):
        stop_win = 2**i
        bp = stop_win/next_win

        if bp < t:
            next_win = (1+t) / 2 * next_win
        else:
            next_win = stop_win * (bp-t) / (1-t) + \
                next_win*(bp+1)/2*(1-bp)/(1-t)

    print("{:.3f}".format(next_win))


def main():
    input = []
    if len(sys.argv) != 2:
        a = sys.stdin.readlines()
        for i in a:
            input.append(i[:-1])
    else:
        with open(sys.argv[1], 'r') as f:
            input = f.read().splitlines()

    while input:
        n, t = input.pop(0).split()
        n = int(n)
        t = float(t)
        if n == 0 and t == 0:
            break
        solver2(n, t)


if __name__ == "__main__":
    main()
