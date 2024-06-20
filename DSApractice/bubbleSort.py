my_array = [4, 6, 8, 2, 10, 5, 1, 9, 3]

n = len(my_array)
for i in range(n - 1):
    swaps = False
    for j in range(n - i - 1):
        if my_array[j] > my_array[j + 1]:
            my_array[j], my_array[j + 1] = my_array[j + 1], my_array[j]
            swaps = True
    if not swaps:
        break
print(my_array)
