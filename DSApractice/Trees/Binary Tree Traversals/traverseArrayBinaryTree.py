binary_tree_array = ['R', 'A', 'B', 'C', 'D', 'E', 'F', None, None, None, None, None, None, 'G']

def left_child_index(index):
    return 2 * index + 1

def right_child_index(index):
    return 2 * index + 2

def preOrder(index):
    if index >= len(binary_tree_array) or binary_tree_array[index] is None:
        return []
    return [binary_tree_array[index]] + preOrder(left_child_index(index)) + preOrder(right_child_index(index))

def inOrder(index):
    if index >= len(binary_tree_array) or binary_tree_array[index] is None:
        return []
    return inOrder(left_child_index(index)) + [binary_tree_array[index]] + inOrder(right_child_index(index))

def postOrder(index):
    if index >= len(binary_tree_array) or binary_tree_array[index] is None:
        return []
    return postOrder(left_child_index(index)) + postOrder(right_child_index(index)) + [binary_tree_array[index]]

print("Preorder traversal:", preOrder(0))
print("Inorder traversal:", inOrder(0))
print("Postorder traversal:", postOrder(0))