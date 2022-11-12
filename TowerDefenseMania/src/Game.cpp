#include "Game.h"

#include <iostream>
#include <string>

Game::Game() {
	const std::string SPRITES_PATH = "assets/sprites/";

	this->tower_sprite_sheet = new sf::Texture();
	this->enemy_sprite_sheet = new sf::Texture();
	this->environment_sprite_sheet = new sf::Texture();

	this->tower_sprite_sheet->loadFromFile(SPRITES_PATH + "TowerSpriteSheet.png");
	this->enemy_sprite_sheet->loadFromFile(SPRITES_PATH + "EnemySpriteSheet.png");
	this->environment_sprite_sheet->loadFromFile(SPRITES_PATH + "EnvironmentSpriteSheet.png");

	this->environment = new Environment(this->environment_sprite_sheet);
}

Game::~Game() {
	delete this->tower_sprite_sheet;
	delete this->enemy_sprite_sheet;
	delete this->environment_sprite_sheet;

	delete this->environment;
}

void Game::draw_environment(sf::RenderWindow& window) {
	this->environment->draw(window);
}
