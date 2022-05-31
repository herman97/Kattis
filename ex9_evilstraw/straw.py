import sys

"""
    See if possbile to generade a plaindrome for a given number of letters and print the number of swaps needed for it to become a palindrome.

    Stat by looking at the word from left and right, if they are the same, continue with the next letters towards the center.
    If they are not the same, look from left and right until the first matchin charcter is found and switch places.

    a b c c a
    a b c c a
    a c b c a

"""


def solver(word):

    left = 0
    right = len(word) - 1
    count = 0
    while left <= right:

        if word[left] != word[right]:
            left2 = left + 1
            right2 = right - 1
            c = False

            while (left2 < right and right2 >= left):

                if word[left2] == word[right]:
                    count += left2-left
                    word = word[0:left] + word[left2] + \
                        word[left:left2] + word[left2+1:]
                    c = True
                    break

                elif word[right2] == word[left]:
                    count += right-right2
                    word = word[0:right2] + word[right2 +
                                                 1:right+1] + word[right2] + word[right+1:]
                    c = True
                    break

                left2 += 1
                right2 -= 1
            if not c:
                print("Impossible")
                return 1

        else:
            left += 1
            right -= 1

    print(count)
    return 1


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

    for word in input:
        solver(word)


if __name__ == "__main__":
    main()
