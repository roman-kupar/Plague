#include "Window.h"
#include<iostream>
#include<sstream>
void Window::initVariables()
{
    maxHumans = 350;
    humans.reserve(maxHumans); // Reserve space for humans
    for (int i = 0; i < maxHumans; i++)
    {
        humans.emplace_back(Human());
    }
    patientZero();
    illPeople = 1;
}

void Window::initWindow()
{
    videoMode = sf::VideoMode::getDesktopMode();
    window.create(videoMode, "Plague simulator", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
}

void Window::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";
    }
}

void Window::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::Black);
    this->uiText.setString("NONE");
}

Window::Window()
{
    initWindow();
    initVariables();
    initFonts();
    initText();
}

Window::~Window()
{
    // Destructor will automatically clean up the window
}

const bool Window::running() const
{
    return window.isOpen();
}

void Window::patientZero()
{
    int random_human = Random::GenerateInt(0, maxHumans);
    humans[random_human].infect();
}

void Window::pollEvents()
{
    while (window.pollEvent(sfmlEvent))
    {
        switch (sfmlEvent.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (sfmlEvent.key.code == sf::Keyboard::Escape)
                window.close();
            break;
        }
    }
}

void Window::update()
{
    pollEvents();

    for (auto& human : humans)
    {
        human.update(&window);
    }

    for (int i = 0; i < maxHumans; i++)
    {
        if (humans[i].isInfected())
        {
            for (int j = 0; j < maxHumans; j++)
            {
                if (!humans[j].isInfected() && i != j)
                {
                    sf::FloatRect boundsI = humans[i].shape.getGlobalBounds();
                    sf::FloatRect boundsJ = humans[j].shape.getGlobalBounds();

                    if (boundsI.intersects(boundsJ))
                    {
                        humans[j].infect();
                        this->illPeople += 1;
                    }
                }
            }
        }
    }

    updateText();
}

void Window::updateText()
{
    std::stringstream ss;

    ss << "Sick people: " << this->illPeople;

    this->uiText.setString(ss.str());
}

void Window::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}

void Window::render()
{
    window.clear(sf::Color::White);

    for (auto& human : humans)
    {
        human.render(&window);
    }

    this->renderText(this->window);

    window.display();
}
