#include "External.h""
#include "Gracz.h"

Gracz::Gracz(float x_in, float y_in)
{
	position.x = x_in;
	position.y = y_in;
	statek.loadFromFile("statek.png");
	statekspr.setTexture(statek);
	statekspr.setPosition(position);
}

void Gracz::przesun(float x_in, float y_in)
{
	sf::Vector2f pos;
	pos.x = x_in;
	pos.y = y_in;
	statekspr.move(pos);
	position = statekspr.getPosition();
}