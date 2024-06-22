my_array = [4, 6, 8, 2, 10, 5, 1, 9, 3, 7]
targetValue = 4
def linearSearch(arr, target):
    for i in range(len(arr)):
        if arr[i] == target:
            return i
    return -1

index = linearSearch(my_array, targetValue)

if index == -1:
    print(f"The target value {targetValue} is not found in the array")
else:
    print(f"The target value {targetValue} is found at index {index}")