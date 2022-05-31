import sys
import math

"""
    Find the smallest distance between two polygons and return a radius that can fit in this distance.

"""


class line:
    node1 = (0, 0)
    node2 = (0, 0)

    def __init__(self, n1, n2):
        self.node1 = n1
        self.node2 = n2

    def __repr__(self):
        return str(self)

    def __str__(self):
        return "n1: " + str(self.node1[0]) + ":" + str(self.node1[1]) + " n2: " + str(self.node2[0]) + ":" + str(self.node2[1])


def get_dist(p, l):
    # https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line

    x0, y0 = p
    x1, y1 = l.node1
    x2, y2 = l.node2

    a = y1-y2
    b = x2-x1
    c = x1*y2-x2*y1

    dist = (abs(a*x0+b*y0+c)) / (math.sqrt(a**2 + b**2))

    max_y = max(y1, y2)
    min_y = min(y1, y2)
    max_x = max(x1, x2)
    min_x = min(x1, x2)

    x = (b*(b*x0 - a*y0) - a*c) / (a**2 + b**2)
    y = (a*(-b*x0 + a*y0) - b*c) / (a**2 + b**2)

    if max_y >= y >= min_y and max_x >= x >= min_x:
        return dist/2
    else:
        dd = math.sqrt((x1-x0)**2 + (y1-y0)**2)
        dd2 = math.sqrt((x2-x0)**2 + (y2-y0)**2)
        return min(dd, dd2)/2


def create_lines(nodes):
    lines = []
    for i in range(len(nodes)):
        if i != len(nodes) - 1:
            lines.append(line(nodes[i], nodes[i+1]))
        else:
            lines.append(line(nodes[i], nodes[0]))

    return lines


def solver(inner_nodes, outer_nodes):
    inner_lines = create_lines(inner_nodes)
    outer_lines = create_lines(outer_nodes)

    min_dist = -1

    for node in inner_nodes:
        for line in outer_lines:
            if min_dist == -1:
                min_dist = get_dist(node, line)
            else:
                min_dist = min(get_dist(node, line), min_dist)

    for node in outer_nodes:
        for line in inner_lines:
            min_dist = min(get_dist(node, line), min_dist)

    print(min_dist)


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

    while input:
        num_inner = int(input.pop(0))
        inner_nodes = []

        for i in range(num_inner):
            n1, n2 = input.pop(0).split()
            inner_nodes.append((int(n1), int(n2)))

        num_outer = int(input.pop(0))
        outer_nodes = []
        for i in range(num_outer):
            n1, n2 = input.pop(0).split()
            outer_nodes.append((int(n1), int(n2)))

        solver(inner_nodes, outer_nodes)


if __name__ == "__main__":
    main()
