#pragma once
#include "External.h""

class Escape
{
private:
	sf::Font font;
	sf::Text Napis[5];
	sf::Text F1[7];
	std::stringstream Liczba;
	int selectedItem = 0;
public:
	Escape();
	void drukuj_p(sf::RenderWindow& window);
	void drukuj_k(sf::RenderWindow& window);
	void drukuj_F1(sf::RenderWindow& window);
	int getSelectedItem() { return selectedItem; }
	bool czy_pauza = false;
	bool czy_F1 = false;
	void moveRight();
	void moveLeft();
	void ustaw_wynik(int wynik);
};