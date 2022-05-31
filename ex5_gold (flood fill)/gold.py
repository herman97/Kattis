import sys


"""
    Given a map with walls, traps, gold and a starting position, return the maximum number of gold that can be retrieved.
    The player can only move up, down, left or right. If the player is next to a trap it can only move back to where it came from.

    Uses flood fill to solve the problem.

"""


def solver(lista, start, borders):
    visited = [start]
    queue = [start]
    goldies = 0
    while(queue):
        curr_pos = queue.pop(0)

        if curr_pos[1] < 1 or curr_pos[1] > borders[0] - 1 or curr_pos[0] < 1 or curr_pos[0] > borders[1] - 1:
            # print("nonono")
            continue

        if lista[curr_pos[0]][curr_pos[1]] == 'G':
            # print(n)
            goldies += 1

        if lista[curr_pos[0]][curr_pos[1]] != '#' and lista[curr_pos[0]][curr_pos[1]] != 'T' and can_move(lista, curr_pos):
            if not (curr_pos[0], curr_pos[1]+1) in visited:
                # print(1)
                queue.append((curr_pos[0], curr_pos[1]+1))
                visited.append((curr_pos[0], curr_pos[1]+1))
            if not (curr_pos[0], curr_pos[1]-1) in visited:
                # print(2)
                queue.append((curr_pos[0], curr_pos[1]-1))
                visited.append((curr_pos[0], curr_pos[1]-1))
            if not (curr_pos[0]+1, curr_pos[1]) in visited:
                # print(3)
                queue.append((curr_pos[0]+1, curr_pos[1]))
                visited.append((curr_pos[0]+1, curr_pos[1]))
            if not (curr_pos[0]-1, curr_pos[1]) in visited:
                # print(4)
                queue.append((curr_pos[0]-1, curr_pos[1]))
                visited.append((curr_pos[0]-1, curr_pos[1]))

    print(goldies)


def can_move(lista, pos):

    if lista[pos[0]-1][pos[1]] == 'T' or lista[pos[0]+1][pos[1]] == 'T' or lista[pos[0]][pos[1]-1] == 'T' or lista[pos[0]][pos[1]+1] == 'T':
        return False
    return True


def main():
    if len(sys.argv) != 2:
        input = sys.stdin.readlines()
    else:
        with open(sys.argv[1], 'r') as f:
            input = f.read().splitlines()

    mapa = []
    start = (0, 0)
    borders = [i for i in map(int, input[0].split())]
    for line in range(1, len(input)):
        # print(input[line])
        row = [i for i in input[line]]
        if 'P' in row:
            start = (line-1, row.index('P'))

        mapa.append(row)

    solver(mapa, start, borders)


if __name__ == "__main__":
    main()
