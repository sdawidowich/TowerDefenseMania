#pragma once
#include <SFML/Graphics.hpp>

#include "Sprite.h"
#include "HealthBar.h"

class Enemy : public Sprite {
protected:
	float speed;
	int max_health;
	int health;
	int damage;
	int gold_value;
	int path_index;
	sf::Vector2i dir;

	HealthBar health_bar;
public:
	Enemy(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, sf::Texture* gui_textures, sf::IntRect* health_bar_crop, float speed, int health, int damage, int gold_value, sf::Vector2i dir);

	int get_health();
	int get_damage();
	int get_gold_value();
	int get_path_index();
	sf::Vector2i get_dir();

	void move();
	void update_health_bar();
	void set_path_index(int path_index);
	void change_dir(sf::Vector2i dir);
	void take_damage(int damage);

	void draw(sf::RenderWindow& window) override;
};