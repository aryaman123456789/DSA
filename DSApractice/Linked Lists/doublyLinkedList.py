#create a class node to represent the data, and the paths forward and backwards (next and prev)
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.prev = None

#create nodes
node1 = Node(1)
node2 = Node(2)
node3 = Node(3)
node4 = Node(4)

#create the links
node1.next = node2

node2.prev = node1
node2.next = node3

node3.prev = node2
node3.next = node4

node4.prev = node3

#traverse the list forwards
def traverse_forward(head):
    current_node = head
    print("Traversing in forward order:  ")
    while current_node:
        print(current_node.data, end = " -> ")
        current_node = current_node.next
    print("Null")

#traverse the list backwards
def traverse_backward(tail):
    current_node = tail
    print("Traversing in reverse order:  ")
    while current_node:
        print(current_node.data, end = " <- ")
        current_node = current_node.prev
    print("Null")

#traverse the list forward (from head node1) and backward (from tail node4)
traverse_forward(node1)
traverse_backward(node4)

