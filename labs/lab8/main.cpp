#include <iostream>
#include "Stack.h"

int main() {
    try {
        Stack<int> S(5);

        for (int i = 1; i < 6; i++) {
            S.push(i);
        }
        S.show();

        S.pop(0);
        S.pop(0);
        S.show();

        std::cout << S.size() << "\t" << S.top() << "\t" << S.empty() << std::endl;
    }
    catch (std::bad_alloc& e) {
        std::cerr << "Ex1: " << "Allocating of necessary memory area for stack is impossible" << std::endl;
    }
    catch (std::overflow_error& e) {
        std::cerr << "Ex2: " << e.what() << std::endl;
    }
    catch (std::out_of_range& e) {
        std::cerr << "Ex3: " << e.what() << std::endl;
    }
    catch (std::logic_error& e) {
        std::cerr << "Ex4: " << e.what() << std::endl;
    }

    return 0;
}
