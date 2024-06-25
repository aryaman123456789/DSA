class SimpleHashMap:
    def __init__ (self, size = 100):
        self.size = size
        self.buckets = [[] for _ in range(self.size)]
    def hash_function(self, key):
    # a simple hash function that sums the ASCII values of the characters only for numeric characters
    # and then takes the remainder when divided by 10
        numericSum = sum(ord(char) for char in key if char.isdigit())
        return numericSum % 10
    def put(self, key, value):
    # insert or update the value associated with the given key
        index = self.hash_function(key)
        bucket = self.buckets[index]
        for i, (k, _) in enumerate(bucket):
            if k == key:
                bucket[i] = (key, value)
                return
        bucket.append((key, value))
    def get(self, key):
    # find and return the value associated with the given key
        index = self.hash_function(key)
        bucket = self.buckets[index]
        for k, v in bucket:
            if k == key:
                return v
        return None
    def remove(self, key):
        index = self.hash_function(key)
        #finish later
    