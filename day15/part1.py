
def hash(s):
    val = 0
    for c in s:
        val += ord(c)
        val *= 17
        val %= 256
    return val

def part1():
    data = input().split(',')
    hashes = map(hash, data)
    return sum(hashes)

print(part1())
