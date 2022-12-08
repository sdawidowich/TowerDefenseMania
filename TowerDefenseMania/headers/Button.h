#pragma once
#include "Sprite.h"

#include <string>
#include <functional>

enum class Button_State {
	BTN_IDLE, BTN_HOVER, BTN_CLICKED
};

class Button : public Sprite {
private:
	std::string label;
	sf::Text text;
	Button_State btn_state;
	bool selected;

	std::function<void(sf::RenderWindow&, Button*)> on_idle;
	std::function<void(sf::RenderWindow&, Button*)> on_hover;
	std::function<void(sf::RenderWindow&, Button*)> on_click;

public:
	Button(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, std::string label, sf::Text text, 
		std::function<void(sf::RenderWindow&, Button*)> on_idle, 
		std::function<void(sf::RenderWindow&, Button*)> on_hover, 
		std::function<void(sf::RenderWindow&, Button*)> on_click);

	void update(sf::RenderWindow& window, sf::Event& event, sf::Vector2f mouse_pos);
	void check_hover(sf::RenderWindow& window, sf::Vector2f mouse_pos);
	void check_click(sf::RenderWindow& window, sf::Event& event, sf::Vector2f mouse_pos);

	void set_crop(sf::IntRect* crop);

	Button_State get_state();
	std::string get_label();

	void select();
	void deselect();
	bool is_selected();

	void draw(sf::RenderWindow& window) override;
};