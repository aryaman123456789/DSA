my_array = [4, 6, 8, 2, 10, 5, 1, -9, 3, 7]

def merge_sort(my_array):
    if len(my_array) <= 1:
        return my_array
    mid = len(my_array) // 2
    left = my_array[:mid]
    right = my_array[mid:]
    sortLeft = merge_sort(left)
    sortRight = merge_sort(right)
    return merge(sortLeft, sortRight)

def merge(left, right):
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result

sorted_array = merge_sort(my_array)
print(sorted_array)
