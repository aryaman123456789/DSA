# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def rangeSumBST(self, root: Optional[TreeNode], low: int, high: int) -> int:
        def dfs(node):
            if not node:
                return 0
            curr_sum = 0
            if low <= node.val <= high:
                curr_sum += node.val
            if node.val > low:
                curr_sum += dfs(node.left)
            if node.val < high:
                curr_sum += dfs(node.right)
            return curr_sum
        return dfs(root)