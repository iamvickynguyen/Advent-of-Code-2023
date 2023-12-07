import sys
from bisect import bisect_left

seeds = list(map(int, input().split(':')[1].strip().split()))
seed_soil = []
soil_fert = []
fert_water = []
water_light = []
light_temp = []
temp_hum = []
hum_loc = []

def init_map(category):
    val = sys.stdin.readline().strip()
    while val != "":
        dest, src, dist = map(int, val.split())
        category.append((src, dest, dist))
        val = sys.stdin.readline().strip()
    category.sort(key=lambda x: x[0])

def init():
    line = sys.stdin.readline()
    line = sys.stdin.readline().strip()
    while line:
        if line == "seed-to-soil map:": init_map(seed_soil)
        elif line == "soil-to-fertilizer map:": init_map(soil_fert)
        elif line == "fertilizer-to-water map:": init_map(fert_water)
        elif line == "water-to-light map:": init_map(water_light)
        elif line == "light-to-temperature map:": init_map(light_temp)
        elif line == "temperature-to-humidity map:": init_map(temp_hum)
        elif line == "humidity-to-location map:": init_map(hum_loc)
        line = sys.stdin.readline().strip()

# binary search
def find_target(category, x):
    i = bisect_left(category, (x,))
    (src, dest, dist) = (0, 0, 0)
    if i == 0:
        if category[0][0] > x: return x
        (src, dest, dist) = category[0]
    elif i < len(category) and category[i][0] == x: (src, dest, dist) = category[i]
    else: (src, dest, dist) = category[i-1]
    if src + dist < x: return x
    return x - src + dest

def find_loc(seed):
    soil = find_target(seed_soil, seed)
    fert = find_target(soil_fert, soil)
    water = find_target(fert_water, fert)
    light = find_target(water_light, water)
    temp = find_target(light_temp, light)
    hum = find_target(temp_hum, temp)
    loc = find_target(hum_loc, hum)
    return loc

def part1():
    init()
    return min(map(lambda s: find_loc(s), seeds))

print(part1())
