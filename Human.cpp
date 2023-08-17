    #define _USE_MATH_DEFINES

    #include<iostream>
    #include<vector>
    #include "Human.h"
    #include "Random.h"
    #include<cmath>
    #include "WindowParamets.h"


    void Human::initVariables()
    {
	    this->borderRadius = 100.f;
	    this->startPosition = sf::Vector2f(Random::GenerateFloat(0.f, static_cast<float>(WindowParametrs::getVideoWidth())), Random::GenerateFloat(0.f, static_cast<float>(WindowParametrs::getVideoHeight())));
	    this->currentPosition = this->startPosition;
	    this->movementSpeed = 4.f;
	    this->currentDirection = chooseDirection();
        this->radius = 4.f;
    }
    void Human::initShape()
    {
	    this->shape.setRadius(this->radius);
	    this->shape.setFillColor(sf::Color::Black);
        this->shape.setOrigin(this->radius/2.f, this->radius/2.f);
	    this->shape.setPosition(this->startPosition);
	    this->shape.setOutlineColor(sf::Color::Magenta);
	    this->shape.setOutlineThickness(1.f);
    }

    Human::Human()
    {
	    this->initVariables();
	    this->initShape();
    }

    Human::~Human()
    {
	
    }

    void Human::updateWindowBoundsCollision(const sf::RenderTarget* target)
    {
        const float halfWidth = this->shape.getGlobalBounds().width / 2.f;
        const float halfHeight = this->shape.getGlobalBounds().height / 2.f;

        // Left collision
        if (this->shape.getPosition().x - halfWidth <= 0.f)
        {
            this->shape.setPosition(halfWidth, this->shape.getPosition().y);
            this->currentDirection = chooseDirection();
        }

        // Right collision
        if (this->shape.getPosition().x + halfWidth >= target->getSize().x)
        {
            this->shape.setPosition(target->getSize().x - halfWidth, this->shape.getPosition().y);
            this->currentDirection = chooseDirection();
        }

        // Top collision
        if (this->shape.getPosition().y - halfHeight <= 0.f)
        {
            this->shape.setPosition(this->shape.getPosition().x, halfHeight);
            this->currentDirection = chooseDirection();
        }

        // Bottom collision
        if (this->shape.getPosition().y + halfHeight >= target->getSize().y)
        {
            this->shape.setPosition(this->shape.getPosition().x, target->getSize().y - halfHeight);
            this->currentDirection = chooseDirection();
        }
    }

    bool Human::isInfected()
    {
        return this->infected;
    }

    void Human::infect()
    {
        this->infected = true;
        this->shape.setFillColor(sf::Color::Red);
    }

    sf::Vector2f Human::chooseDirection()
    {
        float x = this->startPosition.x;
        float y = this->startPosition.y;

        float directive_x = Random::GenerateFloat(x - this->borderRadius, x + this->borderRadius);
        float directive_y = Random::GenerateFloat(y - this->borderRadius, y + this->borderRadius);

        return sf::Vector2f(directive_x, directive_y);
    }

    void Human::update(const sf::RenderTarget* target)
    {
        //movement phase

        sf::Vector2f directionVector = this->currentDirection - this->currentPosition;

        float module_vector_direciton = std::sqrt(pow(directionVector.x,2) + pow(directionVector.y,2));

        sf::Vector2f normalizedDirection = directionVector / module_vector_direciton;

        sf::Vector2f newPosition = this->currentPosition + normalizedDirection * this->movementSpeed;

        float distanceToDirection = std::sqrt((this->currentDirection.x - newPosition.x) * (this->currentDirection.x - newPosition.x) +
            (this->currentDirection.y - newPosition.y) * (this->currentDirection.y - newPosition.y));

        if (distanceToDirection <= this->movementSpeed)
        {
            this->currentPosition = this->currentDirection;
            this->shape.setPosition(this->currentPosition);

            this->currentDirection = chooseDirection();
        }
        else
        {
            this->currentPosition = newPosition;
            this->shape.setPosition(this->currentPosition);
        }

        //check collisions
        this->updateWindowBoundsCollision(target);
    }

    void Human::render(sf::RenderTarget* target)
    {
	    target->draw(this->shape);

    }
