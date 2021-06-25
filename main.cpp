#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>

class cell {
public:
    int x, y;
    int size;

    sf::Sprite cellSprite;

    cell(int x, int y) : x(x), y(y),size(10) {};
    /*/sf::RectangleShape draw() {
        sf::RectangleShape rectangle;
        rectangle.setPosition(x, y);
        rectangle.setFillColor(sf::Color::Green);
        rectangle.setSize(sf::Vector2f(size,size));

        return rectangle;
    }
    */

    sf::Sprite draw() {
        cellSprite.setPosition(x, y);
        cellSprite.setOrigin(7.5, 7.5);
        return cellSprite;
    }

    bool check(int sx, int sy) {
        if (sx == x && sy == y) return true;
        else return false;
    }

    cell() {}
};

class brick {
public:
    int x, y;
    sf::Sprite cellSprite;
    

    sf::Sprite draw() {
        cellSprite.setPosition(x, y);
        cellSprite.setOrigin(7.5, 7.5);
        
        return cellSprite;
    }

    bool check(int sx, int sy) {
        if (sx == x && sy == y) return true;
        else return false;
    }

    brick(int x, int y):x(x), y(y) {
        
        
        
    }
};

enum {
    right,left,up,down,
};




    

class food {
public:
    int x, y;
    int size;
    sf::Texture tex, cherries;
    sf::Sprite appleSprite;
    sf::Texture empty;
    int step;
    int time;


    /*/sf::RectangleShape draw() {
        sf::RectangleShape rectangle;
        rectangle.setPosition(x, y);
        rectangle.setFillColor(sf::Color::Red);
        rectangle.setSize(sf::Vector2f(size, size));

        return rectangle;
    }
    */

    void update() {
        x = ((rand() % 32) * 15) + 15;
        y = ((rand() % 29) * 15)+75;
    }
    

    bool check(int sx, int sy) {
        if (x == sx && y == sy) {
            update();
            step++;
            time = 0;
            
            
            return true;
        }
        return false;
    }

    sf::Sprite draw() {

        if (step % 5 == 0) {
            if (time < 30) {
                if (time % 8 < 4)
                    appleSprite.setTexture(cherries);
                else
                    appleSprite.setTexture(empty);
            }
            else {
                x = (rand() % 33) * 15;
                y = (rand() % 33) * 15;
                step++;
                time = 0;
            }
        }
        else {
            appleSprite.setTexture(tex);
        }


        appleSprite.setPosition(x, y);

        return appleSprite;
    }

    food() : x(75), y(75), size(15), step(1), time(0) {
        tex.loadFromFile("apple.png");
        appleSprite.setTexture(tex);
        appleSprite.setOrigin(7.5, 7.5);
        cherries.loadFromFile("cherries.png");
        empty.loadFromFile("empty.png");
    }
}food;

class snake {
public:
    int size;
    int x, y;
    int direction;
    int speed;
    sf::Vector2i wpos;

    sf::Texture center, head;

    std::vector<cell> cells;

    void changesize(int s) {
        if (s > size) {
            cells.at(size - 1).cellSprite.setTexture(center);
            size=s;
            while (cells.size() < size) 
                cells.push_back(cell(-15, -15));
          
        }
        else if (s < size) {
            size=s;
            while(cells.size() > size)
                cells.pop_back();
        }
    }

    snake() :x(30), y(120), direction(0), speed(15), size(1) {
        cells.push_back(cell(-15, -15));
        changesize(4);

        center.loadFromFile("snakeSprites/center_up.png");
        head.loadFromFile("snakeSprites/head.png");
    }

    void setRotate(sf::Sprite* sp) {
        if (direction == left)
            sp->setRotation(90);
        else if (direction == right)
            sp->setRotation(-90);
        else if (direction == down)
            sp->setRotation(0);
        else if (direction == up)
            sp->setRotation(180);
    }

    void move(int xx, int yy) {
        for (int i = 0; i < cells.size() - 1; i++) {

            cells.at(i).x = cells.at(i + 1).x;
            cells.at(i).y = cells.at(i + 1).y;

            cells.at(i).cellSprite = cells.at(i + 1).cellSprite;
        }

        
        cells.at(size - 1).x = xx;
        cells.at(size - 1).y = yy;

        cells.at(size - 1).cellSprite.setTexture(head);
        setRotate(&cells.at(size - 1).cellSprite);

        cells.at(size - 2).cellSprite.setTexture(center);
        setRotate(&cells.at(size - 2).cellSprite);
        
    }

    void refresh() {
       
        if (direction == left) {
            x -= speed;
        }
        else if (direction == up) {
            y -= speed;
        }
        else if (direction == right) {
            x += speed;
        }
        else if (direction == down) {
            y += speed;
        }
        move(x, y);
        if (x > 525) x = 0;
        if (x < 0) x = 525;
        if (y < 60) y = 525;
        if (y > 525) y = 45;
        
    }

    void draw(sf::RenderWindow *win) {
        for (int i = 0; i < cells.size() ; i++) {
            win->draw(cells.at(i).draw());
        }
    }
}snake;

