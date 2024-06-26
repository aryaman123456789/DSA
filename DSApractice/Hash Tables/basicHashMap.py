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
        bucket = self.buckets[index]
        for i, (k, _) in enumerate(bucket):
            if k == key:
                del bucket[i]
                return
    def print_map(self):
        print("Hash Map:")
        for index, bucket in enumerate(self.buckets):
            print(f"Bucket {index}: {bucket}")
    
# Creating the Hash Map from the simulation
hash_map = SimpleHashMap(size=10)

# Adding some entries
hash_map.put("123-4567", "Charlotte")
hash_map.put("123-4568", "Thomas")
hash_map.put("123-4569", "Jens")
hash_map.put("123-4570", "Peter")
hash_map.put("123-4571", "Lisa")
hash_map.put("123-4672", "Adele")
hash_map.put("123-4573", "Michaela")
hash_map.put("123-6574", "Bob")

hash_map.print_map()

# Demonstrating retrieval
print("\nName associated with '123-4570':", hash_map.get("123-4570"))

print("Updating the name for '123-4570' to 'James'")
hash_map.put("123-4570","James")

# Checking if Peter is still there
print("Name associated with '123-4570':", hash_map.get("123-4570"))
    