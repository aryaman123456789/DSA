class Node:
    def __init__ (self, data):
        self.data = data
        self.next = None

def traverse(head):
    currentNode = head
    while currentNode:
        print(currentNode.data, end = " -> ")
        currentNode = currentNode.next
    print("Null")

def deleteSpecificNode(head, nodeToDelete):
    if head == nodeToDelete:
        return head.next
    currentNode = head
    while currentNode.next and currentNode.next != nodeToDelete:
        currentNode = currentNode.next
    if currentNode.next is None:
        return head
    currentNode.next = currentNode.next.next
    return head

node1 = Node(7)
node2 = Node(11)
node3 = Node(3)
node4 = Node(2)
node5 = Node(9)

node1.next = node2
node2.next = node3
node3.next = node4
node4.next = node5

print("Original Linked List:")
traverse(node1)

node1 = deleteSpecificNode(node1, node1)
print("\nLinked List after deleting node 1:")
traverse(node1)