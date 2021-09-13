#include "External.h"
#include "Escape.h"

Escape::Escape()
{
	if (!font.loadFromFile("Roboto.ttf"))
		return;
	for (int i = 0; i < 5; i++)
	{
		Napis[i].setFont(font);
		Napis[i].setFillColor(sf::Color::White);
		Napis[i].setCharacterSize(50);
	}
	Napis[0].setPosition(sf::Vector2f(650, 400));
	Napis[0].setString("Czy chcesz zakonczyc rozgrywke?");
	Napis[1].setFillColor(sf::Color::Cyan);
	Napis[1].setStyle(sf::Text::Bold);
	Napis[1].setString("Tak");
	Napis[1].setPosition(sf::Vector2f(800, 460));
	Napis[2].setString("Nie");
	Napis[2].setPosition(sf::Vector2f(1100, 460));
	Napis[3].setString("Twoj wynik to:");
	Napis[3].setPosition(sf::Vector2f(830, 400));
	Napis[4].setPosition(sf::Vector2f(850, 460));
	for (int i = 0; i < 7; i++)
	{
		F1[i].setFont(font);
		F1[i].setFillColor(sf::Color::White);
		F1[i].setCharacterSize(50);
		if (i >= 1)
			F1[i].setPosition(sf::Vector2f(100, 100 + (100 * i)));
	}
	F1[0].setString("Pomoc");
	F1[0].setPosition(sf::Vector2f(900, 100));
	F1[1].setString("A-> Poruszanie statkiem w lewo");
	F1[2].setString("D-> Poruszanie statkiem w prawo");
	F1[3].setString("Spacja-> Wystrzal");
	F1[4].setString("Celem gry jest zestrzelenie jak najwiekszej liczby przeciwnikow i unikanie ich pociskow.");
	F1[5].setString("Przeciwnicy pozostawiaja czasami serca. Zbieraj je, by zwiekszec liczbe zyc.");
	F1[6].setString("Wcisnij F1, by wylaczyc pomoc.");
}
void Escape::moveRight()
{
	if (selectedItem == 0)
	{
		Napis[selectedItem + 1].setFillColor(sf::Color::White);
		Napis[selectedItem + 1].setStyle(sf::Text::Regular);
		selectedItem++;
		Napis[selectedItem + 1].setFillColor(sf::Color::Cyan);
		Napis[selectedItem + 1].setStyle(sf::Text::Bold);
	}
}
void Escape::moveLeft()
{
	if (selectedItem == 1)
	{
		Napis[selectedItem + 1].setFillColor(sf::Color::White);
		Napis[selectedItem + 1].setStyle(sf::Text::Regular);
		selectedItem--;
		Napis[selectedItem + 1].setFillColor(sf::Color::Cyan);
		Napis[selectedItem + 1].setStyle(sf::Text::Bold);
	}
}

void Escape::drukuj_p(sf::RenderWindow& window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(Napis[i]);
	}
}
void Escape::drukuj_k(sf::RenderWindow& window)
{
	for (int i = 3; i < 5; i++)
	{
		window.draw(Napis[i]);
	}
}
void Escape::drukuj_F1(sf::RenderWindow& window)
{
	for (int i = 0; i < 7; i++)
	{
		window.draw(F1[i]);
	}
}
void Escape::ustaw_wynik(int wynik)
{
	Liczba << wynik;
	Napis[4].setString(Liczba.str());
	Liczba.str(std::string(""));
}