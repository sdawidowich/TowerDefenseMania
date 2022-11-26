#include "Game.h"

#include <iostream>
#include <string>

Game::Game() {
	const std::string FONT_PATH = "assets/fonts/";
	const std::string SPRITES_PATH = "assets/sprites/";
	
	this->font = new sf::Font();
	this->tower_sprite_sheet = new sf::Texture();
	this->enemy_sprite_sheet = new sf::Texture();
	this->environment_sprite_sheet = new sf::Texture();
	this->gui_sprite_sheet = new sf::Texture();

	this->font->loadFromFile(FONT_PATH + "upheavtt.ttf");
	this->tower_sprite_sheet->loadFromFile(SPRITES_PATH + "TowerSpriteSheet.png");
	this->enemy_sprite_sheet->loadFromFile(SPRITES_PATH + "EnemySpriteSheet.png");
	this->environment_sprite_sheet->loadFromFile(SPRITES_PATH + "EnvironmentSpriteSheet.png");
	this->gui_sprite_sheet->loadFromFile(SPRITES_PATH + "GUISpriteSheet.png");

	this->set_sprite_indices(this->tower_sprite_sheet, this->tower_sprites_indices);
	this->set_sprite_indices(this->enemy_sprite_sheet, this->enemy_sprites_indices);
	this->set_sprite_indices(this->environment_sprite_sheet, this->environment_sprites_indices);
	this->set_sprite_indices(this->gui_sprite_sheet, this->gui_sprites_indices);

	this->environment = new Environment(this->environment_sprite_sheet, &this->environment_sprites_indices);
	this->gui = new GUI(this->font, this->gui_sprite_sheet, &this->gui_sprites_indices, this->tower_sprite_sheet, &this->tower_sprites_indices);

	this->level = 1;
	this->gold = 100;
	this->max_health = 1000;
	this->health = 1000;
}

Game::~Game() {
	delete this->tower_sprite_sheet;
	delete this->enemy_sprite_sheet;
	delete this->environment_sprite_sheet;
	delete this->gui_sprite_sheet;

	this->delete_sprite_indices(this->tower_sprites_indices);
	this->delete_sprite_indices(this->enemy_sprites_indices);
	this->delete_sprite_indices(this->environment_sprites_indices);
	this->delete_sprite_indices(this->gui_sprites_indices);

	delete this->environment;
	delete this->gui;

}

void Game::set_sprite_indices(sf::Texture* sprite_sheet, std::map<int, sf::IntRect*>& sprites_indices) {
	int num_x = sprite_sheet->getSize().x / 32;
	int num_y = sprite_sheet->getSize().y / 32;
	for (int i = 0; i < num_y; i++) {
		for (int j = 0; j < num_x; j++) {
			int index = (i * num_x) + j;
			int x_coord = j * 32;
			int y_coord = i * 32;
			sprites_indices[index] = new sf::IntRect(x_coord, y_coord, 32, 32);
		}
	}
}

void Game::delete_sprite_indices(std::map<int, sf::IntRect*>& sprites_indices) {
	for (int i = 0; i < sprites_indices.size(); i++) {
		delete sprites_indices[i];
	}
	sprites_indices.clear();
}

void Game::update_gui(sf::RenderWindow& window, sf::Event& event) {
	this->gui->update_selection(window, event);
}

void Game::place_tower(sf::RenderWindow& window, sf::Event& event) {
	sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));

	int num_tiles = this->environment->get_num_tiles();
	sf::Vector2i env_dimensions = this->environment->get_dimensions();
	Tile** tiles = this->environment->get_tiles();
	Tower* new_tower = this->gui->get_new_tower();

	if (new_tower) {
		// Reset highlights then highlight selected tiles
		for (int i = 0; i < num_tiles; i++) {
			tiles[i]->set_highlight(false);
		}
		int x_quadrant = -1;
		int y_quadrant = -1;
		for (int i = 0; i < num_tiles; i++) {
			if (tiles[i]->get_sprite_bounds().contains(mouse_pos)) {
				tiles[i]->set_highlight(true);

				sf::Vector2f tile_pos = tiles[i]->get_position();
				if (mouse_pos.x > tile_pos.x) {
					x_quadrant = 1;
				}
				if (mouse_pos.y > tile_pos.y) {
					y_quadrant = 1;
				}

				if ((i % env_dimensions.x) >= (env_dimensions.x - 1)) {
					x_quadrant = -1;
				}
				else if ((i % env_dimensions.x) <= 0) {
					x_quadrant = 1;
				}
				if ((i / env_dimensions.x) >= (env_dimensions.y - 1)) {
					y_quadrant = -1;
				}
				else if ((i / env_dimensions.x) <= 0) {
					y_quadrant = 1;
				}

				tiles[i + x_quadrant]->set_highlight(true);
				tiles[i + y_quadrant * env_dimensions.x]->set_highlight(true);
				tiles[i + x_quadrant + y_quadrant * env_dimensions.x]->set_highlight(true);
				break;
			}
		}

		if (event.type == sf::Event::MouseButtonReleased) {
			this->towers.push_back(this->gui->get_new_tower());
		}
	}
	
}

void Game::draw_environment(sf::RenderWindow& window) {
	this->environment->draw(window);
}

void Game::draw_gui(sf::RenderWindow& window) {
	this->gui->draw_buttons(window);
	this->gui->draw_selection(window);
	this->gui->draw_text(window, this->level, this->gold, this->level);
}

void Game::draw_towers(sf::RenderWindow& window) {
	for (int i = 0; i < this->towers.size(); i++) {
		this->towers[i]->draw(window);
	}
}

void Game::draw_enemies(sf::RenderWindow& window) {
	for (int i = 0; i < this->enemies.size(); i++) {
		this->enemies[i].draw(window);
	}
}
