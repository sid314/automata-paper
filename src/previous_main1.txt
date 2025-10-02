#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

std::vector<sf::RectangleShape> squares;
std::vector<int> value;

float division = 26;
float space = 10;
void createsq(float margin_left)
{

    float wWidth = 1280 - 100;
    float wHeight = 1280 - 100;
    sf::RectangleShape sq;
    sq.setSize({ (wWidth / division) - (space/2), (wHeight / division) - (space/2)});
    sq.setFillColor(sf::Color(49, 41, 64));
    int v = 0;
    for (int i = 0; i < division; i++)
    {
        for (int j = 0; j < division; j++)
        {
            squares.push_back(sq);
            value.push_back(v);
        }

    }

    for (int i = 0; i < division; i++)
    {
        for (int j = 0; j < division; j++)
        {
            squares[i * division + j].setPosition({ (float)i * (wWidth / division) + space / 2 + margin_left/2, (float)j*(wHeight/division) + space / 2 + margin_left});
        }

    }

}

void changePixel(int i = 0, int j = 0)
{
    if (value[i * division + j] == 0)
    {
        value[i * division + j] = 1;
        squares[i * division + j].setFillColor(sf::Color::Green);
    }
    else if (value[i * division + j] == 1)
    {
        value[i * division + j] = 0;
        squares[i * division + j].setFillColor(sf::Color(49, 41, 64));
    }

}

void rule1(int i, int j)
{
    for (int i = 2; i < division - 2; i++)
    {
        for (int j = 2; j < division - 2; j++)
        {
            if (value[i * division + j] == 0 && i!=0 && j!=0)
            {
                changePixel(i, j);
                changePixel(i - 1, j);
                changePixel(i + 1, j);
                changePixel(i, j - 1);
                changePixel(i, j + 1);
            }

        }

    }
}


int main()
{
    const int wWidth = 1280;
    const int wHeight = 1280;

    sf::RenderWindow window(sf::VideoMode({ wWidth, wHeight }), "SFML works!");
    window.setFramerateLimit(60);

    sf::RectangleShape menu({ wWidth, 100 });
    menu.setFillColor(sf::Color(36, 36, 46));

    sf::Font font("C:\\Users\\HP\\Desktop\\automata-paper\\src\\NataSans-VariableFont_wght.ttf");

    sf::Text generations(font);
    generations.setPosition({ 20, 50 - 15 });
    generations.setString("Generations");
    generations.setCharacterSize(30);
    generations.setFillColor(sf::Color::White);

    int gen = 0;
    sf::Text gen_number(font);
    gen_number.setPosition({ 300, 50 - 15 });
    gen_number.setCharacterSize(30);
    gen_number.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* Keypressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (Keypressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        }

        createsq(100);
        changePixel(5, 5);
        sf::sleep(sf::seconds(1));

        window.clear(sf::Color(72, 72, 79));
        gen++;
        gen_number.setString(std::to_string(gen));
        window.draw(menu);
        window.draw(generations);
        window.draw(gen_number);
        for (int i = 0; i < division; i++)
        {
            for (int j = 0; j < division; j++)
            {
                window.draw(squares[i * division + j]);
            }
        }
        window.display();
        rule1(5,5);
    }
}