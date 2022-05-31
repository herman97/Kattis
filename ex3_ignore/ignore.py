import sys

"""
    Print the Kth number a display will show. The display is upside down so not all numbers will be real numbers.

    Base 7 numbers.

"""

numbers = ['1', '2', '5', '9', '8', '6', '0']


def ignore(lista):
    for elem in lista:
        show(elem)


def show(number):
    x = number
    p = ""
    while (x):
        p += numbers[x % 7 - 1]
        x //= 7

    print(p)


def main():

    #input = sys.stdin.readlines()
    with open(sys.argv[1], 'r') as f:
        input = f.read().splitlines()

    lista = []
    for line in map(int, input):
        lista.append(line)

    ignore(lista)


if __name__ == "__main__":
    main()
