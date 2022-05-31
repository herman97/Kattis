import sys

def solve(dictionary, words):
    for word in words:
        if word not in dictionary.keys():
            print("eh")
        else:
            print(dictionary[word])

def main():

    input = sys.stdin.readlines()

    #with open(sys.argv[1], 'r') as f:
    #    input = f.readlines()

    dictionary = dict()
    words = []
    blank = False

    for line in input:
        if line == "\n":
            blank = True
            continue
        if not blank:
            word, key = line[:-1].split()
            dictionary[key] = word
        else:
            words.append(line[:-1])

    solve(dictionary, words)

if __name__ == "__main__":
    main()