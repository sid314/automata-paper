#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

std::vector<sf::RectangleShape> squares;
std::vector<std::vector<int>> coordinates;
std::vector<int> value;

float division = 8;
float space = 2;
bool classicUI = false;
void createsq(float margin_left)
{

    float wWidth = 1280 - 100;
    float wHeight = 1280 - 100;
    sf::RectangleShape sq;
    sq.setSize(
        {(wWidth / division) - (space / 2), (wHeight / division) - (space / 2)});

    if (classicUI == true)
    {
        sq.setFillColor(sf::Color(49, 41, 64));
    }
    else
    {
        sq.setFillColor(sf::Color::White);
    }
    // sq.setFillColor(sf::Color(49, 41, 64));
    int v = 0;
    int two = 4;
    for (int i = 0; i < division; i++)
    {
        for (int j = 0; j < division; j++)
        {
            squares.push_back(sq);
            value.push_back(v);
            coordinates.push_back({i, j});
        }
    }

    for (int i = 0; i < division; i++)
    {
        for (int j = 0; j < division; j++)
        {
            squares[i * division + j].setPosition(
                {(float)i * (wWidth / division) + space / 2 + margin_left / 2,
                 (float)j * (wHeight / division) + space / 2 + margin_left});
        }
    }
}

void changePixel(int i = 0, int j = 0)
{
    if (value[i * division + j] == 0)
    {
        value[i * division + j] = 1;
        if (classicUI == true)
        {
            squares[i * division + j].setFillColor(sf::Color::Green);
        }
        else
        {
            squares[i * division + j].setFillColor(sf::Color::White);
        }
    }
    else if (value[i * division + j] == 1)
    {
        value[i * division + j] = 0;
        if (classicUI == true)
        {
            squares[i * division + j].setFillColor(sf::Color(49, 41, 64));
        }
        else
        {
            squares[i * division + j].setFillColor(sf::Color::White);
        }
    }
}
void fill(int i, int j)
{
    value[i * division + j] = 1;
    if (classicUI == true)
    {
        squares[i * division + j].setFillColor(sf::Color::Green);
    }
    else
    {
        squares[i * division + j].setFillColor(sf::Color::Black);
    }
}

void fill_color(int i, int j, int R, int G, int B, float A)
{
    // value[i * division + j] = 1;
    squares[i * division + j].setFillColor(sf::Color(R, G, B, A));
}

void kill(int i, int j)
{
    value[i * division + j] = 0;
    if (classicUI == true)
    {
        squares[i * division + j].setFillColor(sf::Color(49, 41, 64));
    }
    else
    {
        squares[i * division + j].setFillColor(sf::Color::White);
    }
}
int makeNBD(int in, int jn)
{
    std::vector<int> coll;
    for (int i = in - 1; i < in + 2; i++)
    {
        for (int j = jn - 1; j < jn + 2; j++)
        {
            if (value[i * division + j] == 1 && i != 0 && j != 0 && i != division &&
                j != division)
            {
                if (!(i == in && j == jn))
                {
                    coll.push_back((int)1);
                }
            }
        }
    }
    return coll.size();
}

