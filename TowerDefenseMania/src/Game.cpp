#include "Game.h"

#include <iostream>
#include <string>

Game::Game() {
	const std::string SPRITES_PATH = "assets/sprites/";

	this->tower_sprite_sheet = new sf::Texture();
	this->enemy_sprite_sheet = new sf::Texture();
	this->environment_sprite_sheet = new sf::Texture();
	this->gui_sprite_sheet = new sf::Texture();

	this->tower_sprite_sheet->loadFromFile(SPRITES_PATH + "TowerSpriteSheet.png");
	this->enemy_sprite_sheet->loadFromFile(SPRITES_PATH + "EnemySpriteSheet.png");
	this->environment_sprite_sheet->loadFromFile(SPRITES_PATH + "EnvironmentSpriteSheet.png");
	this->gui_sprite_sheet->loadFromFile(SPRITES_PATH + "GUISpriteSheet.png");

	this->set_sprite_indices(this->tower_sprite_sheet, this->tower_sprites_indices);
	this->set_sprite_indices(this->enemy_sprite_sheet, this->enemy_sprites_indices);
	this->set_sprite_indices(this->environment_sprite_sheet, this->environment_sprites_indices);
	this->set_sprite_indices(this->gui_sprite_sheet, this->gui_sprites_indices);

	this->environment = new Environment(this->environment_sprite_sheet, &this->environment_sprites_indices);
	this->gui = new GUI(this->gui_sprite_sheet, &this->gui_sprites_indices, this->tower_sprite_sheet, &this->tower_sprites_indices);

	this->level = 1;
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
	this->gui->move_selection(window);
}

void Game::draw_environment(sf::RenderWindow& window) {
	this->environment->draw(window);
}

void Game::draw_gui(sf::RenderWindow& window) {
	this->gui->draw_buttons(window);
	this->gui->draw_selection(window);
}

void Game::draw_towers(sf::RenderWindow& window) {
	for (int i = 0; i < this->towers.size(); i++) {
		this->towers[i].draw(window);
	}
}

void Game::draw_enemies(sf::RenderWindow& window) {
	for (int i = 0; i < this->enemies.size(); i++) {
		this->enemies[i].draw(window);
	}
}
