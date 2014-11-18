#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

// a = f/m

class Data
{

public:
    float jumpF = 200; // Force in Newtons (kg*m/s^2)
    float gravityAcceleration=9.8; // (s/t^2)

};

class PhysicalCharacteristics
{

public:
    float mass=0; // Mass in kg

    float speedValue=0;
    float speedAngel=0;

    float accelerationValue=0;
    float accelerationAngel=0;

};

class Player :public PhysicalCharacteristics
{

public:

    sf::RectangleShape playerSprite;
    bool multi;

    struct massCenter{
        float x;
        float y;
    };

    Player()
    {
        playerSprite.setSize(sf::Vector2f(50, 50));
        playerSprite.setFillColor(sf::Color::Red);
        playerSprite.setPosition(512-25, 550);
    }

    massCenter getMassCenter(){
        massCenter mc;

        mc.x = playerSprite.getPosition().x + (playerSprite.getSize().x/2);
        mc.y = playerSprite.getPosition().y + (playerSprite.getSize().y/2);

        return mc;

    }

    void setMultiJump(bool data){

        multi=data;

    }

    bool isMultiJumpable(){
        return multi;
    }

    void jump(float deltaTime)
    {

        Data date;

        speedValue-=date.gravityAcceleration*deltaTime;
        playerSprite.move(0, -speedValue);
        cout << speedValue << endl;
    }

    void playerMove(float deltaTime){

        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
        {
            playerSprite.move(200*deltaTime, 0);
        }

        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
        {
            playerSprite.move(-200*deltaTime, 0);
        }


    }
};


class Board :public PhysicalCharacteristics
{

public:
    sf::RectangleShape boardSprite;

    Board(int n, sf::Vector2f pos){

        boardSprite.setSize(sf::Vector2f(n, 2));
        boardSprite.setFillColor(sf::Color::Blue);
        boardSprite.setPosition(pos);

    }

};


int main()
{

    Player gracz;
    gracz.mass=46; // in kg
    gracz.setMultiJump(false);

    Board  board1(70, sf::Vector2f(300,480));

    sf::Clock delta;
    float deltaTime;
    bool whileJump = false;
    Data dat;

    sf::RenderWindow WindowApp(sf::VideoMode(1024, 600), "Symulacja odbicia pilki");
    WindowApp.setVerticalSyncEnabled(true);

    while (WindowApp.isOpen())
    {
        deltaTime = delta.restart().asSeconds();
        sf::Event event;

        while (WindowApp.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WindowApp.close();

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space )
            {
                if(gracz.isMultiJumpable()){
                    gracz.speedValue=dat.jumpF/gracz.mass;
                    whileJump = true;
                }else if(!gracz.isMultiJumpable()  && whileJump == false){
                    gracz.speedValue=dat.jumpF/gracz.mass;
                    whileJump = true;
                }
            }
        }

        if(whileJump)
        {
            gracz.jump(deltaTime);
            if(gracz.playerSprite.getPosition().y > 550)
            {
                gracz.playerSprite.setPosition(gracz.playerSprite.getPosition().x, 550);
                whileJump=false;
                gracz.accelerationValue=0;
            }
        }

        gracz.playerMove(deltaTime);

        WindowApp.clear();
        WindowApp.draw(board1.boardSprite);
        WindowApp.draw(gracz.playerSprite);
        WindowApp.display();
    }

    return EXIT_SUCCESS;
}
