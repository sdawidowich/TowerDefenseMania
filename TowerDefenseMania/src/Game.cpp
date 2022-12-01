#include "Game.h"

#include <iostream>
#include <string>

Game::Game() {
	this->gen = std::mt19937(this->rd());
	this->distr = std::uniform_real_distribution<double>(0.2, 1);

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
	this->max_health = 100;
	this->health = 100;

	this->timer.restart();
	this->generate_delay = sf::Time(sf::seconds((float)this->distr(this->gen)));
	this->num_generated_enemies = 0;
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

void Game::check_events(sf::RenderWindow& window, sf::Event& event) {
	this->event_handler.check_events(window, event, this->gui, this->environment, this->towers);
}

void Game::towers_attack() {
	for (int i = 0; i < this->towers.size(); i++) {
		this->towers[i]->attack(this->enemies, this->gold);
	}
	this->check_enemies();
}

void Game::check_enemies() {
	for (int i = 0; i < this->enemies.size(); i++) {
		if (enemies[i].get_health() <= 0) {
			enemies.erase(enemies.begin() + i);
			i--;
		}
	}
}

void Game::generate_enemies() {
	int lvl_num_enemies = this->level * 3;
	if (this->num_generated_enemies < lvl_num_enemies) {
		if (this->timer.getElapsedTime() >= this->generate_delay) {
			timer.restart();
			this->generate_delay = sf::Time(sf::seconds((float)this->distr(this->gen)));
			this->enemies.push_back(Zombie(this->enemy_sprite_sheet, this->enemy_sprites_indices[0], sf::Vector2f(0.f, 200.f), sf::Vector2i(1, 0)));
			this->num_generated_enemies++;
		}
	}
}

void Game::move_enemies() {
	for (int i = 0; i < this->enemies.size(); i++) {
		enemies[i].move();
	}
}

void Game::advance_lvl() {
	int lvl_num_enemies = this->level * 3;
	if (!this->enemies.size() && this->num_generated_enemies >= lvl_num_enemies) {
		this->level++;
	}
}

void Game::draw_environment(sf::RenderWindow& window) {
	this->environment->draw(window);
}

void Game::draw_gui(sf::RenderWindow& window) {
	this->gui->draw_background(window);
	this->gui->draw_buttons(window);
	this->gui->draw_tower_range_indicator(window);
	this->gui->draw_text(window, this->level, this->gold, this->health, this->max_health);
	this->gui->draw_icons(window);
	this->gui->draw_selection(window);
	this->gui->draw_button_hover_label(window);
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
