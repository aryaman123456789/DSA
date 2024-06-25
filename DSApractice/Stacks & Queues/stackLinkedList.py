class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
class Stack:
    def __init__(self):
        self.head = None
        self.size = 0
    def push(self, data):
        newNode = Node(data)
        if self.head:
            newNode.next = self.head
        self.head = newNode
        self.size += 1
    def pop(self):
        if self.is_empty():
            return "Stack is empty"
        poppedNode = self.head
        self.head = self.head.next
        self.size -= 1
        return poppedNode.data
    def peek(self):
        if self.is_empty():
            return "Stack is empty"
        return self.head.data
    def is_empty(self):
        return self.size == 0
    def sizeOf(self):
        return self.size
    def traverse(self):
        current_node = self.head
        while current_node:
            print(current_node.data, end = " -> ")
            current_node = current_node.next
        print("Null")
        
    
myStack = Stack()
myStack.push('A')
myStack.push('B')
myStack.push('C')

print("Stack: ", myStack.traverse())
print("Pop: ", myStack.pop())
print("Peek: ", myStack.peek())
print("isEmpty: ", myStack.is_empty())
print("Size: ", myStack.sizeOf())