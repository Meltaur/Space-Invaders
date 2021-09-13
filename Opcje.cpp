#include "External.h""
#include "Opcje.h"

const int MAX_LICZBA_POZIOMOW = 4;
const int MAX_LICZBA_POZIOMOW_OPCJI = 4;

Opcje::Opcje()
{
	if (!font.loadFromFile("Roboto.ttf"))
		return;
	for (int i = 0; i < 6; i++)
	{
		Napis[i].setFont(font);
		Napis[i].setFillColor(sf::Color::White);
		Napis[i].setCharacterSize(50);
		if (i < 5)
		{
			Suwaki[i].setFont(font);
			Suwaki[i].setFillColor(sf::Color::White);
			Suwaki[i].setCharacterSize(50);
			Suwaki[i].setPosition(sf::Vector2f(1300, 300 + (i * 150)));
			if (i < 3)
			{
				Liczby[i] << liczniki[i];
				Suwaki[i].setString(Liczby[i].str());
				Liczby[i].str(std::string(""));
			}
		}
	}
	Napis[0].setString("Opcje");
	Napis[0].setPosition(sf::Vector2f(900, 200));
	Napis[1].setString("Czestotliwosc strzalow przeciwnikow");
	Napis[1].setFillColor(sf::Color::Cyan);
	Napis[1].setStyle(sf::Text::Bold);
	Napis[1].setPosition(sf::Vector2f(100, 300));
	Napis[2].setString("Predkosc pociskow przeciwnikow");
	Napis[2].setPosition(sf::Vector2f(100, 450));
	Napis[3].setString("Czestotliwosc pojawiania sie dodatkowych zyc");
	Napis[3].setPosition(sf::Vector2f(100, 600));
	Napis[4].setString("Kolor statkow przeciwnikow");
	Napis[4].setPosition(sf::Vector2f(100, 750));
	Napis[5].setString("Mnoznik punktow");
	Napis[5].setPosition(sf::Vector2f(100, 900));
	Suwaki[3].setString(Tekstury[0]);
	Liczby[3] << mnoznik;
	Suwaki[4].setString("x" + Liczby[3].str() + ".0");
	Liczby[3].str(std::string(""));
}
void Opcje::moveUp()
{
	if (selectedItem + 1 >= 0 && selectedItem + 1 < MAX_LICZBA_POZIOMOW_OPCJI + 1)
	{
		Napis[selectedItem + 1].setFillColor(sf::Color::White);
		Napis[selectedItem + 1].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = MAX_LICZBA_POZIOMOW_OPCJI - 1;
		Napis[selectedItem + 1].setFillColor(sf::Color::Cyan);
		Napis[selectedItem + 1].setStyle(sf::Text::Bold);
	}
}
void Opcje::moveDown()
{
	if (selectedItem + 1 >= 0 && selectedItem < MAX_LICZBA_POZIOMOW_OPCJI + 1)
	{
		Napis[selectedItem + 1].setFillColor(sf::Color::White);
		Napis[selectedItem + 1].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem + 1 >= MAX_LICZBA_POZIOMOW_OPCJI + 1)
			selectedItem = 0;
		Napis[selectedItem + 1].setFillColor(sf::Color::Cyan);
		Napis[selectedItem + 1].setStyle(sf::Text::Bold);
	}
}
void Opcje::zmiana(int a)
{
	Napis[a + 1].setFillColor(sf::Color::White);
	Napis[a + 1].setStyle(sf::Text::Regular);
	Suwaki[a].setFillColor(sf::Color::Cyan);
	Suwaki[a].setStyle(sf::Text::Bold);
}
void Opcje::powrot(int a)
{
	Napis[a + 1].setFillColor(sf::Color::Cyan);
	Napis[a + 1].setStyle(sf::Text::Bold);
	Suwaki[a].setFillColor(sf::Color::White);
	Suwaki[a].setStyle(sf::Text::Regular);
}
void Opcje::przesuwanie_gora(int a)
{
	if (liczniki[a] >= 1 && liczniki[a] < 6)
	{
		liczniki[a]++;
		Liczby[a] << liczniki[a];
		Suwaki[a].setString(Liczby[a].str());
		Liczby[a].str(std::string(""));
		mnoznik = mnoznik + 0.1;
		Liczby[3] << mnoznik;
		if (mnoznik >= 0.99 && mnoznik <= 1.01)
		{
			Suwaki[4].setString("x" + Liczby[3].str() + ".0");
		}
		else
		{
			Suwaki[4].setString("x" + Liczby[3].str());
		}
		Liczby[3].str(std::string(""));
	}
	if (mnoznik >= 1.89)
	{
		mnoznik = 2;
		Liczby[3] << mnoznik;
		Suwaki[4].setString("x" + Liczby[3].str() + ".0");
		Liczby[3].str(std::string(""));
	}
}
void Opcje::przesuwanie_dol(int a)
{
	if (liczniki[a] > 1 && liczniki[a] <= 6)
	{
		liczniki[a]--;
		Liczby[a] << liczniki[a];
		Suwaki[a].setString(Liczby[a].str());
		Liczby[a].str(std::string(""));
		if (mnoznik >= 2)
		{
			mnoznik = 1.8;
			Liczby[3] << mnoznik;
			Suwaki[4].setString("x" + Liczby[3].str());
			Liczby[3].str(std::string(""));
		}
		else
		{
			mnoznik = mnoznik - 0.1;
			Liczby[3] << mnoznik;
			if (mnoznik >= 0.99 && mnoznik <= 1.01)
			{
				Suwaki[4].setString("x" + Liczby[3].str() + ".0");
			}
			else
			{
				Suwaki[4].setString("x" + Liczby[3].str());
			}
			Liczby[3].str(std::string(""));
		}
	}
}
void Opcje::przesuwanie_gora_kolor(int a)
{
	if (tekstury >= 0 && tekstury < 10)
	{
		tekstury++;
		Suwaki[3].setString(Tekstury[tekstury]);
	}
}
void Opcje::przesuwanie_dol_kolor(int a)
{
	if (tekstury > 0 && tekstury <= 10)
	{
		tekstury--;
		Suwaki[3].setString(Tekstury[tekstury]);
	}
}

void Opcje::interfejs(sf::RenderWindow& window)
{
	for (int i = 0; i < 6; i++)
	{
		window.draw(Napis[i]);
		if (i < 5)
		{
			window.draw(Suwaki[i]);
		}
	}
}