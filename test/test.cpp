#include <iostream>

struct MyStruct {
    int value;

    // Overload the '>' operator
    bool operator>(const MyStruct& other) const {
        return value > other.value;
    }
};

int main() {
    MyStruct a = {5};
    MyStruct b = {10};

    if (a > b) {
        std::cout << "a is greater than b." << std::endl;
    } else {
        std::cout << "b is greater than or equal to a." << std::endl;
    }

    return 0;
}
