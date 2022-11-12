#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"

int main() {
	int width = 1280;
	int height = 720;
	sf::RenderWindow window(sf::VideoMode(width, height), "Tower Defense Mania");
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
		}
		//render
		window.clear();

		game.draw_environment(window);

		window.display();
	}


	return 0;
}