class Node:
    def __init__(self, val = 0, left = None, right = None):
        self.val = val
        self.left = left
        self.right = right

from collections import deque
class Solution:
    def topNodes(self, root):
        if not root:
            return []
        queue = deque([(root, 0)])
        dist_to_node = {}
        while queue:
            node, distance = queue.popleft()
            if distance not in dist_to_node:
                dist_to_node[distance] = node.val
            if node.left:
                queue.append((node.left, distance - 1))
            if node.right:
                queue.append((node.right, distance + 1))
        return [dist_to_node[distance] for distance in sorted(dist_to_node.keys())]