class menu{
    private:
        sf::Font font;
        sf::Text text;
    public:
        std::string title;
        int selectedItem;
        sf::Vector2f titlePos;

        void draw(sf::RenderWindow *win){
            text.setCharacterSize(36);
            text.setString(title);
            text.setPosition(titlePos);
            text.setFillColor(sf::Color::White);
            win->draw(text);

            text.setCharacterSize(24);
            text.setString("Play");
            text.setPosition(sf::Vector2f(230, 232));
            if(selectedItem==0)
                text.setFillColor(sf::Color::Green);
            else
                text.setFillColor(sf::Color::White);
            win->draw(text);

            text.setCharacterSize(24);
            text.setString("Exit");
            text.setPosition(sf::Vector2f(230, 262));
            if(selectedItem==1)
                text.setFillColor(sf::Color::Green);
            else
                text.setFillColor(sf::Color::White);
            win->draw(text);
        }
        
        menu():title("Snake"), selectedItem(0), titlePos(sf::Vector2f(208, 172)){
            font.loadFromFile("font.ttf");
            text.setFont(font);
        }
    }menu;


class game {
private:
    sf::Texture backgroundTexture;
    sf::Sprite background;

    sf::RectangleShape line;
    sf::Text scoreText;
    sf::Font font;

    std::vector<brick> bricks;
    sf::Texture brickTexture;
    
public:

    bool isGameOver;
    
    void LoadLevel(std::string levelName) {
        sf::Image level;
        level.loadFromFile(levelName);
        for (int i = 0; i < 34; i++) {
            for (int j = 0; j < 34; j++) {
                if (level.getPixel(j, i) == sf::Color::Black)
                    bricks.push_back(brick(j * 15, i * 15));
            }
        }
    }

    void gameover() {
        isGameOver=true;
        snake.changesize(4);
        snake.x = 45;
        snake.y = 105;
        for (int i = 0; i < snake.cells.size(); i++) {
            snake.cells.at(i).x = -15;
            snake.cells.at(i).y=-15;
        }
        std::cout << "gameover";

        menu.title = "Game over";
        menu.titlePos = sf::Vector2f(168, 172);
        
    }

    void keyboardAction() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (snake.direction != right)
                snake.direction = left;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (snake.direction != left)
                snake.direction = right;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (snake.direction != up)
                snake.direction = down;
            menu.selectedItem = 1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (snake.direction != down)
                snake.direction = up;
            menu.selectedItem=0;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            if(menu.selectedItem==1)
                exit(0);
            if(menu.selectedItem==0){
                snake.changesize(4);
                isGameOver=false;
            }

        }
    }

    void draw(sf::RenderWindow* win) {

        win->draw(background);
        

        for (int i = 0; i < bricks.size(); i++) {
            win->draw(bricks.at(i).draw());
        }

        
        scoreText.setString("Score: " + std::to_string(snake.size));
        win->draw(scoreText);

        

        
        
        win->draw(food.draw());
        snake.draw(win);
        win->draw(line);
        
    }

    void gameAction() {
        for (int i = 0; i < snake.cells.size()-1; i++) {
            if (snake.cells.at(i).check(snake.x, snake.y)) {
                gameover();
                std::cout << "cellerr\n";
            }
        }

        if (food.check(snake.x, snake.y)) {
            if ((food.step - 1) % 5 == 0)
                snake.changesize(snake.size + 5);
            else
                snake.changesize(snake.size + 1);
            std::cout << snake.size;
        }

        for (int i = 0; i < bricks.size(); i++) {
            if (bricks.at(i).check(snake.x, snake.y)) {
                gameover();
                std::cout << "brickch\n";
            }
        }

        for (int i = 9; i < bricks.size(); i++) {
            if (bricks.at(i).x == food.x && bricks.at(i).y == food.y) {
                food.update();
            }
        }
        snake.refresh();
    }

    void run() {
        sf::RenderWindow window(sf::VideoMode(525, 525), "Snake");

        sf::Clock clock;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;

        while (window.isOpen())
        {
            sf::Time elapsedTime = clock.restart();
            timeSinceLastUpdate += elapsedTime;
            sf::Time TimePerFrame = sf::seconds(10.0f / 60.0f);

            while (timeSinceLastUpdate > TimePerFrame)
            {
                timeSinceLastUpdate -= TimePerFrame;
                gameAction();
                keyboardAction();
                if (food.step % 5 == 0)
                    food.time++;
            }

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            keyboardAction();
            if(!isGameOver)
                draw(&window);
            else
            menu.draw(&window);

            window.display();
            window.clear();
        }
    }
    game():isGameOver(1) {
        srand(time(0));
        
        font.loadFromFile("font.ttf");
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setPosition(sf::Vector2f(15, 15));

        backgroundTexture.loadFromFile("background.png");
        background.setTexture(backgroundTexture);

        line.setSize(sf::Vector2f(510, 2));
        line.setPosition(sf::Vector2f(5, 45));


        LoadLevel("level.png");

        brickTexture.loadFromFile("brick2.png");
        for (int i = 0; i < bricks.size(); i++) {
            bricks.at(i).cellSprite.setTexture(brickTexture);
        }

    }
} game;

int main()
{
    game.run();
    

    return 0;
}