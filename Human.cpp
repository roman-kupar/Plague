#include "Human.h"
#include "Random.h"
#include "WindowParamets.h"
#include <cmath>

Human::Human(Human&& other) noexcept
    : infected(other.infected), color(other.color), tick(other.tick), tack(other.tack),
    movementSpeed(other.movementSpeed), startPosition(other.startPosition),
    currentPosition(other.currentPosition), currentDirection(other.currentDirection)
{
    // Move the shape and reset the other object's shape
    shape = std::move(other.shape);
    other.shape = sf::CircleShape();

    // Reset the other object's properties
    other.infected = false;
    other.color = sf::Color::Blue;
    other.tack = 0.5;
    other.movementSpeed = 0.0f;
}

Human& Human::operator=(Human&& other) noexcept
{
    if (this != &other)
    {
        // Move the shape and reset the other object's shape
        shape = std::move(other.shape);
        other.shape = sf::CircleShape();

        // Move other properties
        infected = other.infected;
        color = other.color;
        tick = other.tick;
        tack = other.tack;
        movementSpeed = other.movementSpeed;
        startPosition = other.startPosition;
        currentPosition = other.currentPosition;
        currentDirection = other.currentDirection;

        // Reset the other object's properties
        other.infected = false;
        other.color = sf::Color::Blue;
        other.tack = 0.5;
        other.movementSpeed = 0.0f;
    }
    return *this;
}


Human::Human()
{

    initVariables();
    initShape();
}

Human::~Human()
{

}

void Human::initVariables()
{
    startPosition = sf::Vector2f(Random::GenerateFloat(0.f, static_cast<float>(WindowParametrs::getVideoWidth())),
                                  Random::GenerateFloat(0.f, static_cast<float>(WindowParametrs::getVideoHeight())));
    currentPosition = startPosition;
    currentDirection = chooseDirection();

    this->color = sf::Color::Blue;
    this->heavyIll = false;
    this->lightIll = false;
    this->infected = false;
}

void Human::initShape()
{
    
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setOrigin(radius / 2.f, radius / 2.f);
    shape.setPosition(startPosition);
    shape.setOutlineColor(sf::Color::Magenta);
    shape.setOutlineThickness(1.f);
}

void Human::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
    sf::FloatRect bounds = shape.getGlobalBounds();
    sf::Vector2f position = shape.getPosition();
    sf::Vector2u targetSize = target->getSize();

    position.x = std::max(bounds.width / 2.f, std::min(position.x, static_cast<float>(targetSize.x) - bounds.width / 2.f));
    position.y = std::max(bounds.height / 2.f, std::min(position.y, static_cast<float>(targetSize.y) - bounds.height / 2.f));

    shape.setPosition(position);
    
    if (position.x <= bounds.width / 2.f || position.x >= targetSize.x - bounds.width / 2.f ||
        position.y <= bounds.height / 2.f || position.y >= targetSize.y - bounds.height / 2.f) {
        currentDirection = chooseDirection();
    }
}

bool Human::isInfected()
{
    return this->infected;
}
bool Human::isHeavyIll()
{
    return this->heavyIll;
}
bool Human::isLightIll()
{
    return this->lightIll;
}
void Human::infect()
{
    infected = true;

    this->color = sf::Color::Red;
    this->shape.setFillColor(this->color);
    this->shape.setOutlineColor(this->color);
    this->tick.restart();
    this->tack = 0.5;

}

sf::Vector2f Human::chooseDirection()
{
    float x = startPosition.x;
    float y = startPosition.y;

    float directive_x = Random::GenerateFloat(x - borderRadius, x + borderRadius);
    float directive_y = Random::GenerateFloat(y - borderRadius, y + borderRadius);

    return sf::Vector2f(directive_x, directive_y);
}

void Human::update(const sf::RenderTarget* target)
{
    sf::Vector2f directionVector = currentDirection - currentPosition;
    float distanceToDirection = std::hypot(directionVector.x, directionVector.y);

    if (distanceToDirection <= movementSpeed)
    {
        currentPosition = currentDirection;
        shape.setPosition(currentPosition);
        currentDirection = chooseDirection();
    }
    else
    {
        sf::Vector2f normalizedDirection = directionVector / distanceToDirection;
        sf::Vector2f newPosition = currentPosition + normalizedDirection * movementSpeed;
        currentPosition = newPosition;
        shape.setPosition(currentPosition);
    }

    if (isInfected())
    {
        if (this->tick.getElapsedTime().asSeconds() >= this->tack)
        {
            this->tack += 0.5;
            this->color.r -= 4;
            if (this->movementSpeed > 0.f)  
            {
                this->movementSpeed -= 0.1f;  
            }
            else if (this->movementSpeed<0.f)
            {
                this->movementSpeed = 0.f;  
            }
            this->shape.setFillColor(this->color);
            this->shape.setOutlineColor(this->color);
        }
    }

    updateWindowBoundsCollision(target);
}

void Human::render(sf::RenderTarget* target)
{
    target->draw(shape);
}
