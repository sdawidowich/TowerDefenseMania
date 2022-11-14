#pragma once
#include "Sprite.h"

enum Button_State {
	BTN_IDLE = 0, BTN_HOVER = 1, BTN_PRESSED = 2
};

class Button : public Sprite {
private:
	Button_State btn_state;
public:
	Button(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position);

	void update(sf::Event& event, sf::Vector2f mouse_pos);
	void check_hover(sf::Vector2f mouse_pos);
	void check_click(sf::Event& event, sf::Vector2f mouse_pos);

	Button_State get_state();
};