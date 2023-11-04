#pragma once
#include <SFML/Graphics.hpp>

class Human
{
private:
    sf::CircleShape dir;
    sf::Vector2f startPosition;
    sf::Vector2f currentPosition;
    sf::Vector2f currentDirection;
    sf::Color color;
    float distance;

    sf::Clock timer;
   
    int chance;

    bool infected;
    bool heavyIll;
    bool lightIll;

    void initVariables();
    void initShape();

public:
    const float borderRadius = 100.f;
    float movementSpeed = 4.f;
    const float radius = 4.f;
    const float tack = 0.4;
    sf::CircleShape shape;

    Human();
    virtual ~Human();

    Human(Human&& other) noexcept;
    Human& operator=(Human&& other) noexcept;
    Human(const Human&) = delete;
    Human& operator=(const Human&) = delete;

    sf::Vector2f chooseDirection();
    
    bool isLightIll();
    bool isHeavyIll();
    bool isInfected();

    void infect();
    void recover();

    void updateWindowBoundsCollision(const sf::RenderTarget* target);
    void update(const sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
};
