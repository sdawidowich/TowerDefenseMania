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

	this->environment = new Environment(this->environment_sprite_sheet);
	this->gui = new GUI(this->gui_sprite_sheet, this->tower_sprite_sheet);

	this->level = 1;
}

Game::~Game() {
	delete this->tower_sprite_sheet;
	delete this->enemy_sprite_sheet;
	delete this->environment_sprite_sheet;
	delete this->gui_sprite_sheet;

	delete this->environment;
}

void Game::update_gui(sf::RenderWindow& window, sf::Event& event) {
	this->gui->update_selection(window, event);
	this->gui->move_selection();
}

void Game::draw_environment(sf::RenderWindow& window) {
	this->environment->draw(window);
}

void Game::draw_gui(sf::RenderWindow& window) {
	this->gui->draw_buttons(window);
	this->gui->draw_selection(window);
}

void Game::draw_towers(sf::RenderWindow& window) {
}

void Game::draw_enemies(sf::RenderWindow& window) {
}
