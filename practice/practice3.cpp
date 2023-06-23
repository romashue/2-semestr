#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <stdlib.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "windows.h"

const double PI = 3.141592653589793;


class KinematicSolver
{
private:
    double m_alpha = NULL;
    double m_beta = NULL;

    double m_l1 = NULL;
    double m_l2 = NULL;

    double m_m[2] = { NULL };

    double m_sharnir[2] = { NULL };

    void set_data()
    {
        std::cout << "enter l1 and l2: ";
        std::cin >> m_l1;
        std::cin >> m_l2;
        std::cout << "\n";
        std::cout << "enter m(x,y): ";
        for (int i = 0; i < 2; i++)
        {
            std::cin >> m_m[i];
        }
    }

    int check_data()
    {
        if ((m_l1 == NULL) || (m_l2 == NULL))
        {
            std::cout << "incorrect length" << std::endl;
            return 1;
        }
        if (m_m[0] == NULL || m_m[1] == NULL)
        {
            std::cout << "incorrect m(x,y)" << std::endl;
            return 1;
        }

        double hyp = pow((m_m[0] * m_m[0] + m_m[1] * m_m[1]), 0.5);
        double maxx = std::max(hyp, m_l1);
        maxx = std::max(maxx, m_l2);


        if (maxx > (hyp + m_l1 + m_l2 - maxx))
        {
            std::cout << "This traingle is not exist";
            return 1;
        }
        return 0;
    }

    void Solve()
    {
        double hypotenuse = sqrt(m_m[0] * m_m[0] + m_m[1] * m_m[1]);
        double q2 = (pow(m_l1, 2) - pow(m_l2, 2) + pow(hypotenuse, 2));
        m_alpha = acos(m_m[0] / hypotenuse) - acos(q2 / (2 * hypotenuse * m_l1));
        m_beta = PI - acos((pow(m_l1, 2) + pow(m_l2, 2) - pow(hypotenuse, 2)) / (2 * m_l1 * m_l2));

        m_sharnir[0] = m_l1 * cos(m_alpha);
        m_sharnir[1] = m_l1 * sin(m_alpha);
    }


public:

    KinematicSolver()
    {
        set_data();
        check_data();
        Solve();
    }
    ~KinematicSolver() = default;

    void getAlphaBeta() const
    {
        //return m_alpha, m_beta;
        std::cout << (180 * m_alpha) / PI << " " << (180 * m_beta) / PI << "\n";
    }

    double get_coord_sharnir(bool x) const
    {
        //std::cout << m_sharnir[0] << " " << m_sharnir[1] << "\n";
        return m_sharnir[x];
    }
    double get_M(bool x) const
    {
        return m_m[x];
    }
};

int main()
{
    std::cout << "Hello World!\n";
    KinematicSolver a;
    a.getAlphaBeta();
    double k_x = round(a.get_coord_sharnir(0) * 20);
    double k_y = round(a.get_coord_sharnir(1) * 20);

    double m_x = round(a.get_M(0) * 20);
    double m_y = round(a.get_M(1) * 20);

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "solver", sf::Style::Close);
    sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            sf::Vertex line_ox[] =
            {
             sf::Vertex(sf::Vector2f(0, 500)),
             sf::Vertex(sf::Vector2f(10000, 500))
            };
            line_ox->color = sf::Color::Magenta;
            window.draw(line_ox, 2, sf::Lines);
            sf::Vertex line_oy[] =
            {
             sf::Vertex(sf::Vector2f(500, 0)),
             sf::Vertex(sf::Vector2f(500, 10000))
            };
            line_oy->color = sf::Color::Magenta;
            window.draw(line_oy, 2, sf::Lines);

            sf::Vertex line_l1[] =
            {
             sf::Vertex(sf::Vector2f(500, 500)),
             sf::Vertex(sf::Vector2f(500 + k_x, 500 + k_y))
            };

            window.draw(line_l1, 2, sf::Lines);


            sf::Vertex line_l2[] =
            {
             sf::Vertex(sf::Vector2f(k_x + 500, k_y + 500)),
             sf::Vertex(sf::Vector2f(m_x + 500,-m_y + 500))
            };
            window.draw(line_l2, 2, sf::Lines);

            sf::Vertex line_hyp[] =
            {
             sf::Vertex(sf::Vector2f(500, 500)),
             sf::Vertex(sf::Vector2f(m_x + 500,-m_y + 500))
            };
            line_hyp->color = sf::Color::Green;
            window.draw(line_hyp, 2, sf::Lines);



            window.display();

            while (window.waitEvent(event))
            {
                if (event.type == sf::Event::Closed) { window.close(); }
            }
        }
    }
}