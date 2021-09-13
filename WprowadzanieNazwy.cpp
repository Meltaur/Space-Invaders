#include "External.h"
#include "WprowadzanieNazwy.h"

WprowadzanieNazwy::WprowadzanieNazwy()
{
	if (!font.loadFromFile("Roboto.ttf"))
		return;
	Napis.setFont(font);
	Napis.setFillColor(sf::Color::White);
	Napis.setCharacterSize(50);
	Napis.setString("Podaj nazwe gracza:");
	Napis.setPosition(sf::Vector2f(750, 460));
	Napis2.setFont(font);
	Napis2.setFillColor(sf::Color::White);
	Napis2.setCharacterSize(50);
	Napis2.setPosition(sf::Vector2f(800, 530));
	Napis2.setString(nazwa_gracza);
}
