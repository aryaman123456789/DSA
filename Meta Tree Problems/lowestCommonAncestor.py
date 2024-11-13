class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.parent = None
class Solution:
    def lowestCommonAncestor(self, p, q):
        visited = set()
        node = p
        while node:
            visited.add(node)
            node = node.parent
        temp = q
        while temp not in visited:
            temp = temp.parent
        return temp