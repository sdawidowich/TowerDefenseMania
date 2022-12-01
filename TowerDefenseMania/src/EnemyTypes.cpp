#include "EnemyTypes.h"

Zombie::Zombie(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position, sf::Vector2i dir) 
	: Enemy(texture, crop, position, 2.0, 10, 2, 5, dir) {
}
