my_array = [4, 6, 8, 2, 10, 5, 1, 9, 3, 7]
def radix_sort(my_array):
    radixArray = [[], [], [], [], [], [], [], [], [], []]
    maxVal = max(my_array)
    exp = 1
    while (maxVal // exp) > 0:
        while len(my_array) > 0:
            num = my_array.pop()
            radixIndex = (num // exp) % 10
            radixArray[radixIndex].append(num)
        for bucket in radixArray:
            while len(bucket) > 0:
                val = bucket.pop()
                my_array.append(val)
        exp *= 10
    return my_array

sorted_array = radix_sort(my_array)
print(sorted_array)
