#pragma once
#include<SFML/Window.hpp>

namespace WindowParametrs {
	unsigned int getVideoHeight()
	{
		return sf::VideoMode::getDesktopMode().height;
	}

	unsigned int getVideoWidth()
	{
		return sf::VideoMode::getDesktopMode().width;
	}
}