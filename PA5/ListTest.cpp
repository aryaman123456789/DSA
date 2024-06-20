#include "List.h"

void TestForConstructAndDeconstruct() {
    List list1;
    std::cout << "Default constructor test: " << list1.to_string() << std::endl;

    list1.insertAfter(1);
    list1.insertAfter(2);
    list1.insertAfter(3);
    List list2(list1);

    std::cout << "Copy constructor test: " << list2.to_string() << std::endl;

    std::cout << "Destructor test: Objects freed implicitly in C++." << std::endl;
}

void TestAccess() {
    List testAccess;
    testAccess.insertAfter(1);
    testAccess.insertAfter(2);
    testAccess.insertAfter(3);

    std::cout << "Test length(): " << testAccess.length() << " (Expected: 3)" << std::endl;

    std::cout << "Test front(): " << testAccess.front() << " (Expected: 1)" << std::endl;

    std::cout << "Test back(): " << testAccess.back() << " (Expected: 3)" << std::endl;

    std::cout << "Test position(): " << testAccess.position() << " (Expected: 0)" << std::endl;

    std::cout << "Test peekNext(): " << testAccess.peekNext() << " (Expected: 2)" << std::endl;

    std::cout << "Test peekPrev(): ";
    testAccess.moveBack();
    std::cout << testAccess.peekPrev() << " (Expected: 2)" << std::endl;
}

void TestManipulation() {
    List testManipulation;
    testManipulation.insertAfter(1);
    testManipulation.insertAfter(2);
    testManipulation.insertAfter(3);

    std::cout << "Initial List: " << testManipulation.to_string() << std::endl;

    std::cout << "Test moveNext(): ";
    testManipulation.moveNext();
    std::cout << testManipulation.position() << " (Expected: 1)" << std::endl;

    std::cout << "Test movePrev(): ";
    testManipulation.movePrev();
    std::cout << testManipulation.position() << " (Expected: 0)" << std::endl;

    std::cout << "Test insertAfter(): ";
    testManipulation.insertAfter(4);
    std::cout << testManipulation.to_string() << " (Expected: (1, 4, 2, 3))" << std::endl;

    std::cout << "Insert after and current state: ";
    testManipulation.insertBefore(0);
    std::cout << testManipulation.to_string() << " (Expected: (0, 1, 4, 2, 3))" << std::endl;

    std::cout << "Test setAfter(): ";
    testManipulation.setAfter(9);
    std::cout << testManipulation.to_string() << " (Expected: (0, 9, 4, 2, 3))" << std::endl;

    std::cout << "Test setBefore(): ";
    testManipulation.moveNext();
    testManipulation.setBefore(8);
    std::cout << testManipulation.to_string() << " (Expected: (8, 9, 4, 2, 3))" << std::endl;

    std::cout << "Test eraseAfter(): ";
    testManipulation.eraseAfter();
    std::cout << testManipulation.to_string() << " (Expected: (8, 9, 2, 3))" << std::endl;

    std::cout << "Test eraseBefore(): ";
    testManipulation.eraseBefore();
    std::cout << testManipulation.to_string() << " (Expected: (9, 2, 3))" << std::endl;
}

void TestFind() {
    List find;
    find.insertAfter(1);
    find.insertAfter(2);
    find.insertAfter(3);
    find.insertAfter(2);

    std::cout << "Test findNext(): ";
    int resultNext = find.findNext(2);
    std::cout << "Result: " << resultNext << " (Expected: 2)" << std::endl;

    std::cout << "Test findNext() with error: ";
    int resultNextError = find.findNext(69);
    std::cout << "Result: " << resultNextError << " (Expected: -1)" << std::endl;

    std::cout << "Test findPrev(): ";
    int resultPrev = find.findPrev(2);
    std::cout << "Result: " << resultPrev << " (Expected: 1)" << std::endl;

    std::cout << "Test findPrev() with error: ";
    int resultPrevError = find.findPrev(69);
    std::cout << "Result: " << resultPrevError << " (Expected: -1)" << std::endl;
}

void TestCleaup() {
    List testList;
    testList.insertAfter(1);
    testList.insertAfter(2);
    testList.insertAfter(3);
    testList.insertAfter(2);
    testList.insertAfter(1);
    std::cout << "Initial List: " << testList.to_string() << std::endl;

    std::cout << "Test cleanup(): ";
    testList.cleanup();
    std::cout << "Result: " << testList.to_string() << " (Expected: (1, 2, 3))" << std::endl;
}

void TestConcat() {
    List list1;
    list1.insertAfter(1);
    list1.insertAfter(2);
    List list2;
    list2.insertAfter(3);
    list2.insertAfter(4);
    std::cout << "List 1: " << list1.to_string() << std::endl;
    std::cout << "List 2: " << list2.to_string() << std::endl;

    std::cout << "Test concat(): ";
    List concatenatedList = list1.concat(list2);
    std::cout << "Result: " << concatenatedList.to_string() << " (Expected: (1, 2, 3, 4))" << std::endl;
}

void TestEquals() {
    List list1;
    list1.insertAfter(1);
    list1.insertAfter(2);
    list1.insertAfter(2);
    List list2;
    list2.insertAfter(1);
    list2.insertAfter(2);
    list2.insertAfter(2);
    std::cout << "List 1: " << list1.to_string() << std::endl;
    std::cout << "List 2: " << list2.to_string() << std::endl;

    std::cout << "Test equals(): ";
    bool TrueResult = list1.equals(list2);
    std::cout << "Result: " << std::boolalpha << TrueResult << " (Expected: true)" << std::endl;

    list1.cleanup();
    std::cout << "Test NOT equals(): ";
    bool FalseResult = list1.equals(list2);
    std::cout << "Result: " << std::boolalpha << FalseResult << " (Expected: false)" << std::endl;
}

void testOutputOperator() {
    List testOut;
    testOut.insertAfter(1);
    testOut.insertAfter(2);
    testOut.insertAfter(3);

    std::cout << "Test operator<<(): " << testOut << " (Expected: (1, 2, 3))" << std::endl;
}

void testEqualityOperator() {
    List list1;
    list1.insertAfter(1);
    list1.insertAfter(2);
    list1.insertAfter(3);
    List list2;
    list2.insertAfter(1);
    list2.insertAfter(2);
    list2.insertAfter(3);

    std::cout << "Test operator==(): ";
    bool isEqual = (list1 == list2);
    std::cout << "Result: " << std::boolalpha << isEqual << " (Expected: true)" << std::endl;
}

void testAssignmentOperator() {
    List list1;
    list1.insertAfter(1);
    list1.insertAfter(2);
    list1.insertAfter(3);
    List list2;
    list2.insertAfter(9);
    list2.insertAfter(8);
    list2.insertAfter(7);

    std::cout << "List 1: " << list1 << std::endl;
    std::cout << "List 2: " << list2 << std::endl;
    
    list2 = list1;
    std::cout << "Overwrite List2 with List1 - Test operator=(): " << list2 << " (Expected: (1, 2, 3))" << std::endl;
}
