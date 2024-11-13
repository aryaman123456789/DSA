def getMinimumTime(processSize, capacity): 
    def canExecuteInTime(processSize, capacity, t): 
        # Sort both processSize and capacity for easier assignment 
        processSize.sort(reverse=True)  
        # Sort tasks from largest to smallest
        capacity.sort(reverse=True)  
        # Sort processors from largest to smallest capacity 
        i = 0  
        # Pointer for processSize (tasks) 
        n = len(processSize) 
        # Each processor tries to handle tasks up to its capacity in t seconds 
        for cap in capacity: 
            available_time = t // 2  # In t seconds, a processor can handle t // 2 tasks 
            while i < n and processSize[i] <= cap and available_time > 0: 
                available_time -= 1  # This processor processes a task 
                i += 1  # Move to the next task 
            if i >= n: 
                return True  # All processes are handled within t seconds 
        return i >= n  
        # Check if all processes were executed 
        # Check if any process is larger than the max processor capacity 
    if max(processSize) > max(capacity): 
        return -1 # Binary search for the minimum time 
    left, right = 1, 2 * len(processSize)  # min time is 1 second, max time is 2n seconds (considering pauses) 
    while left < right: 
        mid = (left + right) // 2 
        if canExecuteInTime(processSize, capacity, mid): 
            right = mid  # Try for a smaller time 
        else: 
            left = mid + 1  # Increase the time 
    return left 
processSize = [1, 2, 3, 4, 6] 
capacity = [4, 7, 4]
print(getMinimumTime(processSize, capacity))