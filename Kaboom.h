#pragma once
#include "External.h""

class Kaboom
{
private:
	sf::Vector2f position;
	sf::Clock zegar; // Zegar do odstêpu miêdzy klatkami animacji
	sf::Sprite eksplozja;
public:
	Kaboom(float pos_x, float pos_y);
	sf::Sprite Boom(float deltatime, sf::Texture& tekstura);
	sf::IntRect animacja;
};