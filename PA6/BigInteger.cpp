// Aryaman Gautam, agautam6, PA6
#include "BigInteger.h"
#include "List.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <stdexcept>
using namespace std;
const long base = 1000000000;
const int power = 9;        

List scalarMultiply(long scalar, List *B, int* counter) {
    List L; // Resulting list to store the product of scalar multiplication.
    long carryOver = 0; // Carry over value during multiplication.
    long currDigit = 0; // Current digit in the multiplication process.
    // Iterate through the digits in reverse order.
    for (B->moveBack(); B->position() > 0; B->movePrev()) {
        // Calculate the product of the current digit and the scalar, add the carry over.
        currDigit = ((B->peekPrev() * scalar) + carryOver);
        carryOver = (currDigit / base); // Determine the carry over.
        currDigit %= base; // Update the current digit.
        // Insert the calculated digit into the result list.
        L.insertAfter(currDigit);
    }
    // If there is a final carry over, insert it as a new digit.
    if (carryOver > 0) {
        L.insertAfter(carryOver);
    }
    // Move to the back of the result list.
    L.moveBack();
    // Insert zeros at the end based on the counter value.
    for (int i = 0; i < *counter; i++) {
        L.insertAfter(0);
    }
    // Return the resulting list representing the scalar multiplication.
    return L;
}

void deleteLeadZero(List* L) {
    // Edge case: Iterate through the list and delete all leading zeroes
    L->moveFront();
    while ((L->length() > 0) && (!L->peekNext())) {
        L->eraseAfter();
    }
}

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
    signum = 0;
    digits = List();
}

// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x) {
    // Create BigInteger based on given signum value
    if (x == 0) {
        signum = 0;
        digits.insertAfter(0);
        return;
    }
    if (x < 0) {
        signum = -1;
        x = -x;
    } else {
        signum = 1;
    }
    while (x > 0) {
        digits.insertBefore(x % base);
        x /= base;
    }
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
    // Check if the input string is empty.
    if (!s.length()) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    int startIndex = 0;
    // Check if the string starts with a sign character.
    if ((s[0] == '+') | (s[0] == '-')) {
        signum = 1;
        if (s[0] == '-') {
            signum = -1;
        }
        startIndex = 1;
        s = s.substr(startIndex, (s.length() - 1));
    } else {
        // Default to positive sign if no sign character is present.
        signum = 1;
    }

    // Validate that the string contains only numeric characters.
    for (long unsigned int i = 0; i < s.length();) {
        if (!std::isdigit(s[i])) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
        i++;
    }
    std::string result = "";
    size_t maxBlocks = 0;
    size_t currentLength = s.length();
    // Divide the input string into chunks of power digits and convert each chunk to a number.
    while (maxBlocks < s.length() / power) {
        result = s.substr((currentLength - power), power);
        digits.insertAfter(std::stol(result, nullptr, 10));
        currentLength = (currentLength - power);
        maxBlocks++;
    }
    // If there are remaining digits, convert them to a number and insert them.
    if (currentLength > 0) {
        result = s.substr(0, currentLength);
        digits.insertAfter(std::stol(result, nullptr, 10));
    }
    // Remove leading zeros from the digits list.
    deleteLeadZero(&digits);
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    // Copy over the signum and digits parameters of N into this
    this->signum = N.signum;
    this->digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
    // Return signum of this
    return this->signum;
}

// compare()
// Returns -1, 1, or 0 according to whether this BigInteger is less than N,
// greater than N, or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    // Compare signs
    if (signum > N.signum) {
        return 1;
    } else if (signum < N.signum) {
        return -1;
    } else if ((signum == 0) && (N.signum == 0)) {
        // Both BigIntegers are zero
        return 0;
    }
    // Compare lengths of the digit lists
    const List& bigIntDigits = digits;
    const List& NDigits = N.digits;
    int bigIntLength = bigIntDigits.length();
    if (bigIntLength != NDigits.length()) {
        if (bigIntLength > NDigits.length()) {
            // Current BigInteger has more digits, so it is greater
            return signum;
        } else {
            // N has more digits, so it is greater
            return -N.signum;
        }
    }
    // Compare individual digits
    List bigIntDigitsCopy = bigIntDigits;
    List NDigitsCopy = NDigits;
    bigIntDigitsCopy.moveFront();
    NDigitsCopy.moveFront();
    for (int i = 0; i < bigIntLength; ++i) {
        if (bigIntDigitsCopy.peekNext() > NDigitsCopy.peekNext()) {
            // Current BigInteger has a larger digit at this position
            return signum;
        } else if (bigIntDigitsCopy.peekNext() < NDigitsCopy.peekNext()) {
            // N has a larger digit at this position
            return -N.signum;
        }
        bigIntDigitsCopy.moveNext();
        NDigitsCopy.moveNext();
    }
    // Both BigIntegers are equal
    return 0;
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    // Clear all digits and make sure if signum is set to 0 (default)
    digits.clear();
    signum = 0;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
    signum = -signum;
}

// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    // Create copies of the operands to avoid modifying the original BigIntegers
    BigInteger operand1 = *this;
    BigInteger operand2 = N;
    // Resulting BigInteger to store the result
    BigInteger result;
    // Handle cases where signs differ
    if ((operand1.sign() > 0) && (operand2.sign() < 0)) {
        operand2.negate();
        return operand1.sub(operand2);
    } else if ((operand1.sign() < 0) && (operand2.sign() > 0)) {
        operand1.negate();
        return operand2.sub(operand1);
    } else if ((operand1.sign() < 0) && (operand2.sign() < 0)) {
        operand1.negate();
        operand2.negate();
        result = operand1.add(operand2);
        result.negate();
        return result;
    }
    // Ensure operand1 is the smaller BigInteger
    if (operand1 > operand2) {
        return operand2.add(operand1);
    }
    // Lists to store digits of operands and result
    List op1 = operand1.digits;
    List op2 = operand2.digits;
    List res = result.digits;
    // Variables for addition process
    long carry = 0;
    long currentDigit = 0;
    // Move iterators to the end of digit lists
    op1.moveBack();
    op2.moveBack();
    // Iterate through digits of both operands
    while ((op1.position() > 0) && (op2.position() > 0)) {
        currentDigit = carry + op1.peekPrev() + op2.peekPrev();
        carry = currentDigit / base;
        currentDigit %= base;
        res.insertAfter(currentDigit);
        op1.movePrev();
        op2.movePrev();
    }
    // Handle any remaining digits in operand2
    while (op2.position() > 0) {
        currentDigit = carry + op2.peekPrev();
        carry = currentDigit / base;
        currentDigit %= base;
        res.insertAfter(currentDigit);
        op2.movePrev();
    }
    // If there is a final carry, add it as a new digit
    if (carry > 0) {
        res.insertAfter(carry);
    }
    // Set the sign of the result to positive
    result.signum = 1;
    result.digits = res;
    // Return the resulting BigInteger
    return result;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    // Create copies of the operands to avoid modifying the original BigIntegers
    BigInteger operand1 = *this;
    BigInteger operand2 = N;
    // Resulting BigInteger to store the difference
    BigInteger result;
    // Lists to store digits of operands and result
    List op1 = operand1.digits;
    List op2 = operand2.digits;
    List res = result.digits;
    // Check for special cases
    if (operand2 == operand1) {
        return result;  // Return zero if both operands are equal
    }
    if (operand2.sign() && !operand1.sign()) {
        operand2.negate();
        return operand2;  // Return negation of operand2 if operand1 is positive and operand2 is negative
    }
    if (!operand2.sign() && operand1.sign()) {
        return operand1;  // Return operand1 if operand1 is negative and operand2 is positive
    }
    if ((operand2.sign() < 0) && (operand1.sign() > 0)) {
        operand1.negate();
        result = operand2.add(operand1);
        result.negate();
        return result;  // Return negation of (operand2 + (-operand1)) if signs differ
    }
    if ((operand2.sign() > 0) && (operand1.sign() < 0)) {
        operand2.negate();
        result = operand2.add(operand1);
        return result;  // Return (operand2 + (-operand1)) if signs differ
    }
    if ((operand2.sign() < 0) && (operand1.sign() < 0)) {
        operand2.negate();
        operand1.negate();
        result = operand1.sub(operand2);
        result.negate();
        return result;  // Return negation of (operand1 - operand2) if both operands are negative
    }
    if (operand2 < operand1) {
        result = operand2.sub(operand1);
        result.negate();
        return result;  // Return negation of (operand2 - operand1) if operand2 is smaller
    }
    // Perform digit-by-digit subtraction
    op2.moveBack();
    op1.moveBack();
    long carry = 0;
    long currentDigit = 0;
    int op1position = op1.position();
    while (!(op1position <= 0)) {
        if ((op2.peekPrev() - carry) < op1.peekPrev()) {
            currentDigit = op2.peekPrev() + base - op1.peekPrev() - carry;
            carry = 1;
        } else {
            currentDigit = op2.peekPrev() - carry - op1.peekPrev();
            if (!(op2.peekPrev() <= 0)) {
                carry = 0;
            }
        }
        res.insertAfter(currentDigit);
        op2.movePrev();
        op1.movePrev();
        op1position--;
    }
    // Handle remaining digits of operand2
    while (op2.position() > 0) {
        if (op2.peekPrev() - carry < 0) {
            currentDigit = op2.peekPrev() + base - 0 - carry;
            carry = 1;
        } else {
            currentDigit = op2.peekPrev() - carry - 0;
            if (!(op2.peekPrev() <= 0)) {
                carry = 0;
            }
        }
        res.insertAfter(currentDigit);
        op2.movePrev();
    }
    // Set the result digits and remove leading zeros
    result.digits = res;
    deleteLeadZero(&(result.digits));
    // Set the sign of the result to negative
    result.signum = -1;
    // Return the resulting BigInteger
    return result;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
    // Create copies of the operands to avoid modifying the original BigIntegers
    BigInteger operand1 = N;
    BigInteger operand2 = *this;
    // Resulting BigInteger to store the product
    BigInteger result;
    // Lists to store digits of operands and result
    List op1 = operand1.digits;
    List op2 = operand2.digits;
    // Move to the end of the digit lists
    op1.moveBack();
    op2.moveBack();
    // Position of op1, used in the loop
    int op1position = op1.position();
    // Counter to keep track of the position of the current digit in the result
    int counter = 0;
    // Iterate through each digit of op1
    for (int i = op1position; i > 0; i--) {
        // Multiply the current digit of op1 with op2 and get the result as a list
        List product = scalarMultiply(op1.peekPrev(), &op2, &counter);
        // Create a temporary BigInteger from the list
        BigInteger tempResult;
        tempResult.signum = 1;
        tempResult.digits = product;
        // Add the temporary result to the overall result
        result = result.add(tempResult);
        // Move to the next digit of op1
        op1.movePrev();
        // Increment the counter to position the next digit in the result
        counter++;
    }
    // Determine the sign of the result based on the signs of the operands
    result.signum = operand1.signum * operand2.signum;
    // Return the resulting BigInteger
    return result;
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
    // Resulting string representation of the BigInteger
    std::string result = "";
    // Check if the BigInteger is zero
    if (this->signum == 0) {
        return "0";
    } else if (signum == -1) {
        // Add a negative sign if the BigInteger is negative
        result += "-";
    }
    // Move to the front of the digits list
    digits.moveFront();
    // Remove leading zeros from the digits list
    while (digits.front() == 0 && digits.length() > 1) {
        digits.eraseAfter();
    }
    // Iterate through each digit in the digits list
    for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
        // Convert the current digit to a string segment
        std::string seg1 = std::to_string(digits.peekNext());
        // Add trailing zeros to the segment to make it a power of 10
        std::string seg2 = "";
        while (((int)(seg2.length() + seg1.length()) < power) && (digits.position() != 0)) {
            seg2 += '0';
        }
        // Concatenate the segments to the result
        result += (seg2 + seg1);
    }
    // Return the resulting string representation
    return result;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    // Use to_string() for stream
    return (stream << N.to_string());
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
    // Use compare()
    return (A.compare(B) == 0);
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
    return (A.compare(B) < 0);
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ) {
    return (A.compare(B) <= 0);
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) {
    return (A.compare(B) > 0);
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    return (A.compare(B) >= 0);
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return (A.add(B));
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return (A.sub(B));
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return (A.mult(B));
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    A = A.mult(B);
    return A;
}