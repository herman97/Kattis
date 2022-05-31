import sys


# calculates anger. Difference of what a kid wants and what they get squared.
def anger(gets, wants):
    anger = 0
    for i in range(len(gets)):
        diff = wants[i] - gets[i]
        anger += diff**2
    print(anger)


# sub is how many each kid should remove to remove same from all
# if there is still candies left after we iterate and remove until diff == 0 (we give as many as we have)
def calculate(get, diff):
    if diff != 0:
        while(True):
            sub = int(diff/len(get))
            if sub == 0:
                sub = 1
            for i in range(len(get)):
                if diff == 0:
                    break

                if get[i] == 0:
                    continue
                if get[i] - sub < 0:
                    diff -= get[i]
                    get[i] -= get[i]
                else:
                    get[i] -= sub
                    diff -= sub
            if diff == 0:
                break


# takes the difference of wanted candies and how many we have
def solve(wants, candies, gets):
    diff = sum(wants) - candies
    calculate(gets, diff)
    anger(gets, wants)


# takes input and puts it in variables and calls the solver
def main():
    candies = 0
    kids = 0
    wants = []
    gets = []

    # input = sys.stdin.readlines()

    with open(sys.argv[1], 'r') as f:
        input = f.readlines()

    for line in input:
        if candies == 0 or kids == 0:
            candies, kids = map(int, line.split())
        else:
            wants.append(int(line[:-1]))
            gets.append(int(line[:-1]))

    wants.sort()
    gets.sort()
    solve(wants, candies, gets)


if __name__ == "__main__":
    main()
