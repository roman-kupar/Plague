#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Human
{
private:
	sf::CircleShape dir;
	sf::Vector2f startPosition;
	sf::Vector2f currentPosition;
	sf::Vector2f currentDirection;
	float borderRadius;
	float borderSquare;
	float movementSpeed;

	//Polar coordinats;
	float distanse;

	//infect
	bool infected;
	float infectionRadius;

	void initVariables();
	void initShape();
public:
	sf::CircleShape shape;
	//Constructors and destructors
	Human();
	virtual ~Human();

	//Modifiers
	sf::Vector2f chooseDirection();
	bool isInfected();
	void infect();

	//Functions
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

