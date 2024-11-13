# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        from collections import deque
        res = []
        if not root:
            return res
        queue = deque([root])
        while queue:
            rightMost = None
            for i in range(len(queue)):
                node = queue.popleft()
                if node:
                    rightMost = node
                    queue.append(node.left)
                    queue.append(node.right)
            if rightMost:
                res.append(rightMost.val)
        return res