#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "GameStats.h"
#include "StatsFileIO.h"

int main() {
	// Get input
	std::cout << "Enter name: ";
	
	std::string name;
	std::getline(std::cin, name);

	int width = 1280;
	int height = 720;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(width, height), "Tower Defense Mania", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	Game game(name);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}

			if (game.get_state() == Game_State::START || game.get_state() == Game_State::PLAYING) {
				game.check_events(window, event);
			}
			else if (game.get_state() == Game_State::GAME_OVER) {
				if (event.type == sf::Event::KeyPressed) {
					window.close();
				}
			}
		}

		//render
		if (game.get_state() == Game_State::START) {
			window.clear();

			game.draw_start_screen(window);

			window.display();
		}
		else if (game.get_state() == Game_State::PLAYING) {
			window.clear();

			game.check_error_timer();

			game.towers_attack();
			game.move_enemies();
			game.generate_enemies();
			game.advance_lvl();

			game.draw_environment(window);
			game.draw_gui(window);
			game.draw_towers(window);
			game.draw_enemies(window);
			game.check_game_end();

			window.display();
		}
		else if (game.get_state() == Game_State::GAME_OVER) {
			window.clear();
			
			game.draw_game_over(window);
			game.update_stats();

			window.display();
		}
	}


	GameStats stats = game.get_stats();
	std::cout << "Name: " << stats.get_name() << std::endl;
	std::cout << "Time: " << stats.get_time() << std::endl;
	std::cout << "Level: " << stats.get_level() << std::endl;
	std::cout << "Kills: " << stats.get_kills() << std::endl;
	std::cout << "Gold: " << stats.get_gold() << std::endl;
	std::cout << "Damage: " << stats.get_damage() << std::endl;
	std::cout << "Towers: " << stats.get_towers() << std::endl;

	const std::string path = "data/game_stats.csv";
	StatsFileIO io;
	std::vector<GameStats> stats_list = io.read_stats_from_file(path);
	stats_list.push_back(stats);
	io.write_stats_to_file(path, stats_list);

	return 0;
}