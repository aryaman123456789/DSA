my_array = [4, 6, 8, 2, 10, 5, 1, 9, 3, 7]

n = len(my_array)
for i in range(1, n):
    for j in range(0, i):
        if my_array[i] < my_array[j]:
            my_array[i], my_array[j] = my_array[j], my_array[i]
print(my_array)