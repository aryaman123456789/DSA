# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

#Time: O(N) where each node is processed exactly one
#Space: O(N) which is the ize of the queue, and in worse case, with a perfectly balanced tree, we could have up to N/2 nodes
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