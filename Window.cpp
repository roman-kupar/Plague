#include "Window.h"

void Window::initVariables()
{
	this->maxHumans = 350;
	for (int i = 0;i < this->maxHumans;i++)
	{
		this->humans.emplace_back(Human());
	}
	this->patientZero();
}
void Window::initWindow()
{
	this->videoMode = sf::VideoMode::getDesktopMode();
	this->window = new sf::RenderWindow(this->videoMode, "Plague simulator", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

Window::Window()
{
	this->initWindow();
	this->initVariables();
}

Window::~Window()
{
	delete this->window;
}

const bool Window::running() const
{
	return this->window->isOpen();
}

void Window::patientZero()
{
	int random_human = Random::GenerateInt(0, this->maxHumans);
	this->humans[random_human].infect();
}

void Window::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;

		}
	}
}

void Window::update()
{
	this->pollEvents();

	
	for (int i = 0; i < this->maxHumans; i++) {
		this->humans[i].update(this->window);

		for (int j = i + 1; j < this->maxHumans; j++) {
			if (this->humans[i].isInfected() && this->humans[i].shape.getGlobalBounds().intersects(this->humans[j].shape.getGlobalBounds())) {
				this->humans[j].infect();
			}
			else if (this->humans[j].isInfected() && this->humans[j].shape.getGlobalBounds().intersects(this->humans[i].shape.getGlobalBounds())) {
				this->humans[i].infect();
			}
		}
	}	
}

void Window::render()
{
	this->window->clear(sf::Color::White);

	for (int i = 0;i < this->maxHumans;i++)
	{
		this->humans[i].render(this->window);
	}
	//this->human.render(this->window);
	this->window->display();
}
