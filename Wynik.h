#pragma once
#include "External.h""
#include "Rekord.h"


class Wynik
{
private:
	sf::Font font;
	sf::Text Napis;
	sf::Text Napis2;
	std::stringstream ssuma;

	struct tm newtime;
	__time64_t long_time;
	errno_t err,err_2;
	FILE* fp;
public:
	Wynik();
	void draw(sf::RenderWindow& window) { window.draw(Napis); window.draw(Napis2); };
	void update();
	void Dodaj_Rekord(std::string nazwa_in, float suma_in);
	float suma = 0;
};