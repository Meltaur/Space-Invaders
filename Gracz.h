#pragma once
#include "External.h""

class Gracz
{
private:
	sf::Vector2f position;
	sf::Texture statek;
	sf::Sprite statekspr;
public:
	Gracz(float x_in, float y_in);
	void przesun(float x_in, float y_in); //Ruch statkiem
	sf::Sprite getGracz() { return statekspr; };
	sf::Vector2f getPos() { return statekspr.getPosition(); }
	int getheight() { return statekspr.getTextureRect().height; }; //Do ifów z kolizjami
	int getwidth() { return statekspr.getTextureRect().width; }; //Do ifów z kolizjami
	int Zycia = 3; //Gdy gracz->Zycia==0 koniec gry.
};