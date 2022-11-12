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
}

Game::~Game() {
	delete tower_sprite_sheet;
	delete enemy_sprite_sheet;
	delete environment_sprite_sheet;
}
