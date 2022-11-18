#include "Button.h"

#include <iostream>

Button::Button(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, std::string label, sf::IntRect* hover_crop, sf::IntRect* selected_crop) : Sprite(texture, crop, position) {
	this->btn_state = Button_State::BTN_IDLE;
	this->label = label;
	this->hover_crop = hover_crop;
	this->selected_crop = selected_crop;

	this->sprite.setScale(sf::Vector2f(2.f, 2.f));
}

void Button::update(sf::Event& event, sf::Vector2f mouse_pos) {
	if (this->btn_state != Button_State::BTN_SELECTED) {
		this->btn_state = Button_State::BTN_IDLE;
		this->check_hover(mouse_pos);
	}
	else {
		this->update_sprite(this->selected_crop);
	}

	this->check_click(event, mouse_pos);
	
}

void Button::check_hover(sf::Vector2f mouse_pos) {
	if (this->get_sprite_bounds().contains(mouse_pos)) {
		this->btn_state = Button_State::BTN_HOVER;
		this->update_sprite(this->hover_crop);
	}
	else {
		this->update_sprite(this->crop);
	}
}

void Button::check_click(sf::Event& event, sf::Vector2f mouse_pos) {
	if (event.type == sf::Event::MouseButtonReleased) {
		if (this->get_sprite_bounds().contains(mouse_pos)) {
			this->btn_state = Button_State::BTN_CLICKED;
		}
	}
}

void Button::update_sprite(sf::IntRect* crop) {
	this->sprite.setTextureRect(*crop);
}

Button_State Button::get_state() {
	return this->btn_state;
}

std::string Button::get_label() {
	return this->label;
}

void Button::set_selected() {
	this->btn_state = Button_State::BTN_SELECTED;
}

void Button::set_unselected() {
	this->btn_state = Button_State::BTN_IDLE;
}
