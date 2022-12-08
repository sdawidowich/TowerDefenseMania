#pragma once
#include <SFML/Graphics.hpp>

#include "Game_State.h"
#include "StartScreen.h"
#include "GUI.h"
#include "Environment.h"
#include "Tile.h"
#include "Tower.h"
#include "TowerTypes.h"
#include "Button.h"

class EventHandler {
private:
	void check_start_screen_button_events(sf::RenderWindow& window, sf::Event& event, StartScreen* start_screen);

	void check_button_events(sf::RenderWindow& window, sf::Event& event, GUI* gui);
	void check_selection_movement(sf::RenderWindow& window, GUI* gui);
	void check_tower_placement(sf::RenderWindow& window, sf::Event& event, GUI* gui, Environment* environment, std::vector<Tower*>& towers, int& gold);
	void check_tower_click(sf::RenderWindow& window, sf::Event& event, GUI* gui, std::vector<Tower*>& towers);
public:
	EventHandler();
	
	void check_events(sf::RenderWindow& window, sf::Event& event, Game_State& state, StartScreen* start_screen, GUI* gui, Environment* environment, std::vector<Tower*>& towers, int& gold);
};