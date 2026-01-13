#include "tile.h"

Tile::Tile(sf::Sprite sprite, int sprite_id)
    : sprite(sprite), sprite_id(sprite_id), position(0.f, 0.f), size(32.f, 32.f)
{
    this->sprite.setPosition(position);
}

Tile::Tile(sf::Sprite sprite, int sprite_id, const sf::Vector2f& position, const sf::Vector2f& size)
    : sprite(sprite), sprite_id(sprite_id), position(position), size(size) // initializer list
{
    this->sprite.setPosition(position);

    sf::IntRect rect = sprite.getTextureRect();
    sf::Vector2u tex_size(rect.width, rect.height);

    this->sprite.setScale(
        size.x / tex_size.x,
        size.y / tex_size.y
    );
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states)
{
    target.draw(sprite, states);
}

bool Tile::collides(const Tile& other) const
{
    return position.x < other.position.x + other.size.x &&
        position.x + size.x > other.position.x &&
        position.y < other.position.y + other.size.y &&
        position.y + size.y > other.position.y;
}

void Tile::set_sprite_color(sf::Color color)
{
    sprite.setColor(color);
}

void Tile::set_scale(sf::Vector2f scale)
{
    sprite.setScale(scale.x, scale.y);
}

void Tile::set_sprite(sf::Sprite sprite, int id)
{
    this->sprite = sprite;
    this->sprite.setPosition(position);
    sprite_id = id;
}

void Tile::set_sprite(sf::Sprite sprite, int id, int size)
{
    this->sprite = sprite;
    this->sprite.setPosition(position);
    sprite_id = id;

    this->sprite.setScale(size / sprite.getTexture()->getSize().x, size / sprite.getTexture()->getSize().y);
}

void Tile::move(float x, float y)
{
    position.x += x;
    position.y += y;
    sprite.setPosition(position);
}