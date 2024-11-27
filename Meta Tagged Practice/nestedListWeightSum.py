'''Input: [[1,1],2,[1,1]]
Output: 10 
Explanation: Four 1's at depth 2, one 2 at depth 1.'''

class Solution:
    """
    @param nestedList: a list of NestedInteger
    @return: the sum
    """
    def depthSumInverse(self, nestedList):
        # Write your code here.
        def dfs(array, depth):
            total = 0
            for element in array:
                if isinstance(element, int):
                    total += element * depth
                elif isinstance(element, list):
                    total += dfs(element, depth + 1)
        return dfs(nestedList, 1)
