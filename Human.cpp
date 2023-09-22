#include "Human.h"
#include "Random.h"
#include "WindowParamets.h"
#include <cmath>



Human::Human()
    : infected(false)
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

    
}

void Human::initShape()
{
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Black);
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
void Human::infect()
{
    infected = true;
    shape.setFillColor(sf::Color::Red);
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

    updateWindowBoundsCollision(target);
}

void Human::render(sf::RenderTarget* target)
{
    target->draw(shape);
}
