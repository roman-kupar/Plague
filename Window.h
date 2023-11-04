#pragma once

#include <vector>
#include "Random.h"
#include "Human.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Window
{
private:
    sf::VideoMode videoMode;
    sf::RenderWindow window;
    sf::Event sfmlEvent;

    sf::Font font;
    sf::Text uiText;


    unsigned int maxHumans;
    unsigned int illPeople;
    unsigned int deadPeople;
    unsigned int recoveredPeople;

    std::vector<Human> humans;

    sf::Clock deltaTimeClock;
    sf::Clock clock;
    int seconds;

    void initVariables();
    void initWindow();
    void initFonts();
    void initText();
    void initModifiers();
public:
    Window();
    ~Window();

    //game mechanics
    void patientZero();
    void die();

    const bool running() const;
    void pollEvents();

    void update();
    void updateText();

    void renderText(sf::RenderTarget& target);
    void render();
};
