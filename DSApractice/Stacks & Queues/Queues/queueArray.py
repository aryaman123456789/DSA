class Queue:
    def __init__(self):
        self.queue = []
    def enqueue(self, element):
        self.queue.append(element)
    def dequeue(self):
        if len(self.queue) == 0:
            return "Queue is empty"
        return self.queue.pop(0)
    def peek(self):
        if len(self.queue) == 0:
            return "Queue is empty"
        return self.queue[0]
    def is_empty(self):
        return len(self.queue) == 0
    def size(self):
        return len(self.queue)
    
myQueue = Queue()

myQueue.enqueue('A')
myQueue.enqueue('B')
myQueue.enqueue('C')
print("Queue: ", myQueue.queue)

print("Dequeue: ", myQueue.dequeue())

print("Peek: ", myQueue.peek())

print("isEmpty: ", myQueue.is_empty())

print("Size: ", myQueue.size())