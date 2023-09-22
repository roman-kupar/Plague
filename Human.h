#pragma once
#include <SFML/Graphics.hpp>

class Human
{
private:
    sf::CircleShape dir;
    sf::Vector2f startPosition;
    sf::Vector2f currentPosition;
    sf::Vector2f currentDirection;
    float distance;
    bool infected;

    void initVariables();
    void initShape();

public:
    const float borderRadius = 100.f;
    const float movementSpeed = 4.f;
    const float radius = 4.f;

    sf::CircleShape shape;

    Human();
    virtual ~Human();

    sf::Vector2f chooseDirection();
    bool isInfected();
    void infect();
    void updateWindowBoundsCollision(const sf::RenderTarget* target);
    void update(const sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
};
