my_array = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
target = 7
def binarySearch(arr, target):
    low = 0
    high = len(arr) - 1
    while low <= high:
        middle = (low + high) // 2
        if arr[middle] == target:
            return middle
        elif arr[middle] < target:
            low = middle + 1
        else:
            high = middle - 1
    return -1

binaryIndex = binarySearch(my_array, target)

if binaryIndex == -1:
    print(f"The target value {target} is not found in the array")
else:
    print(f"The target value {target} is found at index {binaryIndex}")