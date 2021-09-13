#include "External.h"
#include "Serce.h"

Serca::Serca(float pos_x, float pos_y)
{
	position.x = pos_x;
	position.y = pos_y;
	tekstura_pelne.ZaladujTeksture("Tekstura serca", "heart_full.png");
	tekstura_puste.ZaladujTeksture("Tekstura pustego serca", "heart_empty.png");
	serce_pelne.setTexture(tekstura_pelne.GetTexture("Tekstura serca"));
	serce_puste.setTexture(tekstura_puste.GetTexture("Tekstura pustego serca"));
	serce_pelne.setPosition(pos_x, pos_y);
	serce_puste.setPosition(pos_x, pos_y);
}
void Serca::przesun(float x, float y)
{
	sf::Vector2f pos;
	pos.x = x;
	pos.y = y;
	serce_pelne.move(pos);
	position = serce_pelne.getPosition();
}
void Serca::Zaladujteksture(sf::RenderWindow& window)
{
	this->serce_pelne.setTexture(this->tekstura_pelne.GetTexture("Tekstura serca"));
	window.draw(serce_pelne);
}