#pragma once
#include "External.h"

class WprowadzanieNazwy
{
private:
	sf::Font font;
	sf::Text Napis;
	sf::Text Napis2;
public:
	WprowadzanieNazwy();
	std::string nazwa_gracza = "";
	void draw(sf::RenderWindow& window) { window.draw(Napis); };
	void update(std::string nowa_nazwa) //Funkcja wywo³ywana za ka¿dym razem gdy wciœniêty jest przycisk. Dodaje do stringu jeden znak.
	{
		nazwa_gracza += nowa_nazwa;
		Napis2.setString(nazwa_gracza);
	}
	void draw_nazwe(sf::RenderWindow& window) { window.draw(Napis2); };
};