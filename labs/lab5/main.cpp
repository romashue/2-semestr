#include <iostream>
#include "inc/Vector.h"
#include "inc/VectorBool.h"

// вывод значений массива
void showElements (const Vector<bool>& v) {
    for (int i = 0; i < v.getSize(); i++)
        std::cout << v[i] << '\t';
    std::cout << std::endl;
}

int main() {
    Vector<bool> v;
    v.push_back(true);
    v.push_back(false);
    v.push_back(true);
    showElements(v);
    v[1] = true;
    showElements(v);
    std::cout << "Size: " << v.getSize() << std::endl;
    v.insert(2, false);
    showElements(v);
    v.erase(3);
    showElements(v);

    return 0;
}
