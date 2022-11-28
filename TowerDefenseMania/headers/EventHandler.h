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
public:
	EventHandler();
	
	void check_events(sf::RenderWindow& window, sf::Event& event, GUI* gui, Environment* environment, std::vector<Tower*>& towers);
};