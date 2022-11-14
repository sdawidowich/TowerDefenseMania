#include "Button.h"

Button::Button(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position) : Sprite(texture, crop, position) { 
	this->btn_state = BTN_IDLE;
}

void Button::update(sf::Event& event, sf::Vector2f mouse_pos) {
	this->btn_state = BTN_IDLE;
	this->check_hover(mouse_pos);
	this->check_click(event, mouse_pos);
}

void Button::check_hover(sf::Vector2f mouse_pos) {
	if (this->btn_state != BTN_PRESSED && this->get_sprite_bounds().contains(mouse_pos)) {
		this->btn_state = BTN_HOVER;
	}
}

void Button::check_click(sf::Event& event, sf::Vector2f mouse_pos) {
	if (event.type == sf::Event::MouseButtonReleased) {
		if (this->get_sprite_bounds().contains(mouse_pos)) {
			this->btn_state = BTN_PRESSED;
		}
	}
}

Button_State Button::get_state() {
	return this->btn_state;
}
