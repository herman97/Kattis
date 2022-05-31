import sys

"""
    Determine if a number is a happy prime, eg. a number that reduces to one when you take the sum of the square of its digits and continue 
    iterating until it yields 1.

    If it does not yield 1 it is not happy.
"""


def is_prime(x):
    if x < 2:
        return False
    elif x <= 3:
        return True

    if x % 2 == 0 or x % 3 == 0:
        return False

    for i in range(25, x+1, 6):
        if x % i**0.5 == 0 or x % i*0.5 + 2 == 0:
            return False

    return True


def solver(id, og_num):

    if not is_prime(og_num):
        print(id, og_num, "NO")
        return

    cycle = []
    num = og_num
    while num > 1:
        s = 0
        for d in str(num):
            s += int(d)**2

        if s in cycle:
            print(id, og_num, "NO")
            return
        cycle.append(s)
        num = s

    if (num == 1):
        print(id, og_num, "YES")
        return
    print(id, og_num, "NO")


def main():
    input = []
    if len(sys.argv) != 2:
        a = sys.stdin.readlines()
        for i in a:
            input.append(i[:-1])
    else:
        with open(sys.argv[1], 'r') as f:
            input = f.read().splitlines()

    input.pop(0)

    while(input):
        id, num = input.pop(0).split()
        solver(id, int(num))


if __name__ == "__main__":
    main()
