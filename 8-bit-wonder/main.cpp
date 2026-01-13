#include <iostream>
#include <SFML/Graphics.hpp>

#include "text.h"
#include "utils.h"
#include "tilemap.h"

sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

const int  SCREEN_WIDTH = desktop.width;
const int  SCREEN_HEIGHT = desktop.height;

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "8-bit", sf::Style::Fullscreen);

	sf::Font font;
	font.loadFromFile("assets/fonts/font.ttf");
	Spritesheet spritesheet("assets/sprites/spritesheet.png");

	Text text_FPS(font, 24);
	text_FPS.set_position(5, 0);
	Text text_CPU(font, 24);
	text_CPU.set_position(5, 32);
	Text text_RAM(font, 24);
	text_RAM.set_position(5, 32 * 2);

	sf::RectangleShape rect_data(sf::Vector2f(200, 32));

	sf::Clock time;
	float delta_time = 0;
	float data_update_time = 0;
	int FPS = 0;

	TileMap tilemap(window, spritesheet);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
			if (event.type == event.MouseWheelScrolled)
			{
				int delta = event.mouseWheelScroll.delta;
				if (delta > 0) delta = 1;
				else if (delta < 0) delta = -1;

				tilemap.scroll(delta);
			}
		}

		FPS++;
		delta_time = time.getElapsedTime().asSeconds();
		time.restart();
		data_update_time += delta_time;

		if (data_update_time > 1)
		{
			data_update_time = 0;

			text_FPS.set_string("FPS: " + to_string(FPS));
			FPS = 0;

			text_CPU.set_string("CPU: " + to_string((int)get_CPU()) + "%");

			text_RAM.set_string("RAM: " + to_string((int)get_RAM()) + "MB");
		}

		window.clear(sf::Color::Black);


		rect_data.setPosition(sf::Vector2f(0, 0));
		rect_data.setFillColor(sf::Color(211, 147, 245, 200));
		window.draw(rect_data);
		text_FPS.draw_shadowed(window);

		rect_data.setPosition(sf::Vector2f(0, 32));
		rect_data.setFillColor(sf::Color(165, 207, 161, 200));
		window.draw(rect_data);
		text_CPU.draw_shadowed(window);

		rect_data.setPosition(sf::Vector2f(0, 32 * 2));
		rect_data.setFillColor(sf::Color(219, 170, 132, 200));
		window.draw(rect_data);
		text_RAM.draw_shadowed(window);


		tilemap.draw();
		tilemap.update();


		window.display();

	}
	return 0;
}