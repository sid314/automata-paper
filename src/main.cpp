#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

std::vector<sf::RectangleShape> squares;
std::vector<std::vector<int>> coordinates;
std::vector<int> value;
std::vector<int> valueCopy;
std::vector<int> lifeSpan;

class Cell
{
public:
    int state;
    // 0 = dont do anything
    // 1 = kill
    // 2 = bring to life
};
int maxlives = 15;
int lives[50][50];

void initLives()
{
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            lives[i][j] = 0;
        }
    }
}

float division = 50;
float space = 5;
void createsq(float margin_left)
{

    float wWidth = 1280 - 100;
    float wHeight = 1280 - 100;
    sf::RectangleShape sq;
    sq.setSize(
        { (wWidth / division) - (space / 2), (wHeight / division) - (space / 2) });
    sq.setFillColor(sf::Color(49, 41, 64));
    int v = 0;
    int two = 4;
    for (int i = 0; i < division; i++)
    {
        for (int j = 0; j < division; j++)
        {
            squares.push_back(sq);
            value.push_back(v);
            lifeSpan.push_back(two);
            coordinates.push_back({ i, j });
        }
    }

    for (int i = 0; i < division; i++)
    {
        for (int j = 0; j < division; j++)
        {
            squares[i * division + j].setPosition(
                { (float)i * (wWidth / division) + space / 2 + margin_left / 2,
                 (float)j * (wHeight / division) + space / 2 + margin_left });
        }
    }
}

void changePixel(int i = 0, int j = 0)
{
    if (value[i * division + j] == 0)
    {
        value[i * division + j] = 1;
        squares[i * division + j].setFillColor(sf::Color::Green);
        lives[i][j] = maxlives;
    }
    else if (value[i * division + j] == 1)
    {
        value[i * division + j] = 0;
        squares[i * division + j].setFillColor(sf::Color(49, 41, 64));
    }
}
void fill(int i, int j)
{
    value[i * division + j] = 1;
    squares[i * division + j].setFillColor(sf::Color::Green);
    lives[i][j] = maxlives;
}

void kill(int i, int j)
{
    value[i * division + j] = 0;
    squares[i * division + j].setFillColor(sf::Color(49, 41, 64));
    lives[i][j] = 0;
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

void rule2()
{

    // sf::sleep(sf::milliseconds(500));
    Cell cells[50][50];

    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            cells[i][j].state = 0;
        }
    }
    for (int i = 1; i < division - 1; i++)
    {
        for (int j = 1; j < division - 1; j++)
        {
            int life = lives[i][j];
            int state = cells[i][j].state;

      int aliveNeighbours = makeNBD(i, j);
      if (aliveNeighbours < 2 || aliveNeighbours > 4)
      {
        state = 1;
      }
      // if (life < 1) {
      //   state = 1;
      // }
      // if (aliveNeighbours == 2 || aliveNeighbours == 4) {
      //   life -= 2;
      // }
      // if (aliveNeighbours == 1 || aliveNeighbours == 5) {
      //   life -= 3;
      // }
      // if (aliveNeighbours == 0 || aliveNeighbours == 6) {
      //   life -= 4;
      // }
      // if (aliveNeighbours == 7) {
      //   life -= 5;
      // }
      // if (aliveNeighbours == 8) {
      //   life -= 6;
      // }
      if (aliveNeighbours == 3) {
        state = 2;
        life--;
      }
      cells[i][j].state = state;
      lives[i][j] = life;
    }
  }
  for (int i = 1; i < division - 1; i++) {
    for (int j = 1; j < division - 1; j++) {
      if (cells[i][j].state == 1) {
        kill(i, j);

      } else if (cells[i][j].state == 2) {

                fill(i, j);
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
            kill(12 + succeser, 12+y);
        }
        else if (seed[i] == "1")
        {
            fill(12 + succeser, 12+y);
        }
        std::cout << seed[i];
    }
}

int main()
{

    initLives();
    const int wWidth = 1280;
    const int wHeight = 1280;

    sf::RenderWindow window(sf::VideoMode({ wWidth, wHeight }), "SFML works!");
    window.setFramerateLimit(60);
    window.setPosition({ 500, 0 });

    sf::RectangleShape menu({ wWidth, 100 });
    menu.setFillColor(sf::Color(36, 36, 46));

    sf::RectangleShape pause({ 170, 60 });
    menu.setFillColor(sf::Color(36, 36, 46));
    pause.setFillColor(sf::Color(49, 41, 64));
    pause.setPosition({ 1000, 30 });

    sf::Font font("C:\\Users\\HP\\Desktop\\New folder (2)\\automata-paper\\src\\fonts\\NataSans-VariableFont_wght.ttf");
    sf::Text generations(font);
    generations.setPosition({ 20, 50 - 15 });
    generations.setString("Generations");
    generations.setCharacterSize(30);
    generations.setFillColor(sf::Color::White);

    sf::Text pauset(font);
    pauset.setPosition({ 1020, 50 - 15 });
    pauset.setString("pause 5s");
    pauset.setCharacterSize(30);
    pauset.setFillColor(sf::Color::White);

    int gen = 0;
    /////////////
    // gen changing code here//
    /////////////

    sf::Text gen_number(font);
    gen_number.setPosition({ 300, 50 - 15 });
    gen_number.setCharacterSize(30);
    gen_number.setFillColor(sf::Color::White);

    createsq(100);

    pattern("C:\\Users\\HP\\Desktop\\New folder (2)\\automata-paper\\src\\try.txt", 3);

    std::cout << makeNBD(12, 11);
    while (window.isOpen())
    {
        // sf::sleep(sf::milliseconds(1));

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* Keypressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (Keypressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
            else if (const auto* LmouseClick =
                event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (LmouseClick->button == sf::Mouse::Button::Left)
                    sf::sleep(sf::seconds(5));
            }
        }
        window.clear(sf::Color(72, 72, 79));
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
        rule2();
        window.display();
         if (gen == 1 /*|| gen == 10 || gen == 42*/)
         {
          sf::sleep(sf::seconds(14));
         }
    }
}
