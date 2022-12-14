#include "TowerTypes.h"

ArcherTower::ArcherTower(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position) 
	: Tower(texture, crop, position, 4, 200, TowerCost::ARCHER_TOWER, sf::Time(sf::seconds(0.75))) {

}

void ArcherTower::attack(std::vector<Enemy>& enemies, int& gold, GameStats& stats) {
	if (this->timer.getElapsedTime() >= this->attack_cooldown) {
		for (int i = 0; i < enemies.size(); i++) {
			sf::Vector2f tower_pos = this->get_position();
			sf::Vector2f enemy_pos = enemies[i].get_position();
			double distance = std::sqrt(std::pow(std::abs(tower_pos.x - enemy_pos.x), 2) + std::pow(std::abs(tower_pos.y - enemy_pos.y), 2));

			if (distance <= this->get_range()) {
				enemies[i].take_damage(this->get_attack_damage());

				stats.set_damage(stats.get_damage() + this->get_attack_damage());

				if (enemies[i].get_health() <= 0) {
					int gold_drop = enemies[i].get_gold_value();
					gold += gold_drop;
					enemies.erase(enemies.begin() + i);

					stats.set_gold(stats.get_gold() + gold_drop);
					stats.set_kills(stats.get_kills() + 1);
				}

				this->timer.restart();
				break;
			}
		}
	}
}

WizardTower::WizardTower(sf::Texture* texture, sf::IntRect* crop, sf::Vector2f position) 
	: Tower(texture, crop, position, 2, 100, TowerCost::WIZARD_TOWER, sf::Time(sf::seconds(1.5))) {

}

void WizardTower::attack(std::vector<Enemy>& enemies, int& gold, GameStats& stats) {
	if (this->timer.getElapsedTime() >= this->attack_cooldown) {
		for (int i = 0; i < enemies.size(); i++) {
			sf::Vector2f tower_pos = this->get_position();
			sf::Vector2f enemy_pos = enemies[i].get_position();
			double distance = std::sqrt(std::pow(std::abs(tower_pos.x - enemy_pos.x), 2) + std::pow(std::abs(tower_pos.y - enemy_pos.y), 2));

			if (distance <= this->get_range()) {
				enemies[i].take_damage(this->get_attack_damage());

				stats.set_damage(stats.get_damage() + this->get_attack_damage());

				if (enemies[i].get_health() <= 0) {
					int gold_drop = enemies[i].get_gold_value();
					gold += gold_drop;
					enemies.erase(enemies.begin() + i);

					stats.set_gold(stats.get_gold() + gold_drop);
					stats.set_kills(stats.get_kills() + 1);

					i--;
				}
				this->timer.restart();
			}
		}
	}
}
