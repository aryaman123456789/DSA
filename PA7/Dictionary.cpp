// Aryaman Gautam, agautam6, PA7
#include "Dictionary.h"
#include <stdexcept>

// Class Constructors & Destructors ----------------------------------------

// Node constructor.
Dictionary::Node::Node(keyType k, valType v)
    : key(k), val(v), parent(nullptr), left(nullptr), right(nullptr) {}

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary()
    : nil(new Node("", 0)), root(nil), current(nil), num_pairs(0) {}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D)
    : nil(new Node("", 0)), root(nil), current(nil), num_pairs(0) {
    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
    postOrderDelete(root);
    delete nil;
}

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        // Traverse the left subtree
        inOrderString(s, R->left);
        // Append current node's key-value pair to the string
        s += R->key + " : " + std::to_string(R->val) + "\n";
        // Traverse the right subtree
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        // Append the current node's key to the string and add newline separator
        s += R->key + "\n";
        // Traverse the left subtree
        preOrderString(s, R->left);
        // Traverse the right subtree
        preOrderString(s, R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
    // Check if the keys of the source and destination nodes match
    if (R->key == N->key) {
        return; // Recursion terminates when the keys match
    }
    // Set the value of the current destination node to the value of the source node
    setValue(N->key, R->val);
    // Recursively copy the left subtree
    preOrderCopy(R->left, N);
    // Recursively copy the right subtree
    preOrderCopy(R->right, N);
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R) {
    // Check if the current node is not nil
    if (R != nil) {
        // Recursively delete the left subtree
        postOrderDelete(R->left);
        // Recursively delete the right subtree
        postOrderDelete(R->right);
        // Delete the current node after deleting its subtrees
        delete R;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    // Base case: If the current node is null (nil) or the key matches, return the current node
    if (R == nil || R->key == k) {
        return R;
    }
    // If the key is less than the current node's key, search in the left subtree
    // Otherwise, if the key is greater than the current node's key, search in the right subtree
    if (k < R->key) {
        return search(R->left, k);
    } else {
        return search(R->right, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
    // Traverse the left subtree until the leftmost node is found
    while ((R != nil) && (R->left != nil)) {
        R = R->left;
    }
    // Return the leftmost node or nil if the subtree is empty
    return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
    // Traverse the right subtree until the rightmost node is found
    while ((R != nil) && (R->right != nil)) {
        R = R->right;
    }
    // Return the rightmost node or nil if the subtree is empty
    return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N) {
    // If N is nil, return nil
    if (N == nil) {
        return nil;
    }
    // If N has a right subtree, return the leftmost node in that subtree
    if (N->right != nil) {
        return findMin(N->right);
    }

    // If N does not have a right subtree, find the ancestor that is the parent of a left child
    Node* ancestorWithLeftChild = N->parent;
    while ((ancestorWithLeftChild != nil) && (ancestorWithLeftChild->right == N)) {
        // Traverse up the tree until finding the ancestor whose left child is N
        N = ancestorWithLeftChild;
        ancestorWithLeftChild = ancestorWithLeftChild->parent;
    }
    // Return the ancestor found (or nil if N was the rightmost node)
    return ancestorWithLeftChild;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
    // If N is nil, return nil
    if (N == nil) {
        return nil;
    }
    // If N has a left subtree, return the rightmost node in that subtree
    if (N->left != nil) {
        return findMax(N->left);
    }
    // If N does not have a left subtree, find the ancestor that is the parent of a right child
    Node* ancestorWithRightChild = N->parent;
    while ((ancestorWithRightChild != nil) && (ancestorWithRightChild->left == N)) {
        // Traverse up the tree until finding the ancestor whose right child is N
        N = ancestorWithRightChild;
        ancestorWithRightChild = ancestorWithRightChild->parent;
    }
    // Return the ancestor found (or nil if N was the leftmost node)
    return ancestorWithRightChild;
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
    // Dictionary size corresponds to the number of (key,value) pairs
    return num_pairs; 
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
    // Search tree rooted at root and find k, compare with nil (false) or otherwise (true)
    return search(root, k) != nil;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
    // Search for the key in the dictionary
    Node* key = search(root, k);
    // If the key is not found, throw an exception
    if (key == nil) {
        throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
    }
    // Return a reference to the value associated with the specified key
    return key->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
    // Return bool corresponding to whether or not current is nil
    return (current != nil);
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
    // Check preCondition that current is defined, if not, throw error
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
    // Check preCondition that current is defined, if not, throw error
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
    // Delete all nodes in a post-order traversal
    postOrderDelete(root);
    // Reset root, current, and num_pairs to initial state
    root = nil;
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
    // Search for an existing node with the specified key
    Node* existingNode = search(root, k);
    // If a node with the key already exists, update its value
    if (existingNode != nil) {
        existingNode->val = v;
    } else {
        // Create a new node with the specified key and value
        Node* newNode = new Node(k, v);
        newNode->left = nil;
        newNode->right = nil;
        // Initialize parent and current node variables for tree traversal
        Node* parentNode = nil;
        Node* currentNode = root;
        // Traverse the tree to find the correct position for the new node
        while (currentNode != nil) {
            parentNode = currentNode;
            if (newNode->key < currentNode->key) {
                currentNode = currentNode->left;
            } else {
                currentNode = currentNode->right;
            }
        }
        // Set the parent of the new node and update the tree structure
        newNode->parent = parentNode;
        if (parentNode == nil) {
            root = newNode;
        } else if (newNode->key < parentNode->key) {
            parentNode->left = newNode;
        } else {
            parentNode->right = newNode;
        }
        // Increment the number of key-value pairs in the dictionary
        num_pairs++;
    }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
    // Find the node with the specified key
    Node* targetNode = search(root, k);
    // Check if the node with the specified key exists
    if (targetNode == nil) {
        throw std::invalid_argument("Dictionary: remove(): key \"" + k + "\" does not exist");
    }
    // If the node has both left and right children, find its successor
    if ((targetNode->left != nil) && (targetNode->right != nil)) {
        // Find the successor node in the right subtree
        Node* successorNode = findMin(targetNode->right);
        // Replace the target node's key and value with the successor's key and value
        targetNode->key = successorNode->key;
        targetNode->val = successorNode->val;
        // Update targetNode to point to the successorNode for further processing
        targetNode = successorNode;
    }
    // Determine the child node (left or right) of the target node
    Node* childNode;
    if (targetNode->left != nil) {
        childNode = targetNode->left;
    } else {
        childNode = targetNode->right;
    }
    // Update the parent's reference to the child node
    if (targetNode->parent != nil) {
        if (targetNode == targetNode->parent->left) {
            targetNode->parent->left = childNode;
        } else {
            targetNode->parent->right = childNode;
        }
    } else {
        // If the target node is the root, update the root
        root = childNode;
    }
    // Update the child node's parent reference
    if (childNode != nil) {
        childNode->parent = targetNode->parent;
    }
    // If 'current' was pointing to the removed node, set it to nil
    if (targetNode == current) {
        current = nil;
    }
    // Delete the target node
    delete targetNode;
    // Decrement the number of key-value pairs in the dictionary
    num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() {
    // place current at the first pair using findMin()
    current = findMin(root);
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() {
    // place current at the last pair using findMax()
    current = findMax(root);
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
    // Check precondition, otherwise, use findNext() on current
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: next(): current undefined");
    } else {
        current = findNext(current);
    }
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
    // Check precondition, otherwise, use findPrev() on current
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: prev(): current undefined");
    } else {
        current = findPrev(current);
    }
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
    // Initialize an empty string to store the result
    std::string result;
    // Perform an in-order tree walk to append key-value pairs to the result string
    inOrderString(result, root);
    // Return the resulting string representation of the Dictionary
    return result;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
    // Initialize an empty string to store the result
    std::string result;
    // Perform a pre-order tree walk to append key-value pairs to the result string
    preOrderString(result, root);
    // Return the resulting string representation of the Dictionary
    return result;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
    return (D.to_string() == to_string());
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    return (stream << D.to_string());
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
    // Check for self-assignment
    if (this != &D) {
        // Clear the current contents of the Dictionary
        clear();
        // Perform a deep copy of the provided Dictionary using pre-order traversal
        preOrderCopy(D.root, nil);
    }
    // Return a reference to the modified Dictionary
    return *this;
}