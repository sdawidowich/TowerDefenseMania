#include "Environment.h"

#include <iostream>

Environment::Environment(sf::Texture* sprite_sheet, std::map<int, sf::IntRect*>* environment_sprites_indices) {
	this->sprite_sheet = sprite_sheet;
	this->environment_sprites_indices = environment_sprites_indices;

	this->id_map = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{4, 4, 4, 0, 0, 0, 0, 0, 0, 4, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 4, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 4, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 4, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 4, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 4, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 4, 4, 4, 4, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

	this->num_tiles = (int)this->id_map.size() * (int)this->id_map[0].size();
	this->tiles = new Tile * [this->num_tiles];

	for (int i = 0; i < this->id_map.size(); i++) {
		for (int j = 0; j < this->id_map[i].size(); j++) {
			sf::Vector2f position(j * 32.f + 16.f, i * 32.f + 16.f);
			int index = (i * (int)this->id_map[i].size()) + j;
			tiles[index] = new Tile(this->sprite_sheet, (*this->environment_sprites_indices)[this->id_map[i][j]], position);
		}
	}
	
	int i = 11;
	int j = 0;
	int p_i = i;
	int p_j = j;
	int index = (i * (int)this->id_map[i].size()) + j;
	this->path.push_back(index);
	while (true) {
 		int up = (i - 1 < 0) ? 0 : i - 1;
		int down = (i + 1 >= this->id_map.size()) ? this->id_map.size() - 1 : i + 1;
		int left = (j - 1 < 0) ? 0 : j - 1;
		int right = (j + 1 >= this->id_map[i].size()) ? this->id_map[i].size() - 1: j + 1;

		if (up != i && up != p_i && this->id_map[up][j] == 4) {
			p_i = i;
			p_j = j;
			i--;
			index = (i * (int)this->id_map[i].size()) + j;
			this->path.push_back(index);
		}
		else if (down != i && down != p_i && this->id_map[down][j] == 4) {
			p_i = i;
			p_j = j;
			i++;
			index = (i * (int)this->id_map[i].size()) + j;
			this->path.push_back(index);
		}
		else if (left != j && left != p_j && this->id_map[i][left] == 4) {
			p_i = i;
			p_j = j;
			j--;
			index = (i * (int)this->id_map[i].size()) + j;
			this->path.push_back(index);
		}
		else if (right != j && right != p_j && this->id_map[i][right] == 4) {
			p_i = i;
			p_j = j;
			j++;
			index = (i * (int)this->id_map[i].size()) + j;
			this->path.push_back(index);
		}

		if (j >= this->id_map[i].size() - 1) {
			break;
		}
	}
}

Environment::~Environment() {
	delete[] this->tiles;
}

int Environment::get_num_tiles() {
	return this->num_tiles;
}

sf::Vector2i Environment::get_dimensions() {
	return sf::Vector2i((int)this->id_map[0].size(), (int)this->id_map.size());
}

Tile** Environment::get_tiles() {
	return this->tiles;
}

std::vector<int> Environment::get_path() {
	return this->path;
}

void Environment::draw(sf::RenderWindow& window) {
	for (int i = 0; i < this->num_tiles; i++) {
		this->tiles[i]->draw(window);
	}
}
