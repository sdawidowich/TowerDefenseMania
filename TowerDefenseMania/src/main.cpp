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

			game.check_events(window, event);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
		}
		//render
		window.clear();

		game.towers_attack();

		game.move_enemies();
		game.generate_enemies();

		game.advance_lvl();

		game.draw_environment(window);
		game.draw_gui(window);
		game.draw_towers(window);
		game.draw_enemies(window);

		window.display();
	}

	return 0;
}