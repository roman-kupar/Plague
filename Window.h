#pragma once

#include<iostream>
#include<ctime>
#include<vector>
#include"Random.h"
#include"Human.h"

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Window
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endWindow;
	sf::Event sfmlEvent;

	//variables
	int maxHumans;
	float spawnTimerMax;
	float spawnTimer;

	std::vector<Human> humans;
	//Human human;
	
	void initVariables();
	void initWindow();
public:
	//Constructors and destructors
	Window();
	~Window();

	//Accessors

	//Functions
	void patientZero();
	const bool running() const;
	void pollEvents();

	void update();
	void render();
};

