#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
	int width = 1280;
	int height = 720;
	sf::RenderWindow window(sf::VideoMode(width, height), "Tower Defense");
	window.setFramerateLimit(60);

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

		window.display();
	}


	return 0;
}