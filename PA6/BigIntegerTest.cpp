// Aryaman Gautam, agautam6, PA6
#include "BigInteger.h"
#include <iostream>
#include <cassert>

int main() {
    // Test constructor from base, sign(), and to_string()
    BigInteger num1;
    assert(num1.sign() == 0);
    assert(num1.to_string() == "0");
    // Test constructor from long
    BigInteger num2(12345);
    assert(num2.sign() == 1);
    assert(num2.to_string() == "12345");
    // Test constructor from string
    BigInteger num3("-98765");
    assert(num3.sign() == -1);
    assert(num3.to_string() == "-98765");
    // Test copy constructor
    BigInteger num4(num3);
    assert(num4.sign() == -1);
    assert(num4.to_string() == "-98765");
    // Test negate()
    num4.negate();
    assert(num4.sign() == 1);
    assert(num4.to_string() == "98765");
    // Test makeZero()
    num4.makeZero();
    assert(num4.sign() == 0);
    assert(num4.to_string() == "0");
    // Test add(), sub(), and mult()
    BigInteger num5("123");
    BigInteger num6("-45");
    BigInteger sum = num5.add(num6);
    assert(sum.to_string() == "78");
    BigInteger diff = num5.sub(num6);
    assert(diff.to_string() == "168");
    BigInteger product = num5.mult(num6);
    assert(product.to_string() == "-5535");
    // Test comparison operators
    assert(num5 == num5);
    assert(num5 != num6);
    assert(num5 < num6);
    assert(num5 <= num6);
    assert(num6 > num5);
    assert(num6 >= num5);
    // Test overloaded operators
    assert(num5 + num6 == sum);
    assert(num5 - num6 == diff);
    assert(num5 * num6 == product);
    // Test +=, -=, and *=
    num5 += num6;
    assert(num5 == sum);
    num5 -= num6;
    assert(num5 == num5);
    num5 *= num6;
    assert(num5 == product);
    // Test ostream operator
    std::cout << "Testing ostream() with num5: " << num5 << std::endl;
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
