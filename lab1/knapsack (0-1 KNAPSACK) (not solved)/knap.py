"""
    Author: Herman Nordin
    Problem:  

"""
from os import major
from sys import argv, stdin

def solve2(things, saved, curr, max_weight):
    """ Things = (value, weight, index) """

    if saved[max_weight][curr]:
        """ returning """
        return saved[max_weight][curr]
        
    if max_weight == 0 or not things or curr == len(saved[0]):
        maximum = (0, [])

    elif max_weight < things[0][1]:
        maximum = solve2(things[1:], saved, curr+1, max_weight)
        
    else:
        r1,l1 = solve2(things[1:], saved, curr+1, max_weight)
        r2,l2 = solve2(things[1:], saved, curr+1, max_weight-things[0][1])
        if r1 > r2 + things[0][0]:
            maximum = (r1, l1)
        else:
            maximum = (r2 + things[0][0], l2 + [things[0][2]])

    saved[max_weight][curr] = maximum
    return maximum

def solve(things, max_weight, curr):
    """ Thing = (value, weight, index) """
    keep = [[0] * (max_weight+1) for _y in range(len(things))]
    saved = [[0] * (max_weight+1) for _y in range(len(things))]
    
    for thing in range(len(things)):
        for weight in range(max_weight+1):
            if things[thing][1] <= weight and saved[thing-1][weight] < things[thing][0] + saved[thing-1][weight - things[thing][1]]:
                saved[thing][weight] = things[thing][0] + saved[thing-1][weight - things[thing][1]]
                keep[thing][weight] = 1
            else:
                saved[thing][weight] = saved[thing-1][weight]
                keep[thing][weight] = 0

    k = max_weight
    lista = []
    for i in range(len(things)-1, 0, -1):
        if keep[i][k] == 1:
            lista.insert(0,i)
            k -= things[i][1]
        if k == 0:
            break
    print(len(lista))
    print(*(lista))
    

def main():
    # Open used to read file locally or as input
    if len(argv) != 2:
        input = stdin.readlines()
    else:
        with open(argv[1], 'r') as f:
            input = f.read().splitlines()
    
    index = -1
    lista = []
    cap = num = -1
    for i in input:
        if index == -1:
            cap, num = map(int, i.split())
            index = 0
        else:
            value, weight = map(int, i.split())
            lista.append((value, weight, index))
            index += 1
            if index == num:
                solve(lista, cap, 0)
                index = -1
                lista = []
        

if __name__ == "__main__":
    main()
