#ifndef LIGHT_H
#define LIGHT_H

#include "utils.h"

class Light
{
	public:
		Light(sf::Vector2f pos, float radius, sf::Color color = sf::Color::White);
		sf::Vector2f pos;
		float radius;
		sf::Color color;
};

#endif