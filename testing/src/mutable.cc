#include "mutable.h"

#include <iostream>

void TestMutable() {
    const MutableTest mutable_class;

    std::cout << mutable_class.GetValue() << "\n";
    std::cout << mutable_class.GetValue() << "\n";
    std::cout << mutable_class.GetValue() << "\n";
    std::cout << mutable_class.GetCounter() << "\n";
}