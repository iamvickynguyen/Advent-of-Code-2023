import sys
import re

def get_next(data, conds):
    for cond in conds:
        if len(cond) == 1: return cond[-1]
        else:
            c, sign, threshold, label = cond
            if c in data:
                if (sign == '<' and data[c] < threshold) or (sign == '>' and data[c] > threshold):
                    return label

    return conds[-1][-1]

workflows = {}

for line in sys.stdin:
    if not line.strip(): break

    name = re.search(r"^(.*?)\{", line).group(1)
    conditions = re.search(r"\{(.*?)\}", line).group(1).split(',')
    conds = []
    for cond in conditions:
        data = cond.split(':')
        if len(data) < 2: conds.append(data)
        else:
            pred, label = data[0], data[1]
            conds.append([pred[0], pred[1], int(pred[2:]), label])
    workflows[name] = conds

count = 0
for line in sys.stdin:
    data = line[1:-2].split(',')
    data = {x[0]:int(x[1]) for x in map(lambda y: y.split('='), data)}
    
    label = 'in'
    while label != 'A' and label != 'R':
        label = get_next(data, workflows[label])
        if label == 'A':
            count += sum(data.values()) 

print(count)

