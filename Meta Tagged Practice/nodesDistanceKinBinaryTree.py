# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def distanceK(self, root: TreeNode, target: TreeNode, k: int) -> List[int]:
        res = []
        node_to_parent = {}
        visited = set()
        def map_parent(node, parent):
            if node:
                node_to_parent[node] = parent
                map_parent(node.left, node)
                map_parent(node.right, node)
        map_parent(root, None)
        def dfs(node, remaining_dist):
            if not node or node.val in visited:
                return
            visited.add(node.val)
            if remaining_dist == 0:
                res.append(node.val)
            else:
                dfs(node.left, remaining_dist - 1)
                dfs(node.right, remaining_dist - 1)
                dfs(node_to_parent[node], remaining_dist - 1)
        dfs(target, k)
        return res