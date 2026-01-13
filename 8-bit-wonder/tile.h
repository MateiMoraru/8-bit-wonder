#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
public:
    Tile() = default;
    Tile(sf::Sprite sprite, int sprite_id);
    Tile(sf::Sprite sprite, int sprite_id, const sf::Vector2f& position, const sf::Vector2f& size);

    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

    float get_x() const { return position.x; }
    float get_y() const { return position.y; }
    int get_id() const { return sprite_id; }
    sf::Sprite& get_sprite() { return sprite; }
    sf::FloatRect get_global_bounds() const { return sprite.getGlobalBounds(); }

    void set_position(float x, float y) { position = sf::Vector2f(x, y); sprite.setPosition(position); }
    void set_sprite(sf::Sprite sprite, int id);
    void set_sprite(sf::Sprite sprite, int id, int size);
    void set_sprite_color(sf::Color color);
    void set_scale(sf::Vector2f scale);

    void move(float x, float y);

    bool collides(const Tile& other) const;

private:
    sf::Sprite sprite;
    int sprite_id;
    sf::Vector2f position;
    sf::Vector2f size;
};

#endif