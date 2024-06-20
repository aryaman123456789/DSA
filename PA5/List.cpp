#include "List.h" 
#include <stdexcept>
using namespace std;
// List class
List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}
// Create new list
List::List() {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
}
// Copy constructor
List::List(const List& L) {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    Node *newL = L.frontDummy->next;
    while (newL != L.backDummy) {
        this->insertAfter(newL->data);
        moveNext();
        newL = newL->next;
    }
    moveFront();
}
// Destructor
List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}
// length()
// Returns the length of this List.
int List::length() const {
    return num_elements;
}
// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
    if (num_elements <= 0) {
        throw out_of_range("Error: front()");
    }
    return frontDummy->next->data;
}
// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    if (num_elements <= 0) {
        throw out_of_range("Error: back()");
    }
    return backDummy->prev->data; 
}
// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    return pos_cursor;
}
// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
    if (pos_cursor >= num_elements) {
        throw out_of_range("Error: peekNext()");
    }
    return afterCursor->data;
}
// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    if (pos_cursor <= 0) {
        throw out_of_range("Error: peekPrev()");
    }
    return beforeCursor->data;
}
// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    moveFront();
    while (length() > 0) {
        eraseAfter();
    }
}
// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = num_elements;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {
    if (position() > length()) {
        throw out_of_range("Error: moveNext()");
    }
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {
    if (position() <= 0) {
        throw out_of_range("Error: movePrev()");
    }
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
    if (pos_cursor < 0 || afterCursor == nullptr || beforeCursor == nullptr) {
        throw out_of_range("Error: insertAfter()");
    }
    Node *insertA = new Node(x);
    insertA->prev = beforeCursor;
    beforeCursor->next = insertA;
    insertA->next = afterCursor;
    afterCursor->prev = insertA;
    afterCursor = insertA;
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
    if (pos_cursor < 0 || afterCursor == nullptr || beforeCursor == nullptr) {
        throw out_of_range("Error: insertBefore()");
    }
    Node *insertB = new Node(x);
    insertB->prev = beforeCursor;
    beforeCursor->next = insertB;
    insertB->next = afterCursor;
    afterCursor->prev = insertB;
    beforeCursor = insertB;
    pos_cursor++;
    num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
    if (position() >= length()) {
        throw std::out_of_range("Error: setAfter()");
    }
    afterCursor->next->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
    if (position() <= 0) {
        throw std::out_of_range("Error: setBefore()");
    }
    beforeCursor->prev->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
    if (position() >= length()) {
        throw std::out_of_range("Error: eraseAfter()");
    }
    Node *eraseA = afterCursor;
    beforeCursor->next = afterCursor->next;
    eraseA->next->prev = beforeCursor;
    afterCursor = eraseA->next;
    delete eraseA;
    num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
    if (position() <= 0) {
        throw std::out_of_range("Error: eraseBefore()");
    }
    Node* eraseB = beforeCursor;
    beforeCursor = eraseB->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    delete eraseB;
    num_elements--;
    pos_cursor--;
}

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {
    Node* curr = afterCursor;
    int cursor = pos_cursor;
    while (curr != backDummy) {
        if (curr->data == x) {
            beforeCursor = curr;
            afterCursor = curr->next;
            pos_cursor = cursor+1;
            return pos_cursor;
        }
        curr = curr->next;
        cursor++;
    }
    moveBack(); 
    return -1;
}
// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {
    Node* curr = afterCursor->prev;
    int cursor = pos_cursor-1;
    while (curr != frontDummy) {
        if (curr->data == x) {
            beforeCursor = curr->prev;
            afterCursor = curr;
            pos_cursor = cursor;
            return cursor;
        }
        curr = curr->prev;
        cursor--;
    }
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
    int point = 0;
    Node *cursor = frontDummy->next;
    while (cursor != backDummy) {
        Node *curr = cursor;
        Node *move = cursor->next;
        int check = point+1;
        while (move != backDummy) {
            if (cursor->data == move->data) {
                curr->next = move->next;
                move->next->prev = curr;
                delete move;
                move = curr->next;
                if (check <= pos_cursor) {
                    pos_cursor--;
                }
                num_elements--;
            } else {
                curr = move;
                move = curr->next;
            }
            check++;
        }
        point++;
        cursor = cursor->next;
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
    List concatList;
    Node* currT = this->frontDummy->next;
    while (currT != this->backDummy) {
        concatList.insertBefore(currT->data);
        currT = currT->next;
    }
    Node* currL = L.frontDummy->next;
    while (currL != L.backDummy) {
        concatList.insertBefore(currL->data); 
        currL = currL->next;
    }
    concatList.moveFront();
    return concatList;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    std::string str = "(";
    Node* curr = frontDummy->next;
    while (curr != backDummy) {
        str += std::to_string(curr->data);
        if (curr->next != backDummy) {
            str += ", ";
        }
        curr = curr->next;
    }
    str += ")";
    return str;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
    if (num_elements != R.num_elements) {
        return false;
    } else {
        Node* curr = frontDummy->next;
        Node* Rcurr = R.frontDummy->next;
        while (curr != backDummy) {
            if (curr->data != Rcurr->data) {
                return false;
            }
            curr = curr->next;
            Rcurr = Rcurr->next;
        }
    }
    return true;  
}
   
// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
    return stream << L.to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
    return A.equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
    if (this != &L) {
        List copyL(L);
        swap(frontDummy, copyL.frontDummy);
        swap(backDummy, copyL.backDummy);
        swap(beforeCursor, copyL.beforeCursor);
        swap(afterCursor, copyL.afterCursor);
        swap(pos_cursor, copyL.pos_cursor);
        swap(num_elements, copyL.num_elements);
    }
    return *this;
}
