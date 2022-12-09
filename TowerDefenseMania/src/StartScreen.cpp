#include "StartScreen.h"

StartScreen::StartScreen(sf::Font* font, sf::Texture* gui_sprite_sheet, std::map<int, sf::IntRect*>* gui_sprites_indices, Game_State* state) {
	this->font = font;
	this->gui_sprite_sheet = gui_sprite_sheet;
	this->gui_sprites_indices = gui_sprites_indices;
	this->state = state;

	sf::Text play_text = sf::Text("Play", *this->font, 32);
	play_text.setPosition(sf::Vector2f(640, 190));
	sf::FloatRect bounds = play_text.getGlobalBounds();
	play_text.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));
	Button play_button = Button(this->gui_sprite_sheet, (*this->gui_sprites_indices)[8], sf::Vector2f(640, 200), "playButton", play_text,
		[this](sf::RenderWindow& window, Button* btn) {
			btn->set_crop((*this->gui_sprites_indices)[8]);
		},
		[this](sf::RenderWindow& window, Button* btn) {
			btn->set_crop((*this->gui_sprites_indices)[8]);
		},
		[this](sf::RenderWindow& window, Button* btn) {
			*(this->state) = Game_State::PLAYING;
		});
	play_button.set_scale(sf::Vector2f(7.f, 7.f));
	this->buttons.push_back(play_button);

	sf::Text view_stats_text = sf::Text("View Game Stats", *this->font, 20);
	view_stats_text.setPosition(sf::Vector2f(640, 320));
	bounds = view_stats_text.getGlobalBounds();
	view_stats_text.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));
	Button view_stats_button = Button(this->gui_sprite_sheet, (*this->gui_sprites_indices)[8], sf::Vector2f(640, 330), "quitButton", view_stats_text,
		[this](sf::RenderWindow& window, Button* btn) {
			btn->set_crop((*this->gui_sprites_indices)[8]);
		},
		[this](sf::RenderWindow& window, Button* btn) {
			btn->set_crop((*this->gui_sprites_indices)[8]);
		},
		[this](sf::RenderWindow& window, Button* btn) {
			*(this->state) = Game_State::STATS;
		});
	view_stats_button.set_scale(sf::Vector2f(7.f, 7.f));
	this->buttons.push_back(view_stats_button);

	sf::Text quit_text = sf::Text("Quit", *this->font, 32);
	quit_text.setPosition(sf::Vector2f(640, 450));
	bounds = quit_text.getGlobalBounds();
	quit_text.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));
	Button quit_button = Button(this->gui_sprite_sheet, (*this->gui_sprites_indices)[8], sf::Vector2f(640, 460), "quitButton", quit_text,
		[this](sf::RenderWindow& window, Button* btn) {
			btn->set_crop((*this->gui_sprites_indices)[8]);
		},
		[this](sf::RenderWindow& window, Button* btn) {
			btn->set_crop((*this->gui_sprites_indices)[8]);
		},
		[this](sf::RenderWindow& window, Button* btn) {
			window.close();
		});
	quit_button.set_scale(sf::Vector2f(7.f, 7.f));
	this->buttons.push_back(quit_button);
}

std::vector<Button>* StartScreen::get_buttons() {
	return &this->buttons;
}

void StartScreen::draw_buttons(sf::RenderWindow& window) {
	for (int i = 0; i < this->buttons.size(); i++) {
		this->buttons[i].draw(window);
	}
}
