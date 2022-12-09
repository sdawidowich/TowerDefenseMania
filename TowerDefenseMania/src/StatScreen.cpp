#include "StatScreen.h"

StatScreen::StatScreen(sf::Font* font, sf::Texture* gui_sprite_sheet, std::map<int, sf::IntRect*>* gui_sprites_indices, Game_State* state) {
	this->font = font;
	this->gui_sprite_sheet = gui_sprite_sheet;
	this->gui_sprites_indices = gui_sprites_indices;
	this->state = state;
	this->page = 0;

	sf::Text back_text = sf::Text("Back", *this->font, 32);
	back_text.setPosition(sf::Vector2f(150, 60));
	sf::FloatRect bounds = back_text.getGlobalBounds();
	back_text.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));
	Button back_button = Button(this->gui_sprite_sheet, (*this->gui_sprites_indices)[8], sf::Vector2f(150, 70), "backButton", back_text,
		[this](sf::RenderWindow& window, Button* btn) {
			btn->set_crop((*this->gui_sprites_indices)[8]);
		},
		[this](sf::RenderWindow& window, Button* btn) {
			btn->set_crop((*this->gui_sprites_indices)[8]);
		},
		[this](sf::RenderWindow& window, Button* btn) {
			*(this->state) = Game_State::START;
		});
	back_button.set_scale(sf::Vector2f(7.f, 7.f));
	this->buttons.push_back(back_button);


	sf::Text next_text = sf::Text("Next >>", *this->font, 28);
	next_text.setPosition(sf::Vector2f(1130, 640));
	bounds = next_text.getGlobalBounds();
	next_text.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));
	Button next_button = Button(this->gui_sprite_sheet, (*this->gui_sprites_indices)[8], sf::Vector2f(1130, 650), "nextButton", next_text,
		[this](sf::RenderWindow& window, Button* btn) {
			btn->set_crop((*this->gui_sprites_indices)[8]);
		},
		[this](sf::RenderWindow& window, Button* btn) {
			btn->set_crop((*this->gui_sprites_indices)[8]);
		},
		[this](sf::RenderWindow& window, Button* btn) {
			this->page++;
		});
	next_button.set_scale(sf::Vector2f(7.f, 7.f));
	this->buttons.push_back(next_button);

	sf::Text previous_text = sf::Text("<< Previous", *this->font, 28);
	previous_text.setPosition(sf::Vector2f(150, 640));
	bounds = previous_text.getGlobalBounds();
	previous_text.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));
	Button previous_button = Button(this->gui_sprite_sheet, (*this->gui_sprites_indices)[8], sf::Vector2f(150, 650), "previousButton", previous_text,
		[this](sf::RenderWindow& window, Button* btn) {
			btn->set_crop((*this->gui_sprites_indices)[8]);
		},
		[this](sf::RenderWindow& window, Button* btn) {
			btn->set_crop((*this->gui_sprites_indices)[8]);
		},
			[this](sf::RenderWindow& window, Button* btn) {
			if (page > 0) {
				this->page--;
			}
		});
	previous_button.set_scale(sf::Vector2f(7.f, 7.f));
	this->buttons.push_back(previous_button);
}

std::vector<Button>* StatScreen::get_buttons() {
	return &this->buttons;
	
}

void StatScreen::draw_buttons(sf::RenderWindow& window) {
	for (int i = 0; i < this->buttons.size(); i++) {
		this->buttons[i].draw(window);
	}
}

void StatScreen::draw_stats(sf::RenderWindow& window, std::vector<GameStats>* stats_list) {
	int start_index = this->page * 10;

	sf::Text page_text;
	page_text.setFont(*this->font);
	page_text.setString("Page " + std::to_string(this->page + 1) + " / " + std::to_string((int)std::ceil((double)stats_list->size() / 10.0)));
	page_text.setCharacterSize(28);
	page_text.setPosition(sf::Vector2f(640.f, 650.f));
	sf::FloatRect bounds = page_text.getGlobalBounds();
	page_text.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));

	window.draw(page_text);

	for (int i = start_index; (i < start_index + 10) && i < stats_list->size(); i++) {
		float y = 150.f + 40.f * (i - start_index);

		sf::Text name_text;
		name_text.setFont(*this->font);
		name_text.setString((*stats_list)[i].get_name());
		name_text.setCharacterSize(18);
		name_text.setPosition(sf::Vector2f(30.f, y - 15.f));

		sf::Text time_text;
		time_text.setFont(*this->font);
		time_text.setString(std::to_string((*stats_list)[i].get_time()));
		time_text.setCharacterSize(18);
		time_text.setPosition(sf::Vector2f(230.f, y - 15.f));

		sf::Text level_text;
		level_text.setFont(*this->font);
		level_text.setString("Level " + std::to_string((*stats_list)[i].get_level()));
		level_text.setCharacterSize(18);
		level_text.setPosition(sf::Vector2f(400.f, y - 15.f));

		sf::Text kills_text;
		kills_text.setFont(*this->font);
		kills_text.setString(std::to_string((*stats_list)[i].get_kills()));
		kills_text.setCharacterSize(18);
		kills_text.setPosition(sf::Vector2f(560.f, y - 15.f));

		sf::Text gold_text;
		gold_text.setFont(*this->font);
		gold_text.setString(std::to_string((*stats_list)[i].get_gold()));
		gold_text.setCharacterSize(18);
		gold_text.setPosition(sf::Vector2f(690.f, y - 15.f));

		sf::Text damage_text;
		damage_text.setFont(*this->font);
		damage_text.setString(std::to_string((*stats_list)[i].get_damage()));
		damage_text.setCharacterSize(18);
		damage_text.setPosition(sf::Vector2f(820.f, y - 15.f));

		sf::Text towers_text;
		towers_text.setFont(*this->font);
		towers_text.setString(std::to_string((*stats_list)[i].get_towers()));
		towers_text.setCharacterSize(18);
		towers_text.setPosition(sf::Vector2f(920.f, y - 15.f));

		Sprite clock_icon(this->gui_sprite_sheet, (*this->gui_sprites_indices)[9], sf::Vector2f(200.f, y));
		Sprite skull_icon(this->gui_sprite_sheet, (*this->gui_sprites_indices)[10], sf::Vector2f(530.f, y));
		Sprite gold_icon(this->gui_sprite_sheet, (*this->gui_sprites_indices)[6], sf::Vector2f(660.f, y));
		Sprite sword_icon(this->gui_sprite_sheet, (*this->gui_sprites_indices)[11], sf::Vector2f(790.f, y));
		Sprite tower_icon(this->gui_sprite_sheet, (*this->gui_sprites_indices)[12], sf::Vector2f(890.f, y));

		window.draw(name_text);
		window.draw(time_text);
		window.draw(level_text);
		window.draw(kills_text);
		window.draw(gold_text);
		window.draw(damage_text);
		window.draw(towers_text);

		clock_icon.draw(window);
		skull_icon.draw(window);
		gold_icon.draw(window);
		sword_icon.draw(window);
		tower_icon.draw(window);
	}
}
