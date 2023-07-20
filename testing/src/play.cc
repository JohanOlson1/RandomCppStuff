#include "play.h"

#include <iostream>

int main() {

    const MutableTest mutable_class;

    std::cout << mutable_class.GetValue() << "\n";
    std::cout << mutable_class.GetValue() << "\n";
    std::cout << mutable_class.GetValue() << "\n";
    std::cout << mutable_class.GetCounter() << "\n";

    return 0;
}