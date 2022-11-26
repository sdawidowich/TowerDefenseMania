#pragma once
#include "Sprite.h"

#include <string>

enum class Button_State {
	BTN_IDLE, BTN_HOVER, BTN_CLICKED
};

class Button : public Sprite {
private:
	Button_State btn_state;
	bool selected;

	std::string label;
	sf::IntRect* hover_crop;
	sf::IntRect* selected_crop;
public:
	Button(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, std::string label, sf::IntRect* hover_crop, sf::IntRect* selected_crop);

	void update(sf::Event& event, sf::Vector2f mouse_pos);
	void check_hover(sf::Vector2f mouse_pos);
	void check_click(sf::Event& event, sf::Vector2f mouse_pos);

	void update_sprite(sf::IntRect* crop);

	Button_State get_state();
	std::string get_label();

	void select();
	void deselect();
	bool get_selected();
};