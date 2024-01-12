import sys
import networkx as nx


def part1(G, nodes):
    nodes = list(nodes)
    for i in range(len(nodes)):
        for j in range(i+1, len(nodes)):
            cut_value, partition = nx.minimum_cut(G, nodes[i], nodes[j])
            if cut_value == 3:
                return len(partition[0]) * len(partition[1])

def main():
    nodes = set()
    G = nx.Graph()
    for line in sys.stdin:
        line = line.strip().split()
        line[0] = line[0][:-1]
        nodes.add(line[0])
        for i in range(1,len(line)):
            G.add_edge(line[0], line[i], capacity=1.0)
            G.add_edge(line[i], line[0], capacity=1.0)
            nodes.add(line[i])

    print(part1(G, nodes))

main()
