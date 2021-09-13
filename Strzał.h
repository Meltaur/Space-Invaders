#pragma once
#include "External.h""

class Strzal
{
private:
	sf::SoundBuffer wystrzal;
	sf::Sound sound;
	sf::Vector2f position;
	sf::Texture pocisk;
	sf::Sprite pociskspr;
	bool czy_wystrzelony = false; //Zapobiega ponownym odtworzeniom pliku dŸwiêkowego w ka¿dej kolejnej klatce gry.
public:
	int Rodzaj; //W zale¿noœci od rodzaju statki strzelaj¹ inaczej.
	bool czy_odbity = false; //Zmienna odpowiedzialna za odbijanie pocisków, lec¹cych pod k¹tem, od œciany.
public:
	Strzal(float x_in, float y_in);
	void przesun(double x_in, double y_in); //ruch pocisku
	sf::Sprite getPocisk() { return pociskspr; };
	void rysuj(sf::RenderWindow& window);
	sf::Vector2f getPos() { return pociskspr.getPosition(); }
	void dzwiek();
	int getheight() { return pociskspr.getTextureRect().height; };
	int getwidth() { return pociskspr.getTextureRect().width; };
};