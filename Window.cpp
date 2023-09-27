#include "Window.h"
#include <iostream>
#include <sstream>
#include "Modifiers.h"


void Window::initModifiers()
{
    modifiers::modificators.Vacine = false;
    modifiers::modificators.Airport = false;
}

void Window::initVariables()
{
    maxHumans = 500;
    humans.reserve(maxHumans);
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
    if (!font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";
    }
}

void Window::initText()
{
    uiText.setFont(font);
    uiText.setCharacterSize(24);
    uiText.setFillColor(sf::Color::Black);
    uiText.setString("NONE");
}

Window::Window()
{
    initWindow();
    initVariables();
    initFonts();
    initText();
    initModifiers();
}

Window::~Window()
{
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

void Window::die()
{
    for (auto it = humans.begin(); it != humans.end();++it)
    {
        if (it->movementSpeed <= 0.f)
        {
            this->humans.erase(it);
            this->deadPeople += 1;
            this->illPeople -= 1;
            break;
        }
    }
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
    sf::Time deltaTime = this->deltaTimeClock.restart();

    this->seconds = int(this->clock.getElapsedTime().asSeconds());

    pollEvents();

    for (auto& human : humans)
    {
        human.update(&window);
    }

    for (int i = 0; i < humans.size(); i++)
    {
        if (humans[i].isInfected())
        {
            for (int j = 0; j < humans.size(); j++)
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

    die();
}

void Window::updateText()
{
    std::stringstream ss;

    ss << "Sick people: " << this->illPeople << "\n" << "Dead people: " << this->deadPeople << "\n" << "Time: " << seconds;

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
