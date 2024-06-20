def partition(my_array, low, high):
    pivot = my_array[high]
    i = (low - 1)
    for j in range(low, high):
        if my_array[j] <= pivot:
            i += 1
            my_array[i], my_array[j] = my_array[j], my_array[i]
    my_array[i + 1], my_array[high] = my_array[high], my_array[i + 1]
    return (i + 1)

def quickSort(my_array, low = 0, high = None):
    if high is None:
        high = len(my_array) - 1
    if low < high:
        partition_index = partition(my_array, low, high)
        quickSort(my_array, low, partition_index - 1)
        quickSort(my_array, partition_index + 1, high)
    return my_array

my_array = [4, 6, 8, 2, 10, 5, 1, 9, 3, 7]
sorted_array = quickSort(my_array)
print(sorted_array)
