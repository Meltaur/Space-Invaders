#include "External.h"

#include "Przeciwnik.h"

Przeciwnik::Przeciwnik(float x_in, float y_in, int a)
{
	if (a == 0)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1SN.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2SN.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3SN.png");
	}
	else if (a == 1)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1SZ.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2SZ.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3SZ.png");
	}
	else if (a == 2)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1SP.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2SP.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3SP.png");
	}
	else if (a == 3)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1SF.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2SF.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3SF.png");
	}
	else if (a == 4)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1SC.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2SC.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3SC.png");
	}
	else if (a == 5)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1CN.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2CN.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3CN.png");
	}
	else if (a == 6)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1CZ.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2CZ.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3CZ.png");
	}
	else if (a == 7)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1CP.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2CP.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3CP.png");
	}
	else if (a == 8)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1CF.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2CF.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3CF.png");
	}
	else if (a == 9)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1CC.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2CC.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3CC.png");
	}
	else if (a == 10)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1CY.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2CY.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3CY.png");
	}
	position.x = x_in;
	position.y = y_in;
	Przeciwnikspr.setPosition(position);
}
void Przeciwnik::przesun(float x_in, float y_in)
{
	sf::Vector2f pos;
	pos.x = x_in;
	pos.y = y_in;
	Przeciwnikspr.move(pos);
	position = Przeciwnikspr.getPosition();
}
void Przeciwnik::Zaladujteksture1(sf::RenderWindow& window)
{
	this->Przeciwnikspr.setTexture(this->tekstura1.GetTexture("Tekstura przeciwnika 1"));
	window.draw(Przeciwnikspr);
}
void Przeciwnik::Zaladujteksture2(sf::RenderWindow& window)
{
	this->Przeciwnikspr.setTexture(this->tekstura2.GetTexture("Tekstura przeciwnika 2"));
	window.draw(Przeciwnikspr);
}
void Przeciwnik::Zaladujteksture3(sf::RenderWindow& window)
{
	this->Przeciwnikspr.setTexture(this->tekstura3.GetTexture("Tekstura przeciwnika 3"));
	window.draw(Przeciwnikspr);
}
void Przeciwnik::setPosition(float x_in, float y_in)
{
	sf::Vector2f pos;
	pos.x = x_in;
	pos.y = y_in;
	Przeciwnikspr.setPosition(pos);
}