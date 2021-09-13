#include "External.h""
#include "Menu.h"

Menu::Menu(float width, float height)
{
	tlom.loadFromFile("Menu.png");
	tlomspr.setTexture(tlom);
	position.x = 0;
	position.y = 0;
	tlomspr.setPosition(position);
	if (!font.loadFromFile("Roboto.ttf"))
		return;
	for (int i = 0; i < 4; i++)
	{
		menu[i].setFont(font);
		menu[i].setCharacterSize(50);
		if (i > 0)
			menu[i].setFillColor(sf::Color::White);
	}
	menu[0].setFillColor(sf::Color::Cyan);
	menu[0].setString("Nowa gra");
	menu[0].setPosition(sf::Vector2f(width / 2.3, height / 3.5));
	menu[1].setString("Najlepsze wyniki");
	menu[1].setPosition(sf::Vector2f(width / 2.3, (height / 3.5) + 180));
	menu[2].setString("Opcje");
	menu[2].setPosition(sf::Vector2f(width / 2.3, (height / 3.5) + 330));
	menu[3].setString("Wyjscie");
	menu[3].setPosition(sf::Vector2f(width / 2.3, (height / 3.5) + 480));
}
void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
	{
		window.draw(menu[i]);
	}
}
void Menu::moveUp()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW) //Poruszaj siê po menu tylko jeœli wybrana opcja jest w zakresie 0-3
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;    //Nastêpuje zmiana. Wskazywany przedmiot jest o jeden mniejszy
		if (selectedItem < 0) //Jeœli wskazywana opcja jest na samej górze to nastêpi przeskok do opcji na samym dole.
			selectedItem = MAX_LICZBA_POZIOMOW - 1;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
}
void Menu::moveDown()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW) //analogicznie jak wy¿ej
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= MAX_LICZBA_POZIOMOW)
			selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
}