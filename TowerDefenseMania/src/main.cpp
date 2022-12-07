#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"

int main() {
	int width = 1280;
	int height = 720;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(width, height), "Tower Defense Mania", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	Game game;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}

			if (game.get_game_over() == Game_State::START) {

			}
			else if (game.get_game_over() == Game_State::PLAYING) {
				game.check_events(window, event);
			}
			else if (game.get_game_over() == Game_State::GAME_OVER) {
				if (event.type == sf::Event::KeyPressed) {
					window.close();
				}
			}
		}

		//render
		if (game.get_game_over() == Game_State::START) {
			window.clear();

			game.draw_start_screen(window);

			window.display();
		}
		else if (game.get_game_over() == Game_State::PLAYING) {
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
		else if (game.get_game_over() == Game_State::GAME_OVER) {
			window.clear();
			
			game.draw_game_over(window);

			window.display();
		}
	}

	return 0;
}