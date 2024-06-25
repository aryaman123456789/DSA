// Aryaman Gautam, agautam6, PA7
#include "Dictionary.h"
#include <cassert>
#include <iostream>

int main() {
    // Create a Dictionary
    Dictionary dict1;

    // Test size() on an empty Dictionary
    assert(dict1.size() == 0);

    // Test setValue() to insert key-value pairs
    dict1.setValue("Five", 5);
    dict1.setValue("Three", 3);
    dict1.setValue("Seven", 7);
    dict1.setValue("One", 1);

    // Test size() on a non-empty Dictionary
    assert(dict1.size() == 4);

    // Test to_string() to print the Dictionary
    std::cout << "Dictionary Contents:\n" << dict1.to_string() << std::endl;

    // Test contains() and getValue()
    int keyToFind = "three";
    assert(dict1.contains(keyToFind));
    std::cout << "Value for key " << keyToFind << ": " << dict1.getValue(keyToFind) << std::endl;

    // Test remove() and size() after removal
    dict1.remove(3);
    assert(dict1.size() == 3);

    // Test pre_string() for pre-order traversal
    std::cout << "Pre-order traversal:\n" << dict1.pre_string() << std::endl;

    // Test iterator functions: begin(), next(), hasCurrent(), currentKey(), currentVal()
    dict1.begin();
    while (dict1.hasCurrent()) {
        std::cout << "Current Key: " << dict1.currentKey() << ", Current Value: " << dict1.currentVal() << std::endl;
        dict1.next();
    }

    // Test end() to move the iterator to the last pair
    dict1.end();
    assert(!dict1.hasCurrent());

    // Test equals() with another Dictionary
    Dictionary dict2;
    dict2.setValue(5, "Five");
    dict2.setValue(7, "Seven");
    dict2.setValue(1, "One");
    dict2.setValue(3, "Three");

    assert(dict1.equals(dict2));

    std::cout << "All tests passed successfully!" << std::endl;

    return 0;
}
