class TreeNode:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        self.height = 1

def getHeight(node):
    if not node:
        return 0
    return node.height

def getBalanceFactor(node):
    if not node:
        return 0
    return getHeight(node.left) - getHeight(node.right)

def rightRotate(node):
    print("Right rotate on node ", node.data)
    left_child = node.left
    right_of_left_child = left_child.right
    left_child.right = node # set the right child of the left child as the parent of the node
    node.left = right_of_left_child # set the left child of the node as the right child of the left child
    node.height = 1 + max(getHeight(node.left), getHeight(node.right)) # update the height of the node
    left_child.height = 1 + max(getHeight(left_child.left), getHeight(left_child.right)) # update the height of the left child
    return left_child # return the new root of the right subtree

def leftRotate(node):
    print("Left rotate on node ", node.data)
    right_child = node.right
    left_of_right_child = right_child.left
    right_child.left = node
    node.right = left_of_right_child
    node.height = 1 + max(getHeight(node.left), getHeight(node.right))
    right_child.height = 1 + max(getHeight(right_child.left), getHeight(right_child.right)) 
    return right_child # return the new root of the left subtree

def insertNode(node, data):
    if not node:
        return TreeNode(data)
    if data < node.data:
        node.left = insertNode(node.left, data)
    elif data > node.data:
        node.right = insertNode(node.right, data)

    node.height = 1 + max(getHeight(node.left), getHeight(node.right))
    balance = getBalanceFactor(node)

    # Left Left Case
    if balance > 1 and data < node.left.data: # if left subtree is unbalanced and data is less than left child's data
        return rightRotate(node)
    
    # Right Right Case
    if balance < -1 and data > node.right.data: # if right subtree is unbalanced and data is greater than right child's data
        return leftRotate(node)
    
    # Left Right Case
    if balance > 1 and data > node.left.data: # if left subtree is unbalanced and data is greater than left child's data
        node.left = leftRotate(node.left)
        return rightRotate(node)
    
    # Right Left Case
    if balance < -1 and data < node.right.data: # if right subtree is unbalanced and data is less than right child's data
        node.right = rightRotate(node.right)
        return leftRotate(node)
    
    return node # return the unchanged node


def inOrderTraversal(node):
    if node is None:
        return
    inOrderTraversal(node.left)
    print(node.data, end=", ")
    inOrderTraversal(node.right)

# Create a binary tree from the given array
root = None
letters = ['C', 'B', 'E', 'A', 'D', 'H', 'G', 'F']
for letter in letters:
    root = insertNode(root, letter)

inOrderTraversal(root)

