class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.prev = None

node1 = Node(1)
node2 = Node(2)
node3 = Node(3)
node4 = Node(4)

node1.prev = node4
node1.next = node2

node2.prev = node1
node2.next = node3

node3.prev = node2
node3.next = node4

node4.prev = node3
node4.next = node1

def traverse_forward(head):
    current_node = head
    startingNode = head
    print("Traversing in forward order:  ")
    print(current_node.data, end = " -> ")
    current_node = current_node.next
    while current_node != startingNode:
        print(current_node.data, end = " -> ")
        current_node = current_node.next
    print("...")

def traverse_backward(tail):
    current_node = tail
    startingNode = tail
    print("Traversing in reverse order:  ")
    print(current_node.data, end = " <- ")
    current_node = current_node.prev
    while current_node != startingNode:
        print(current_node.data, end = " <- ")
        current_node = current_node.prev
    print("...")


traverse_forward(node1)
traverse_backward(node4)