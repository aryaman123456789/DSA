class TreeNode:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

def minNodeValue(node):
    current = node
    while current.left is not None:
        current = current.left
    return current

def deleteNode(node, deleteNodeData):
    if node is None:
        return None
    if node.data > deleteNodeData: # recurse on the left subtree
        node.left = deleteNode(node.left, deleteNodeData)
    elif node.data < deleteNodeData: #recurse on the right subtree
        node.right = deleteNode(node.right, deleteNodeData)
    else: # we found the node to be deleted
        if not node.left: # the node has no left child (only the right child exists)
            temp = node.right # assign the right child to a temporary variable
            node = None # delete the current node
            return temp # return the right child (maintain the tree structure)
        elif not node.right: # the node has no right child (only the left child exists)
            temp = node.left # assign the left child to a temporary variable
            node = None # delete the current node
            return temp # return the left child (maintain the tree structure)
        
        # the node has both left and right children
        node.data = minNodeValue(node.right).data # find the in-order successor's value in the right 
                                                  # subtree and replace the node's value with it
        node.right = deleteNode(node.right, node.data) # recurse of the right subtree to delete the in-order successor
    return node #return the updated node (maintain the tree structure)


def inOrderTraversal(node):
    if node is None:
        return
    inOrderTraversal(node.left)
    print(node.data, end = ' -> ')
    inOrderTraversal(node.right)
    
root = TreeNode(13)
node7 = TreeNode(7)
node15 = TreeNode(15)
node3 = TreeNode(3)
node8 = TreeNode(8)
node14 = TreeNode(14)
node19 = TreeNode(19)
node18 = TreeNode(18)

root.left = node7
root.right = node15

node7.left = node3
node7.right = node8

node15.left = node14
node15.right = node19

node19.left = node18

print("Inorder traversal before insertion:\n")
inOrderTraversal(root)
deleteNode(root, 13)
print("\nInorder traversal after deleting 10:\n")
inOrderTraversal(root)