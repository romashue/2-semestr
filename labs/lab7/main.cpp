#include <iostream>
#include <vector>
#include "Figures.h"

using namespace figures;

int main() {
    std::vector<Figure*> figs;

    Figure* trig = new Triangle(1, 2, 2, 3, Color::BLACK);
    Figure* rect = new Rectangle(3, 4, 2, 3, Color::WHITE);
    Figure* circ = new Circle(5, 6, 4, 4, Color::RED);

    figs.push_back(trig);
    figs.push_back(rect);
    figs.push_back(circ);

    for (Figure* i : figs){
        i->getAria();
    }

    for (auto & fig : figs){
        delete fig;
    }

    return 0;
}
