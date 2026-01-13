#include "spritesheet.h"

Spritesheet::Spritesheet(const std::string& file, int file_width, int tile_size)
    : SIZE(file_width), TILE_SIZE(tile_size)
{
    if (!spritesheet.loadFromFile(file))
    {
        std::cout << "Failed to load " << file << std::endl;
        return;
    }
    spritesheet.setSmooth(false);

    int tiles_per_row = SIZE / TILE_SIZE;

    int index = 0;
    for (int y = 0; y < SIZE; y += TILE_SIZE)
    {
        for (int x = 0; x < SIZE; x += TILE_SIZE)
        {
            sf::Sprite sprite(spritesheet, sf::IntRect(x, y, TILE_SIZE, TILE_SIZE));
            sprites.push_back(sprite);

            index++;
        }
    }
}

void Spritesheet::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < 8 * 8; i++)
    {
        sf::Sprite sprite = get_sprite(i);
        sprite.setPosition(i * 64, 100);
        sprite.setScale(4, 4);
        window.draw(sprite);
    }
}

sf::Sprite Spritesheet::get_sprite(int id)
{
    return sprites[id];
}

sf::Sprite Spritesheet::get_sprite(int id, int x_offset)
{
    sf::Sprite sprite = sprites[id];
    sf::IntRect rect = sprite.getTextureRect();
    rect.left += x_offset;
    sprite.setTextureRect(rect);
    return sprite;
}