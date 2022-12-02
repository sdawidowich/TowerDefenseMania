#include "EventHandler.h"

void EventHandler::check_button_events(sf::RenderWindow& window, sf::Event& event, GUI* gui) {
	gui->reset_button_label();
	std::vector<Button>* buttons = gui->get_buttons();
	for (int i = 0; i < buttons->size(); i++) {
		sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
		(*buttons)[i].update(window, event, mouse_pos);

		if ((*buttons)[i].get_sprite_bounds().contains(mouse_pos)) {
			if ((*buttons)[i].get_label() == "archerTowerSelector")
				gui->set_button_label((*buttons)[i], TowerCost::ARCHER_TOWER);
			if ((*buttons)[i].get_label() == "wizardTowerSelector")
				gui->set_button_label((*buttons)[i], TowerCost::WIZARD_TOWER);
		}
	}
}

void EventHandler::check_selection_movement(sf::RenderWindow& window, GUI* gui) {
	if (gui->get_new_tower()) {
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
		gui->get_new_tower()->set_position(sf::Vector2f(mouse_pos));
	}
}

void EventHandler::check_tower_placement(sf::RenderWindow& window, sf::Event& event, GUI* gui, Environment* environment, std::vector<Tower*>& towers) {
	sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
	Tower* new_tower = gui->get_new_tower();
	Tile** tiles = environment->get_tiles();
	int num_tiles = environment->get_num_tiles();
	sf::Vector2i env_dimensions = environment->get_dimensions();

	// Reset highlights
	for (int i = 0; i < num_tiles; i++) {
		tiles[i]->set_highlight(false);
	}

	sf::Vector2f new_posiiton;
	int x_quadrant = -1;
	int y_quadrant = -1;
	for (int i = 0; i < num_tiles; i++) {
		if (tiles[i]->get_sprite_bounds().contains(mouse_pos)) {
			tiles[i]->set_highlight(true);

			sf::Vector2f tile_pos = tiles[i]->get_position();
			if (mouse_pos.x > tile_pos.x) {
				x_quadrant = 1;
			}
			if (mouse_pos.y > tile_pos.y) {
				y_quadrant = 1;
			}

			if ((i % env_dimensions.x) >= (env_dimensions.x - 1)) {
				x_quadrant = -1;
			}
			else if ((i % env_dimensions.x) <= 0) {
				x_quadrant = 1;
			}
			if ((i / env_dimensions.x) >= (env_dimensions.y - 1)) {
				y_quadrant = -1;
			}
			else if ((i / env_dimensions.x) <= 0) {
				y_quadrant = 1;
			}

			tiles[i + x_quadrant]->set_highlight(true);
			tiles[i + y_quadrant * env_dimensions.x]->set_highlight(true);
			tiles[i + x_quadrant + y_quadrant * env_dimensions.x]->set_highlight(true);

			sf::FloatRect tile_bounds = tiles[i]->get_sprite_bounds();
			new_posiiton = sf::Vector2f(tile_pos.x + (float)x_quadrant * 0.5f * tile_bounds.width, tile_pos.y + (float)y_quadrant * 0.5f * tile_bounds.height);
			break;
		}
	}

	if (event.type == sf::Event::MouseButtonReleased) {
		float left = tiles[0]->get_sprite_bounds().left;
		float top = tiles[0]->get_sprite_bounds().top;
		float width = tiles[num_tiles - 1]->get_sprite_bounds().left + tiles[num_tiles - 1]->get_sprite_bounds().width;
		float height = tiles[num_tiles - 1]->get_sprite_bounds().top + tiles[num_tiles - 1]->get_sprite_bounds().height;
		sf::FloatRect gameboard_bounds(left, top, width, height);

		if (gameboard_bounds.contains(mouse_pos)) {
			gui->get_new_tower()->set_position(new_posiiton);
			towers.push_back(gui->get_new_tower());
			gui->reset_selection();

			// Reset highlights
			for (int i = 0; i < num_tiles; i++) {
				tiles[i]->set_highlight(false);
			}
		}
	}
}

void EventHandler::check_tower_click(sf::RenderWindow& window, sf::Event& event, GUI* gui, std::vector<Tower*>& towers) {
	if (event.type == sf::Event::MouseButtonReleased) {
		sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));

		for (int i = 0; i < towers.size(); i++) {
			if (towers[i]->get_sprite_bounds().contains(mouse_pos)) {
				if (gui->get_tower_range_indicator()) {
					if (gui->get_tower_range_indicator()->getPosition() == towers[i]->get_position()) {
						delete gui->get_tower_range_indicator();
						gui->set_tower_range_indicator(nullptr);
						return;
					}
				}

				float radius = (float)towers[i]->get_range();
				sf::CircleShape* range_indicator = new sf::CircleShape(radius);
				range_indicator->setOrigin(sf::Vector2f(radius, radius));
				range_indicator->setPosition(towers[i]->get_position());
				range_indicator->setFillColor(sf::Color(255, 255, 255, 0));
				range_indicator->setOutlineThickness(2.f);
				range_indicator->setOutlineColor(sf::Color(255, 255, 255, 40));
				range_indicator->setPointCount(64);

				if (gui->get_tower_range_indicator() && gui->get_tower_range_indicator()->getPosition() == towers[i]->get_position()) {
					delete gui->get_tower_range_indicator();
				}
				gui->set_tower_range_indicator(range_indicator);
				return;
			}
		}

		if (gui->get_tower_range_indicator()) {
			delete gui->get_tower_range_indicator();
			gui->set_tower_range_indicator(nullptr);
			return;
		}
	}
}

EventHandler::EventHandler() {
}

void EventHandler::check_events(sf::RenderWindow& window, sf::Event& event, GUI* gui, Environment* environment, std::vector<Tower*>& towers) {
	//// Check button events ////
	this->check_button_events(window, event, gui);

	//// Move tower selection if a tower is selected ////
	this->check_selection_movement(window, gui);

	//// Check tower placing ////
	if (gui->get_new_tower()) {
		this->check_tower_placement(window, event, gui, environment, towers);
	}

	//// Check tower click ////
	this->check_tower_click(window, event, gui, towers);
}
