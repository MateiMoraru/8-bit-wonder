#pragma once
#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

//TEXTURES
const int   NULL_TEX = -1, // Error texture
            BRICK = 0,
            STONE = 1;

const int   UI_SLOT = 0,
UI_SLOT_1 = 1,
UI_CRAFTING_SLOT = 2,
UI_CRAFTING_SLOT_1 = 3,
UI_HEART = 4,
UI_BAR = 5,
UI_ARROW = 6;

class Spritesheet
{
public:
    Spritesheet(const std::string& file, int file_width = 160, int tile_size = 16);

    void draw(sf::RenderWindow& window);

    sf::Sprite get_sprite(int id);
    sf::Sprite get_sprite(int id, int x_offset);
    int get_sprite_size() const { return TILE_SIZE; }

private:
    sf::Texture spritesheet;
    vector<sf::Sprite> sprites;

    int SIZE = 256;
    int TILE_SIZE = 16;
};

#endif