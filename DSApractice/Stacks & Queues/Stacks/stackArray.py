class Stack:
    def __init__(self):
        self.stack = []
    def push(self, element):
        self.stack.append(element)
    def pop(self):
        if len(self.stack) == 0:
            return "Stack is empty"
        return self.stack.pop() #remove and return the last element
    def peek(self):
        if len(self.stack) == 0:
            return "Stack is empty"
        return self.stack[-1]
    def is_empty(self):
        return len(self.stack) == 0
    def size(self):
        return len(self.stack)
    
myStack = Stack()

myStack.push('A')
myStack.push('B')
myStack.push('C')
print("Stack: ", myStack.stack)

print("Pop: ", myStack.pop())
print("Stack after pop: ", myStack.stack)

print("Peek: ", myStack.peek())

print("isEmpty: ", myStack.is_empty())

print("Size: ", myStack.size())