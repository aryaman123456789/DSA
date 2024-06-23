class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

node1 = Node(1)
node2 = Node(2)
node3 = Node(3)
node4 = Node(4)

node1.next = node2
node2.next = node3
node3.next = node4
node4.next = node1

currentNode = node1
startingNode = node1

print(currentNode.data, end = " -> ")
currentNode = currentNode.next
while currentNode != startingNode:
    print(currentNode.data, end = " -> ")
    currentNode = currentNode.next
print("...")