#pragma once
#include <SFML/Graphics.hpp>

#include "GUI.h"
#include "Environment.h"
#include "Tile.h"
#include "Tower.h"
#include "TowerTypes.h"
#include "Button.h"

class EventHandler {
private:
	void check_button_clicks(sf::RenderWindow& window, sf::Event& event, GUI* gui);
	void check_button_hovers(sf::RenderWindow& window, sf::Event& event, GUI* gui);
	void check_selection_movement(sf::RenderWindow& window, GUI* gui);
	void check_tower_placement(sf::RenderWindow& window, sf::Event& event, GUI* gui, Environment* environment, std::vector<Tower*>& towers);
	void check_tower_click(sf::RenderWindow& window, sf::Event& event, GUI* gui, std::vector<Tower*>& towers);
public:
	EventHandler();
	
	void check_events(sf::RenderWindow& window, sf::Event& event, GUI* gui, Environment* environment, std::vector<Tower*>& towers);
};