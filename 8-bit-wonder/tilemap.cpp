#include "tilemap.h"

TileMap::TileMap(sf::RenderWindow& window, Spritesheet& spritesheet)
	: window(window)
	, spritesheet(spritesheet)
	, temp_tile(spritesheet.get_sprite(0), 0)
{
	temp_tile.set_position(0, 128);
	scene.create(window.getSize().x, window.getSize().y);

	shader.loadFromFile("default.frag", sf::Shader::Fragment);
	shader.setUniform("resolution", sf::Vector2f(window.getSize().x, window.getSize().y));
	shader.setUniform("pixelSize", 1.f);
	shader.setUniform("lightPixelSize", 12.f);
	shader.setUniform("lightSteps", 12.f);

	lights.push_back(Light(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), TILE_SIZE * 5));
}

void TileMap::draw()
{
	camera.setSize(window.getSize().x, window.getSize().y);
	camera.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
	scene.setView(camera);
	scene.clear(sf::Color::Black);

	for (auto& tile_obj : tiles)
	{
		auto& tile = tile_obj.second;
		tile.draw(scene);
	}

	if (editing)
		temp_tile.draw(scene);

	scene.display();

	sf::Sprite scene_sprite(scene.getTexture());

	//lightshit

	sf::Glsl::Vec3 colors[16];
	sf::Glsl::Vec2 positions[16];
	float radii[16];

	int count = std::min((int)lights.size(), MAX_LIGHTS);

	for (int i = 0; i < count; i++)
	{
		auto& light = lights[i];
		sf::Glsl::Vec3 color = { light.color.r / 255.f, light.color.g / 255.f, light.color.b / 255.f };
		sf::Glsl::Vec2 pos = { light.pos.x, light.pos.y };
		float radius = light.radius;

		colors[i] = color;
		positions[i] = pos;
		radii[i] = radius;
	}

	shader.setUniform("numLights", count);
	shader.setUniformArray("lightPos", positions, count);
	shader.setUniformArray("lightRadius", radii, count);
	shader.setUniformArray("lightColor", colors, count);

	window.draw(scene_sprite, &shader);
}

void TileMap::update()
{
	if (editing)
	{
		edit();
	}
}

void TileMap::edit()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_pos_world = window.mapPixelToCoords(mouse_pos, camera);

		int x = static_cast<int>(mouse_pos_world.x / TILE_SIZE) * static_cast<int>(TILE_SIZE);
		int y = static_cast<int>(mouse_pos_world.y / TILE_SIZE) * static_cast<int>(TILE_SIZE);

		Tile newTile(spritesheet.get_sprite(selected_sprite), selected_sprite, sf::Vector2f(x, y), sf::Vector2f(TILE_SIZE, TILE_SIZE));

		tiles[sf::Vector2i(x, y)] = newTile;
	}
	
}

void TileMap::scroll(int delta)
{
	if (editing)
	{
		if (delta > 0 && selected_sprite < 100)
			selected_sprite++;
		else if (selected_sprite > 0)
			selected_sprite--;
		temp_tile.set_sprite(spritesheet.get_sprite(selected_sprite), selected_sprite, TILE_SIZE);
	}
}

void TileMap::save()
{
	std::ofstream file("assets/map.txt");
	if (!file.is_open())
	{
		std::cerr << "Failed to open save file" << std::endl;
		return;
	}

	for (auto& tile_obj : tiles)
	{
		const Tile& tile = tile_obj.second;
		int id = tile.get_id();
		float x = tile.get_x();
		float y = tile.get_y();

		file << id << " " << x << " " << y << "\n";
	}

	file.close();
	std::cout << "TileMap saved" << std::endl;
}

void TileMap::load()
{
	std::ifstream file("assets/map.txt");
	if (!file.is_open())
	{
		std::cerr << "Failed to open save file" << std::endl;
		return;
	}

	tiles.clear();

	int id;
	float x, y;
	while (file >> id >> x >> y)
	{
		sf::Sprite sprite(spritesheet.get_sprite(id));
		Tile tile(sprite, id, sf::Vector2f(x, y), sf::Vector2f(TILE_SIZE, TILE_SIZE));
		tiles[sf::Vector2i(static_cast<int>(x), static_cast<int>(y))] = tile;
	}

	file.close();
	std::cout << "TileMap loaded"<< std::endl;
}