void Show_Moore_NBD()
{
    int neightbours[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    for (int i = 1; i < division - 1; i++)
    {
        for (int j = 1; j < division - 1; j++)
        {
            for (auto &n : neightbours)
            {
                if (makeNBD(i, j) == n /*&& value[i * division + j] == 1*/)
                {
                    if (classicUI == true)
                    {
                        fill_color(i, j, 0, 255, 0, 20 * n);
                    }
                    else
                    {
                        fill_color(i, j, 0, 0, 0, 30 * n);
                    }
                }
                if (value[i * division + j] == 1)
                {
                    fill(i, j);
                }
            }
        }
    }
}


void Show_Moore_NBD_specific(int in, int jn)
{
    int neightbours[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    for (int i = in - 1; i < in + 2; i++)
    {
        for (int j = jn - 1; j < jn + 2; j++)
        {
            for (auto &n : neightbours)
            {
                // if (makeNBD(i, j) == n /*&& value[i * division + j] == 1*/)
                    if (classicUI == true)
                    {
                        fill_color(i, j, 0, 255, 0, 20);
                    }
                    else
                    {
                        fill_color(i, j, 0, 0, 0, 30);
                    }

                if (value[i * division + j] == 1)
                {
                    fill(i, j);
                }
            }
        }
    }
}

std::fstream fs;
void pattern(std::string filename, int rows = 4)
{
    fs.open(filename);
    std::vector<std::string> seed;
    std::string temp;
    while (fs >> temp)
    {
        seed.push_back(temp);
    }

    int row = 0;
    int y = 0;
    for (int i = 0; i < seed.size(); i++)
    {
        int succeser = i;
        if (i % (seed.size() / rows) == 0)
        {
            row = (i / (seed.size() / rows));
            y = row;
        }
        succeser = i - (seed.size() / rows) * row;

        if (seed[i] == "0")
        {
            kill(4 + succeser - ((seed.size() / rows) / 2), 4 + y - rows / 2);
        }
        else if (seed[i] == "1")
        {
            fill(4 + succeser - ((seed.size() / rows) / 2), 4 + y - rows / 2);
        }
        std::cout << seed[i];
    }
}

int main()
{
    const int wWidth = 1280;
    const int wHeight = 1280;

    sf::RenderWindow window(sf::VideoMode({wWidth, wHeight}), "SFML works!");
    window.setFramerateLimit(120);
    window.setPosition({500, 0});

    sf::RectangleShape menu({wWidth, 100});
    menu.setFillColor(sf::Color(36, 36, 46));

    sf::RectangleShape pause({170, 60});
    menu.setFillColor(sf::Color(36, 36, 46));
    pause.setFillColor(sf::Color(49, 41, 64));
    pause.setPosition({1000, 30});

    sf::Font font("C:\\Users\\HP\\Desktop\\New folder (2)\\automata-paper\\src\\fonts\\NataSans-VariableFont_wght.ttf");
    sf::Text generations(font);
    generations.setPosition({20, 50 - 15});
    generations.setString("Generations");
    generations.setCharacterSize(30);
    generations.setFillColor(sf::Color::White);

    sf::Text pauset(font);
    pauset.setPosition({1020, 50 - 15});
    pauset.setString("pause 5s");
    pauset.setCharacterSize(30);
    pauset.setFillColor(sf::Color::White);

    int gen = 0;
    /////////////
    // gen changing code here//
    /////////////

    sf::Text gen_number(font);
    gen_number.setPosition({300, 50 - 15});
    gen_number.setCharacterSize(30);
    gen_number.setFillColor(sf::Color::White);

    createsq(100);

    pattern("C:\\Users\\HP\\Desktop\\New folder (2)\\automata-paper\\src\\try.txt", 6);

    // std::cout << makeNBD(12, 11);
    while (window.isOpen())
    {
        sf::sleep(sf::milliseconds(100));

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto *Keypressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (Keypressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
            else if (const auto *LmouseClick = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (LmouseClick->button == sf::Mouse::Button::Left)
                    sf::sleep(sf::seconds(5));
            }
        }
        if (classicUI == true)
        {
            window.clear(sf::Color(72, 72, 79));
        }
        else
        {
            window.clear(sf::Color::White);
        }

        gen++;
        gen_number.setString(std::to_string(gen));
        window.draw(menu);
        window.draw(pause);
        window.draw(pauset);
        window.draw(generations);
        window.draw(gen_number);
        for (int i = 0; i < division; i++)
        {
            for (int j = 0; j < division; j++)
            {
                window.draw(squares[i * division + j]);
            }
        }
        Show_Moore_NBD_specific(4,4);
        window.display();
    }
}
