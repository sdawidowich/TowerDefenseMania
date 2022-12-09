#include "Game.h"

#include <iostream>
#include <string>
#include <cmath>

Game::Game(std::string name, std::vector<GameStats>* stats_list) {
	this->stats = GameStats(name);
	this->stats_list = stats_list;
	this->timer.restart();

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

	this->start_screen = new StartScreen(this->font, this->gui_sprite_sheet, &this->gui_sprites_indices, &this->game_state);
	this->stat_screen = new StatScreen(this->font, this->gui_sprite_sheet, &this->gui_sprites_indices, &this->game_state);
	this->environment = new Environment(this->environment_sprite_sheet, &this->environment_sprites_indices);
	this->gui = new GUI(this->font, this->gui_sprite_sheet, &this->gui_sprites_indices, this->tower_sprite_sheet, &this->tower_sprites_indices);

	this->level = 1;
	this->gold = 100;
	this->max_health = 100;
	this->health = 100;

	this->generate_timer.restart();
	this->generate_delay = sf::Time(sf::seconds((float)this->distr(this->gen)));
	this->num_generated_enemies = 0;

	this->game_state = Game_State::START;
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

	delete this->start_screen;
	delete this->stat_screen;
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

GameStats Game::get_stats() {
	return this->stats;
}

Game_State Game::get_state() {
	return this->game_state;
}

void Game::update_stats() {
	this->stats.set_time((double)this->timer.getElapsedTime().asSeconds());
	this->stats.set_towers((int)this->towers.size());
}

void Game::check_events(sf::RenderWindow& window, sf::Event& event) {
	this->event_handler.check_events(window, event, this->game_state, this->start_screen, this->stat_screen, this->gui, this->environment, this->towers, this->gold);
}

void Game::check_error_timer() {
	if (!this->gui->get_error_text().getString().isEmpty()) {
		if (this->gui->get_error_timer().getElapsedTime() >= this->gui->get_error_lifespan()) {
			this->gui->reset_error_text();
		}
	}
}

void Game::check_game_end() {
	if (this->health <= 0) {
		this->health = 0;
		this->game_state = Game_State::GAME_OVER;

		this->update_stats();
	}
}

void Game::towers_attack() {
	for (int i = 0; i < this->towers.size(); i++) {
		this->towers[i]->attack(this->enemies, this->gold, this->stats);
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
	std::vector<int> path = this->environment->get_path();
	Tile* start_tile = this->environment->get_tiles()[path[0]];

	int lvl_num_enemies = (int)std::round(this->level * 1.5 + 3);
	if (this->num_generated_enemies < lvl_num_enemies) {
		if (this->generate_timer.getElapsedTime() >= this->generate_delay) {
			generate_timer.restart();
			this->generate_delay = sf::Time(sf::seconds((float)this->distr(this->gen)));
			this->enemies.push_back(Zombie(this->enemy_sprite_sheet, this->enemy_sprites_indices[0], sf::Vector2f(0.f, start_tile->get_position().y), this->gui_sprite_sheet, this->gui_sprites_indices[13], sf::Vector2i(1, 0)));
			this->num_generated_enemies++;
		}
	}
}

void Game::move_enemies() {
	std::vector<int> path = this->environment->get_path();
	for (int i = 0; i < this->enemies.size(); i++) {
		int index = enemies[i].get_path_index();
		Tile* tile = this->environment->get_tiles()[path[index]];

		sf::Vector2f dis = sf::Vector2f(tile->get_position().x - this->enemies[i].get_position().x, tile->get_position().y - this->enemies[i].get_position().y);
		if (dis.x == 0 && dis.y == 0) {
			this->enemies[i].set_path_index(index + 1);

			index = enemies[i].get_path_index();
			if (index >= path.size()) {
				this->health -= this->enemies[i].get_damage();
				this->enemies.erase(this->enemies.begin() + i);
				i--;
				break;
			}
			tile = this->environment->get_tiles()[path[index]];
			dis = sf::Vector2f(tile->get_position().x - this->enemies[i].get_position().x, tile->get_position().y - this->enemies[i].get_position().y);
			double total_dis = std::sqrt(std::pow(dis.x, 2) + std::pow(dis.y, 2));
			this->enemies[i].change_dir(sf::Vector2i((int)(dis.x / total_dis), (int)(dis.y / total_dis)));
		}
		
		enemies[i].move();
		enemies[i].update_health_bar();
	}
}

void Game::advance_lvl() {
	int lvl_num_enemies = (int)std::round(this->level * 1.5 + 3);
	if (!this->enemies.size() && this->num_generated_enemies >= lvl_num_enemies) {
		this->num_generated_enemies = 0;
		this->level++;
		this->stats.set_level(this->stats.get_level() + 1);
	}
}

void Game::draw_start_screen(sf::RenderWindow& window) {
	this->start_screen->draw_buttons(window);
}

void Game::draw_stat_screen(sf::RenderWindow& window) {
	this->stat_screen->draw_buttons(window);
	this->stat_screen->draw_stats(window, this->stats_list);
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
	this->gui->draw_button_label(window);
	this->gui->draw_error_text(window);
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

void Game::draw_game_over(sf::RenderWindow& window) {
	sf::Text game_over_text;
	game_over_text.setFont(*this->font);
	game_over_text.setString("Game Over!");
	game_over_text.setCharacterSize(48);
	game_over_text.setPosition(sf::Vector2f(640.f, 360.f));
	game_over_text.setFillColor(sf::Color(186, 11, 11, 255));
	sf::FloatRect bounds = game_over_text.getGlobalBounds();
	game_over_text.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));

	sf::Text quit_text;
	quit_text.setFont(*this->font);
	quit_text.setString("Press any key to continue...");
	quit_text.setCharacterSize(24);
	quit_text.setPosition(sf::Vector2f(640.f, 400.f));
	quit_text.setFillColor(sf::Color::White);
	bounds = quit_text.getGlobalBounds();
	quit_text.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));

	float y = 600.f;

	sf::Text name_text;
	name_text.setFont(*this->font);
	name_text.setString(this->stats.get_name());
	name_text.setCharacterSize(24);
	name_text.setPosition(sf::Vector2f(640.f, 500.f));
	bounds = name_text.getGlobalBounds();
	name_text.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));

	sf::Text time_text;
	time_text.setFont(*this->font);
	time_text.setString(std::to_string(this->stats.get_time()));
	time_text.setCharacterSize(18);
	time_text.setPosition(sf::Vector2f(250.f, y - 15.f));

	sf::Text level_text;
	level_text.setFont(*this->font);
	level_text.setString("Level " + std::to_string(this->stats.get_level()));
	level_text.setCharacterSize(18);
	level_text.setPosition(sf::Vector2f(420.f, y - 15.f));

	sf::Text kills_text;
	kills_text.setFont(*this->font);
	kills_text.setString(std::to_string(this->stats.get_kills()));
	kills_text.setCharacterSize(18);
	kills_text.setPosition(sf::Vector2f(580.f, y - 15.f));

	sf::Text gold_text;
	gold_text.setFont(*this->font);
	gold_text.setString(std::to_string(this->stats.get_gold()));
	gold_text.setCharacterSize(18);
	gold_text.setPosition(sf::Vector2f(710.f, y - 15.f));

	sf::Text damage_text;
	damage_text.setFont(*this->font);
	damage_text.setString(std::to_string(this->stats.get_damage()));
	damage_text.setCharacterSize(18);
	damage_text.setPosition(sf::Vector2f(840.f, y - 15.f));

	sf::Text towers_text;
	towers_text.setFont(*this->font);
	towers_text.setString(std::to_string(this->stats.get_towers()));
	towers_text.setCharacterSize(18);
	towers_text.setPosition(sf::Vector2f(940.f, y - 15.f));

	Sprite clock_icon(this->gui_sprite_sheet, this->gui_sprites_indices[9], sf::Vector2f(220.f, y));
	Sprite skull_icon(this->gui_sprite_sheet, this->gui_sprites_indices[10], sf::Vector2f(550.f, y));
	Sprite gold_icon(this->gui_sprite_sheet, this->gui_sprites_indices[6], sf::Vector2f(680.f, y));
	Sprite sword_icon(this->gui_sprite_sheet, this->gui_sprites_indices[11], sf::Vector2f(810.f, y));
	Sprite tower_icon(this->gui_sprite_sheet, this->gui_sprites_indices[12], sf::Vector2f(910.f, y));

	window.draw(game_over_text);
	window.draw(quit_text);
	window.draw(name_text);
	window.draw(time_text);
	window.draw(level_text);
	window.draw(kills_text);
	window.draw(gold_text);
	window.draw(damage_text);
	window.draw(towers_text);

	clock_icon.draw(window);
	skull_icon.draw(window);
	gold_icon.draw(window);
	sword_icon.draw(window);
	tower_icon.draw(window);
}
