import sys

def part1():
    ans = 0
    for line in sys.stdin:
        line = line.strip()
        game = line.split(':')
        sets = game[1].split(';')
        ok = True
        for gameset in sets:
            cubes = gameset.split(',')
            for count in cubes:
                val, color = map(lambda x: x.strip(), count.split())
                val = int(val)
                if (color == "red" and val > 12)\
                    or (color == "green" and val > 13)\
                    or (color == "blue" and val > 14):
                        ok = False
                        break
        if ok: ans += int(game[0].split()[1].strip())
    return ans

def part2():
    ans = 0
    for line in sys.stdin:
        line = line.strip()
        game = line.split(':')
        sets = game[1].split(';')
        red, green, blue = 0, 0, 0
        for gameset in sets:
            cubes = gameset.split(',')
            for count in cubes:
                val, color = map(lambda x: x.strip(), count.split())
                val = int(val)
                if color == "red": red = max(red, val)
                elif color == "green": green = max(green, val)
                else: blue = max(blue, val)
        ans += red * green * blue
    return ans

print(part2())
