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


    int maxHumans;
    unsigned int illPeople;

    std::vector<Human> humans;


    void initVariables();
    void initWindow();
    void initFonts();
    void initText();

public:
    Window();
    ~Window();

    void patientZero();
    const bool running() const;
    void pollEvents();

    void update();
    void updateText();

    void renderText(sf::RenderTarget& target);
    void render();
};
