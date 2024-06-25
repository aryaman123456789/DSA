from typing import Any


class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
class Queue:
    def __init__(self):
        self.front = None
        self.rear = None
        self.size = 0
    def enqueue(self, data):
        newNode = Node(data)
        if self.rear is None:
            self.front = self.rear = newNode
            self.size += 1
            return
        self.rear.next = newNode
        self.rear = newNode
        self.size += 1
    def dequeue(self):
        if self.is_empty():
            return "Queue is empty"
        dequeuedNode = self.front
        if self.front == self.rear:
            self.front = self.rear = None
        else:
            self.front = self.front.next
        self.size -= 1
        return dequeuedNode.data
    def peek(self):
        if self.is_empty():
            return "Queue is empty"
        return self.front.data
    def is_empty(self):
        return self.size == 0
    def sizeOf(self):
        return self.size
    def printQueue(self):
        temp = self.front
        while temp:
            print(temp.data, end=" ")
            temp = temp.next
        print()

myQueue = Queue()

myQueue.enqueue('A')
myQueue.enqueue('B')
myQueue.enqueue('C')
print("Queue: ", end="")
myQueue.printQueue()

print("Dequeue: ", myQueue.dequeue())

print("Peek: ", myQueue.peek())

print("isEmpty: ", myQueue.is_empty())

print("Size: ", myQueue.sizeOf())
    
    