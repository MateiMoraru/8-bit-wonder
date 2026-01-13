#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;

class Text
{

public:
    Text() {};
    Text(const sf::Font& font, unsigned int size);

    string get_string() const { return str; }

    void set_string(const string& str);
    void set_position(float x, float y);
    void set_color(sf::Color color);
    void set_size(unsigned int char_size);

    void draw(sf::RenderWindow& window);
    void draw_shadowed(sf::RenderWindow& window, sf::Color shadowColor = sf::Color(50, 50, 50, 150), float offsetX = 2.f, float offsetY = 2.f);


    sf::FloatRect get_bounds() const;

private:
    sf::Text text;
    sf::Font font;

    string str;
};