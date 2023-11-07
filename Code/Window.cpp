#include "Headers/Window.h"
#include <iostream>
#include <sstream>
#include <fstream>
//#include "Modifiers.h"

//void Window::initModifiers()
//{   
//    modifiers::modificators.Vacine = false;
//    modifiers::modificators.Airport = false;
//}

void Window::initVariables()
{
    maxHumans = 500;
    humans.reserve(maxHumans);
    for (int i = 0; i < maxHumans; i++)
    {
        humans.emplace_back(Human());
    }
    illPeople = 1;
    recoveredPeople = 0;
    deadPeople = 0;
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

    pText.setFont(font);
    pText.setCharacterSize(64);
    pText.setFillColor(sf::Color::Black);
    pText.setString("NONE");

}

Window::Window()
{
    initWindow();
    initVariables();
    initFonts();
    initText();
    //initModifiers();

    patientZero();
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
    for (int i = 0; i < 5;i++) 
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
            else if (sfmlEvent.key.code == sf::Keyboard::Space)
                if (isPaused())
                    this->paused = false;
                else
                {
                    pause();
                    updateText();
                }

            else if (sfmlEvent.key.code == sf::Keyboard::R)
                restart();
            break;
        }
    }
}

void Window::pause()
{
    this->paused = true;
}

bool Window::isPaused()
{
    return this->paused;
}
void Window::restart()
{
    this->restarted = true;
}
bool Window::isRestarted()
{
    return this->restarted;
}
void Window::update()
{
    sf::Time deltaTime = this->deltaTimeClock.restart();

    this->seconds = int(this->clock.getElapsedTime().asSeconds());

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

                    int chance_to_get_infected = Random::GenerateInt(0, 100);

                    if (boundsI.intersects(boundsJ) && chance_to_get_infected>60)
                    {
                        humans[j].infect();
                        this->illPeople += 1;
                    }
                }
            }
        }
    }

    //Recoverment
    /*for (int i = 0; i < humans.size(); i++)
    {
        if (humans[i].isInfected())
        {
            float chance_to_recover = Random::GenerateFloat(0, 10);

            if (chance_to_recover >= 9.99)
            {
                humans[i].recover();
                this->recoveredPeople += 1;
                this->illPeople -= 1;
            }
        }
    }*/

    updateText();

    die();

    pollEvents();
}

void Window::updateText()
{
    std::stringstream ss;
    std::stringstream pp;

    ss << "Sick people: " << this->illPeople << "\n" << "Dead people: " << this->deadPeople << "\n" << "Time: " << seconds /*<< "\n" << "Recovered: " << this->recoveredPeople*/;

    if (isPaused())
    {
        pp << "PAUSED";

        sf::FloatRect textRect = this->pText.getLocalBounds();

        this->pText.setOrigin(textRect.width / 2, textRect.height / 2);

        this->pText.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2.0f, sf::VideoMode::getDesktopMode().height / 2.0f));

        this->pText.setString(pp.str());
    }
        
    this->uiText.setString(ss.str());

}

void Window::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
    if (isPaused())
    {
        target.draw(this->pText);
    }

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
