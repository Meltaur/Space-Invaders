#include "External.h""
#include "Wynik.h"



Wynik::Wynik()
{
	if (!font.loadFromFile("Roboto.ttf"))
		return;
	Napis.setFont(font);
	Napis.setFillColor(sf::Color::White);
	Napis.setCharacterSize(30);
	Napis.setString("Wynik:");
	Napis.setPosition(sf::Vector2f(20, 10));
	Napis2.setFont(font);
	Napis2.setFillColor(sf::Color::White);
	Napis2.setCharacterSize(30);
	Napis2.setPosition(sf::Vector2f(110, 10));
	ssuma << suma;
	Napis2.setString(ssuma.str());
}
void Wynik::update()
{
	ssuma.str(std::string());
	ssuma << suma;
	Napis2.setString(ssuma.str());
}
void Wynik::Dodaj_Rekord(std::string nazwa_in, float suma_in)
{
	Rekord* rekordy;
	rekordy = new Rekord();
	rekordy->imie = nazwa_in;
	rekordy->wynik = suma_in;


	_time64(&long_time);

	err = _localtime64_s(&newtime, &long_time);

	rekordy->dzien = newtime.tm_mday;
	rekordy->miesiac = newtime.tm_mon + 1;
	rekordy->rok = newtime.tm_year + 1900;

	err_2 = fopen_s(&fp, "Rekordy.dat", "a+");
	if (err_2 != NULL){
		err_2 = fopen_s(&fp, "Rekordy.dat", "w+");
	}
	fwrite(rekordy, sizeof(Rekord), 1, fp);
	fclose(fp);
	delete rekordy;
}