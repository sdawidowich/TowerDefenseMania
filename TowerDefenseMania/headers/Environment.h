#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "Tile.h"

class Environment {
private:
	sf::Texture* sprite_sheet;
	std::map<int, sf::IntRect*> tile_index;
	std::vector< std::vector<int> > tile_map;
	std::vector<Tile> tiles;
public:
	Environment(sf::Texture* sprite_sheet);
	~Environment();

	void draw(sf::RenderWindow& window);
};