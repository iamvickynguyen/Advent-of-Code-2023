import sys

def part1():
    ans = 0
    for line in sys.stdin:
        line = line.split(':')[1]
        winning_lst, cards = map(lambda x: map(int, x.split()), line.strip().split('|'))
        winning_lst = set(winning_lst)
        matches = sum([1 if x in winning_lst else 0 for x in cards])
        if matches > 0:
            ans += pow(2, matches - 1)
    return ans

def part2():
    scratchcards = []
    for line in sys.stdin:
        line = line.split(':')[1]
        winning_lst, cards = map(lambda x: map(int, x.split()), line.strip().split('|'))
        winning_lst = set(winning_lst)
        matches = sum([1 if x in winning_lst else 0 for x in cards])
        scratchcards.append(matches)

    ans = 0
    count = [0] * len(scratchcards)
    for i, val in enumerate(count):
        copies = val + 1 
        ans += copies
        for j in range(scratchcards[i]):
            pos = (i + j + 1) % len(scratchcards)
            count[pos] += copies
    return ans

#print(part1())
print(part2())
