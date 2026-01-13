#include <iostream>
#include "text.h"
using namespace std;

Text::Text(const sf::Font& font, unsigned int size)
{

    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);
}

void Text::set_string(const std::string& str) { text.setString(str); this->str = str; }
void Text::set_position(float x, float y) { text.setPosition(x, y); }
void Text::set_color(sf::Color color) { text.setFillColor(color); }
void Text::set_size(unsigned int char_size) { text.setCharacterSize(char_size); }

void Text::draw(sf::RenderWindow& window) { window.draw(text); }
void Text::draw_shadowed(sf::RenderWindow& window, sf::Color shadowColor, float offsetX, float offsetY)
{
    sf::Text shadow = text;
    shadow.setFillColor(shadowColor);
    shadow.move(offsetX, offsetY);
    window.draw(shadow);
    window.draw(text);
}

sf::FloatRect Text::get_bounds() const { return text.getGlobalBounds(); }