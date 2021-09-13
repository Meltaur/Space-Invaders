#pragma once
#include "Rekord.h"

class Najlepsze_wyniki {
private:
	sf::Font font;
	sf::Text Napis[4];
	sf::Text Najlepsze[4][10];
	Rekord* rekordy, * bufor;
	FILE* fp;
	std::stringstream Licznik;
	std::stringstream Bufor1;
	std::stringstream Bufor2;
	std::stringstream Bufor3;
	std::string Imie;
	errno_t err;
	int liczba_rekordow, szukaj;
public:
	Najlepsze_wyniki();
	~Najlepsze_wyniki() { fclose(fp); }
	void interfejs(sf::RenderWindow& window);
	void update();
};