# 314. Binary Tree Vertical Order Traversal
# Given a binary tree, return the vertical order traversal of its nodes' values. (ie, from top to bottom, column by column).

# If two nodes are in the same row and column, the order should be from left to right.

# Time Complexity: O(nlogn), since the BFS traversal itself iterates over all N nodes and sorting the dictionary keys takes logN time
# Space Complexity: O(n) as we allocated a new dictionary memory and it will eventually store all N nodes in the tree
class Node:
    def __init__(self, val = 0, left = None, right = None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def verticalOrder(self, root):
        from collections import deque, defaultdict
        if not root:
            return []
        queue = deque([(root, 0)])
        dist_to_nodes = defaultdict(list)
        while queue:
            node, distance = queue.popleft()
            dist_to_nodes[distance].append(node.val)
            if node.left:
                queue.append((node.left, distance - 1))
            if node.right:
                queue.append((node.right, distance + 1))
        return [nodes for distance, nodes in sorted(dist_to_nodes.items())]
        
        