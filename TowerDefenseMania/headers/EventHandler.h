#pragma once
#include <SFML/Graphics.hpp>

#include "Game_State.h"
#include "Menu.h"
#include "GUI.h"
#include "Environment.h"
#include "Tile.h"
#include "Tower.h"
#include "TowerTypes.h"
#include "Button.h"

class EventHandler {
private:
	void check_menu_button_events(sf::RenderWindow& window, sf::Event& event, Menu* menu);

	void check_button_events(sf::RenderWindow& window, sf::Event& event, GUI* gui);
	void check_selection_movement(sf::RenderWindow& window, GUI* gui);
	void check_tower_placement(sf::RenderWindow& window, sf::Event& event, GUI* gui, Environment* environment, std::vector<Tower*>& towers, int& gold);
	void check_tower_click(sf::RenderWindow& window, sf::Event& event, GUI* gui, std::vector<Tower*>& towers);
public:
	EventHandler();
	
	void check_events(sf::RenderWindow& window, sf::Event& event, Game_State& state, Menu* start_menu, Menu* stat_menu, GUI* gui, Environment* environment, std::vector<Tower*>& towers, int& gold);
};