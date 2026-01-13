#include <iostream>
#include <fstream>
#include <unordered_map>

#include "utils.h"
#include "tile.h"
#include "spritesheet.h"
#include "light.h"

struct Vector2iHash
{
	std::size_t operator()(const sf::Vector2i& v) const
	{
		return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
	}
};

class TileMap
{
	public:
		TileMap(sf::RenderWindow& window, Spritesheet& spritesheet);

		void draw();
		void update();
		void save();

		void scroll(int delta);
	private:
		void load();
		void edit();

		sf::RenderWindow& window;
		Spritesheet& spritesheet;

		sf::RenderTexture scene;
		sf::Shader shader;
		sf::Shader shader_light;
		sf::View camera;

		const int TILE_SIZE = 96;
		const int MAX_LIGHTS = 16;

		std::unordered_map<sf::Vector2i, Tile, Vector2iHash> tiles;
		std::vector<Light> lights;
		Tile temp_tile;

		int selected_sprite = BRICK;
		bool editing = true;
};