#pragma once
#include "External.h"

const int MAX_LICZBA_POZIOMOW = 4;
const int MAX_LICZBA_POZIOMOW_OPCJI = 4;

class Menu
{
private:
	sf::Vector2f position;
	sf::Texture tlom;
	sf::Sprite tlomspr;
	sf::Font font;
	sf::Text menu[MAX_LICZBA_POZIOMOW];
	int selectedItem = 0; //Zmienna wskazuj¹ca na to która opcja w menu jest obecnie zaznaczona przez u¿ytkownika
public:
	Menu(float width, float height);
	~Menu() {};
	void moveUp();
	void moveDown();
	int getSelectedItem() { return selectedItem; }
	void draw(sf::RenderWindow& window);
	sf::Sprite gettlo() { return tlomspr; };
};