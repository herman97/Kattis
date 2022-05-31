import sys

""" NÅGOT FEL, fattar inte """


def solver(suffixes, size):
    word = ["$"]*size
    imp = False

    for index in suffixes:
        suffix = suffixes[index]
        placeholder = False
        for i in range(index, size):

            #print("out: ", *word, " out[i]: ", word[i], "Suff: ", suffix, " i:", i, " p:", index, " i-p: ", i-index, " suff[i-p]", suffix[i-index])

            if i-index < len(suffix) and (word[i] == "$" or word[i] == suffix[i-index]) and suffix[i-index] != "*":
                word[i] = suffix[i-index]
            elif i-index < len(suffix) and suffix[i-index] == "*":
                placeholder = True
                break
            else:
                imp = True

        if placeholder:
            c = size-1

            for i in range(len(suffix)-1, -1, -1):

                if (word[c] == "$" or word[c] == suffix[i]) and suffix[i] != "*":
                    word[c] = suffix[i]
                elif suffix[i] == "*":
                    break
                else:
                    imp = True

                c -= 1

    if imp:
        print("IMPOSSIBLE")
        return

    word1 = ""
    for w in word:
        word1 += w
        if w == "$":
            print("IMPOSSIBLE")
            return
    print(word1)


def solver2(suffixes, size):
    word = ["$"]*size
    imp = False
    for i in suffixes:
        star = False
        suffix = suffixes[i]

        for j in range(i, size):
            # for (j = i; j < size; j+= 1):
            if j-i >= len(suffix):
                s = ""
            else:
                s = suffix[j-i]

            if s == "*":
                star = True
                break
            elif word[j] != "$" and s != word[j]:
                imp = True
            else:
                word[j] = s

        if star:
            index = size-1
            for j in range(len(suffix)-1, -1, -1):
                #print ("suffix, j, suffix[j]", suffix, " ", j, " ", suffix[j], " index:", index)
                if suffix[j] == "*":
                    break
                elif word[index] != "$" and suffix[j] != word[index]:
                    imp = True
                else:
                    word[index] = suffix[j]
                index -= 1

    if imp:
        print("IMPOSSIBLE")
        return

    word1 = ""
    for w in word:
        word1 += w
        if w == "$":
            print("IMPOSSIBLE")
            return
    print(word1)


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
    suffixes = {}
    while(input):
        i = input.pop(0).split()
        length = int(i[0])
        num = int(i[1])
        for i in range(num):
            r = input.pop(0)
            index = int(r[0])
            string = r.split()[1]
            suffixes[index-1] = string
            #print(index, "ind, str: ", string)

        #solver(suffixes, length)
        #print ("---------")
        solver2(suffixes, length)
        suffixes = {}
        # print(suffixes)


if __name__ == "__main__":
    main()
