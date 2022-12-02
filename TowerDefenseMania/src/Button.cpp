#include "Button.h"

#include <iostream>

Button::Button(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, std::string label, std::function<void(sf::RenderWindow&, Button*)> on_idle, std::function<void(sf::RenderWindow&, Button*)> on_hover, std::function<void(sf::RenderWindow&, Button*)> on_click)
	: Sprite(texture, crop, position) {
	this->btn_state = Button_State::BTN_IDLE;
	this->selected = false;
	this->label = label;
	this->on_idle = on_idle;
	this->on_hover = on_hover;
	this->on_click = on_click;

	this->sprite.setScale(sf::Vector2f(2.f, 2.f));
}

void Button::update(sf::RenderWindow& window, sf::Event& event, sf::Vector2f mouse_pos) {
	this->btn_state = Button_State::BTN_IDLE;
	this->check_click(window, event, mouse_pos);

	if (!this->selected) {
		this->check_hover(window, mouse_pos);

		if (this->btn_state == Button_State::BTN_IDLE) {
			this->on_idle(window, this);
		}
	}
}

void Button::check_hover(sf::RenderWindow& window, sf::Vector2f mouse_pos) {
	if (this->get_sprite_bounds().contains(mouse_pos)) {
		this->btn_state = Button_State::BTN_HOVER;
		this->on_hover(window, this);
	}
}

void Button::check_click(sf::RenderWindow& window, sf::Event& event, sf::Vector2f mouse_pos) {
	if (event.type == sf::Event::MouseButtonReleased) {
		if (this->get_sprite_bounds().contains(mouse_pos)) {
			this->btn_state = Button_State::BTN_CLICKED;
			this->on_click(window, this);
		}
	}
}

void Button::set_crop(sf::IntRect* crop) {
	this->sprite.setTextureRect(*crop);
}

Button_State Button::get_state() {
	return this->btn_state;
}

std::string Button::get_label() {
	return this->label;
}

void Button::select() {
	this->selected = true;
}

void Button::deselect() {
	this->selected = false;
}

bool Button::is_selected() {
	return this->selected;
}