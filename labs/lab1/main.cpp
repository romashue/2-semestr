#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>

using namespace std;
using namespace chrono;


class AnimatedText {
private:
    string m_text; // введенный текст
    int m_duration; // введенное время анимации

    milliseconds m_switchTime; // пауза анимации в мс

    int m_letter_stp = 0; // текущий индекс 

    milliseconds m_start;
    bool m_start_of_Animation = true;

public:
    AnimatedText (const string &text, int duration) {
        /* сохраняем введенные данные и определяем m_switchTime в мс с точностью до 2-х знаков */
        m_text = text;
        m_duration = duration;
        m_switchTime = (milliseconds)m_duration * 100 / m_text.size();
    }
    ~AnimatedText() {}

    void Animate(bool& nextt, sf::Text& txt) {
        // если анимация только началась, фиксируем m_start
        if (m_start_of_Animation) {
            m_start = duration_cast<milliseconds>(
                system_clock::now().time_since_epoch()
                ) / 10;
            m_start_of_Animation = false;
        }

        string word = "";

        milliseconds now = duration_cast<milliseconds>(
            system_clock::now().time_since_epoch()
            ) / 10;

        // если прошло m_switchTime миллисекунд...
        if ((now - m_start) == m_switchTime)
        {
            m_start += m_switchTime;

            if (m_text[m_letter_stp] == ' ') {
                m_letter_stp += 2;
            }
            else {
                m_letter_stp++;
            }

            for (int i = 0; i < m_letter_stp; i++) {
                word += m_text[i];
            }

            txt.setString(word);  // задаем строку word для вывода в окно SFML
        }
        if (m_letter_stp >= m_text.length()) {
            nextt = false;
        }
    }
};

int main()
{
    cout << "Enter a text:" << endl;
    string text;
    getline(cin, text);

    cout << "Enter a duration" << endl;
    int duration;
    cin >> duration;

    sf::Text txt;

    sf::RenderWindow window(sf::VideoMode(1000, 400), "Lab #1");
    sf::Font font;
    if (!font.loadFromFile("Fonts/caviar-dreams.ttf"))
    {
        cout << "Loading of font fall" << endl;
    }

    txt.setFont(font);
    txt.setPosition(50, 50);
    txt.setCharacterSize(50);
    txt.setFillColor(sf::Color::Red);
    txt.setStyle(sf::Text::Bold);

    AnimatedText one(text, duration);

    bool nextt = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // если продолжаем работу анимации...
        if (nextt) {
            one.Animate(nextt, txt);
        }

        window.clear();
        window.draw(txt);
        window.display();
    }

    return 0;
}
