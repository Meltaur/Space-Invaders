#pragma once
#include "External.h""
#include "TextureManager.h"

class Przeciwnik
{
private:
	sf::SoundBuffer boom;
	sf::Sound sound;
	sf::Vector2f position;
	sf::Sprite Przeciwnikspr;
	TextureManager tekstura1;
	TextureManager tekstura2;
	TextureManager tekstura3; //trzy tekstury dla trzech rodzajów statków
public:
	int Rodzaj; //W zale¿noœci od rodzaju inna tekstura przeciwnika
	Przeciwnik(float x_in, float y_in, int a);
	void przesun(float x_in, float y_in);
	sf::Vector2f getPos() { return Przeciwnikspr.getPosition(); }
	void Zaladujteksture1(sf::RenderWindow& window);
	void Zaladujteksture2(sf::RenderWindow& window);
	void Zaladujteksture3(sf::RenderWindow& window);
	void setPosition(float x_in, float y_in);
	int getheight() { return Przeciwnikspr.getTextureRect().height; };
	int getwidth() { return Przeciwnikspr.getTextureRect().width; };
};