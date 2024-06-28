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
def minValueNode(node):
    current = node
    while current.left is not None:
        current = current.left
    return current

def delete(node, data):
    if not node:
        return node

    if data < node.data:
        node.left = delete(node.left, data)
    elif data > node.data:
        node.right = delete(node.right, data)
    else:
        if node.left is None:
            temp = node.right
            node = None
            return temp
        elif node.right is None:
            temp = node.left
            node = None
            return temp

        temp = minValueNode(node.right)
        node.data = temp.data
        node.right = delete(node.right, temp.data)

    if node is None:
        return node

    # Update the balance factor and balance the tree
    node.height = 1 + max(getHeight(node.left), getHeight(node.right))
    balance = getBalanceFactor(node)

    # Balancing the tree
    # Left Left
    if balance > 1 and getBalanceFactor(node.left) >= 0:
        return rightRotate(node)

    # Left Right
    if balance > 1 and getBalanceFactor(node.left) < 0:
        node.left = leftRotate(node.left)
        return rightRotate(node)

    # Right Right
    if balance < -1 and getBalanceFactor(node.right) <= 0:
        return leftRotate(node)

    # Right Left
    if balance < -1 and getBalanceFactor(node.right) > 0:
        node.right = rightRotate(node.right)
        return leftRotate(node)

    return node