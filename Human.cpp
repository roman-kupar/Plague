    #define _USE_MATH_DEFINES

    #include<iostream>
    #include<vector>
    #include "Human.h"
    #include "Random.h"
    #include<cmath>
    #include "WindowParamets.h"


    void Human::initVariables()
    {
	    this->borderRadius = 50.f;
	    this->startPosition = sf::Vector2f(Random::GenerateFloat(0.f, static_cast<float>(WindowParametrs::getVideoWidth())), Random::GenerateFloat(0.f, static_cast<float>(WindowParametrs::getVideoHeight())));
	    this->currentPosition = this->startPosition;
	    this->movementSpeed = 4.f;
	    this->currentDirection = chooseDirection();

        this->infectionRadius = 12.f;
    }
    void Human::initShape()
    {
	    this->shape.setRadius(4.f);
	    this->shape.setFillColor(sf::Color::Black);
        this->shape.setOrigin(2.f, 2.f);
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

      /*  this->distanse = static_cast<float>(sqrt(pow(directive_x - this->currentPosition.x, 2) + pow(directive_y - this->currentPosition.y, 2)));

        float module_vector_position = sqrt(pow(this->currentPosition.x,2) + pow(this->currentPosition.y,2));
        float module_vector_directive = sqrt(pow(directive_x, 2) + pow(directive_y, 2));

        float scalar_product = this->currentPosition.x * directive_x + this->currentPosition.y * directive_y;

        float cos_angle = scalar_product / (module_vector_position * module_vector_directive);
        float angle_rad = std::acos(cos_angle);
        float angle = angle_rad * (180 / M_PI);

        this->shape.setRotation(angle);*/


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

        //infection phase

    }

    void Human::render(sf::RenderTarget* target)
    {
	    target->draw(this->shape);

    }
