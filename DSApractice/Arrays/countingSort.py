def countingSort(my_array):
    max_val = max(my_array)
    countArray = [0] * (max_val + 1)
    while len(my_array) > 0:
        num = my_array.pop(0)
        countArray[num] += 1
    for i in range(len(countArray)):
        while countArray[i] > 0:
            my_array.append(i)
            countArray[i] -= 1
    return my_array

my_array = [4, 6, 8, 2, 10, 5, 1, 9, 3, 7]
sorted_array = countingSort(my_array)
print(sorted_array)
