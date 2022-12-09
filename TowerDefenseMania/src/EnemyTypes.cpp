#include "EnemyTypes.h"

Zombie::Zombie(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, sf::Texture* gui_textures, sf::IntRect* health_bar_crop, sf::Vector2i dir)
	: Enemy(texture, crop, position, gui_textures, health_bar_crop, 1.0, 10, 5, 10, dir) {
}
