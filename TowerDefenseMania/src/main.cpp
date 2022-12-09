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

	const std::string path = "data/game_stats.csv";
	StatsFileIO io;
	std::vector<GameStats> stats_list = io.read_stats_from_file(path);

	int width = 1280;
	int height = 720;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(width, height), "Tower Defense Mania", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	Game game(name, &stats_list);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}

			if (game.get_state() == Game_State::START || game.get_state() == Game_State::STATS || game.get_state() == Game_State::PLAYING) {
				game.check_events(window, event);
			}
			else if (game.get_state() == Game_State::GAME_OVER) {
				if (event.type == sf::Event::KeyPressed) {
					window.close();
				}
			}
		}

		//render
		window.clear();

		if (game.get_state() == Game_State::START) {
			game.draw_start_screen(window);
		}
		else if (game.get_state() == Game_State::STATS) {
			game.draw_stat_screen(window);
		}
		else if (game.get_state() == Game_State::PLAYING) {
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
		}
		else if (game.get_state() == Game_State::GAME_OVER) {
			game.draw_game_over(window);
		}

		window.display();
	}
	
	if (game.get_state() == Game_State::GAME_OVER) {
		GameStats stats = game.get_stats();
		stats_list.push_back(stats);
		io.write_stats_to_file(path, stats_list);
	}

	return 0;
}