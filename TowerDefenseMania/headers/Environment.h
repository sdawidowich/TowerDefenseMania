#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "Tile.h"

class Environment {
private:
	sf::Texture* sprite_sheet;
	std::map<int, sf::IntRect*>* environment_sprites_indices;
	std::vector< std::vector<int> > id_map;
	int num_tiles;
	Tile** tiles;

	std::vector<sf::Vector2f> path;
public:
	Environment(sf::Texture* sprite_sheet, std::map<int, sf::IntRect*>* environment_sprites_indices);
	~Environment();

	int get_num_tiles();
	sf::Vector2i get_dimensions();
	Tile** get_tiles();
	std::vector<sf::Vector2f> get_path();

	void draw(sf::RenderWindow& window);
};