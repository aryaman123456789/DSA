class SimpleHashSet:
    def __init__(self, size = 100):
        self.size = size
        self.buckets = [[] for _ in range(size)]
    def hash_function(self, value):
        # a simple hash function that sums the ASCII values of the characters 
        # in the value and returns the remainder when divided by the number of buckets
        return sum(ord(char) for char in value) % self.size
    def add(self, value):
        # add the value to the hash set by calculating its hash index and adding it to the bucket
        index = self.hash_function(value)
        bucket = self.buckets[index]
        if value not in bucket:
            bucket.append(value)
    def contains(self, value):
        # check if the value is in the hash set by calculating its hash index 
        # and checking if it exists in the bucket
        index = self.hash_function(value)
        bucket = self.buckets[index]
        return value in bucket
    def remove(self, value):
        index = self.hash_function(value)
        bucket = self.buckets[index]
        if value in bucket:
            bucket.remove(value)
    def print_set(self):
        print("Hash Set:")
        # print each bucket in the hash set along with its contents
        for index, bucket in enumerate(self.buckets):
            print(f"Bucket {index}: {bucket}")
hash_set = SimpleHashSet(size=10)

hash_set.add("Charlotte")
hash_set.add("Thomas")
hash_set.add("Jens")
hash_set.add("Peter")
hash_set.add("Lisa")
hash_set.add("Adele")
hash_set.add("Michaela")
hash_set.add("Bob")

hash_set.print_set()

print("\n'Peter' is in the set:",hash_set.contains('Peter'))
print("Removing 'Peter'")
hash_set.remove('Peter')
hash_set.print_set()
print("'Peter' is in the set:",hash_set.contains('Peter'))
print("'Adele' has hash code:",hash_set.hash_function('Adele'))
    
    
    