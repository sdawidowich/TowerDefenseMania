#include "Menu.h"

Menu::Menu() {

}

void Menu::add_button(Button btn) {
	this->buttons.push_back(btn);
}

void Menu::add_text(sf::Text text) {
	this->text.push_back(text);
}

void Menu::add_sprite(Sprite sprite) {
	this->sprites.push_back(sprite);
}

std::vector<Button>* Menu::get_buttons() {
	return &this->buttons;
}

void Menu::draw(sf::RenderWindow& window) {
	for (Button btn : this->buttons) {
		btn.draw(window);
	}

	for (sf::Text text : this->text) {
		window.draw(text);
	}

	for (Sprite sprite : this->sprites) {
		sprite.draw(window);
	}
}
