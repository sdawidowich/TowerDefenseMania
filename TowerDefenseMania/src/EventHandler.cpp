#include "EventHandler.h"

EventHandler::EventHandler() {
}

void EventHandler::check_events(sf::RenderWindow& window, sf::Event& event, GUI* gui, Environment* environment, std::vector<Tower*>& towers) {
	sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));

	//// Check button clicks ////
	std::vector<Button>* buttons = gui->get_buttons();
	for (int i = 0; i < buttons->size(); i++) {
		sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));
		(*buttons)[i].update(event, mouse_pos);

		if ((*buttons)[i].get_state() == Button_State::BTN_CLICKED) {
			if ((*buttons)[i].get_label() == "archerTowerSelector") {
				gui->select_tower<ArcherTower>((*buttons)[i], mouse_pos, 0);
				break;
			}
			else if ((*buttons)[i].get_label() == "wizardTowerSelector") {
				gui->select_tower<WizardTower>((*buttons)[i], mouse_pos, 1);
				break;
			}
		}
	}

	//// Move tower selection if a tower is selected ////
	if (gui->get_new_tower()) {
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
		gui->get_new_tower()->set_position(sf::Vector2f(mouse_pos));
	}

	//// Check tower placing ////

	if (gui->get_new_tower()) {
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
				new_posiiton = sf::Vector2f(tile_pos.x + x_quadrant * 0.5 * tile_bounds.width, tile_pos.y + y_quadrant * 0.5 * tile_bounds.height);
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
}
