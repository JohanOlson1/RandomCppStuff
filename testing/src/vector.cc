#include "vector.h"

#include <algorithm>
#include <iostream>
#include <vector>

void VectorInitialization() {
    auto print_vector = [&](std::vector<float> vector) {
        for(float c : vector)
            std::cout << c << ' ';
        std::cout << '\n';  
    };

    constexpr unsigned N_small{100};

    // 1. Brace list
    std::vector<float> vector1{1.0f, 2.0f, 3.0f};

    // 2. Push back
    std::vector<float> vector2;
    for(unsigned i = 0; i < N_small; ++i) {
        vector2.push_back(static_cast<float>(i));
    }

    // 3. Assign
    std::vector<float> vector3;
    vector3.assign(N_small, 1.0f);

    // 4. Overloaded Constructor
    std::vector<float> vector4(N_small, 1.0f);

    // 5. Index
    std::vector<float> vector5(N_small);
    for(unsigned i = 0; i < N_small; ++i) {
        vector5.at(i) = static_cast<float>(i);
    }

    // 6. Using another vector
    std::vector vector6(vector5);

    // 7. Using an array
    constexpr unsigned N_array{5};
    float array[N_array]{1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    std::vector<float> vector7(array, array + N_array);

    // 8. Fill method
    std::vector<float> vector8(N_small);
    std::fill_n(vector8.begin(), N_small, 1.0f);

    // 9. Default initialization, zeros!
    std::vector<float> vector9(N_small);

    print_vector(vector9);
}