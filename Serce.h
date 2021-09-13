#pragma once
#include "External.h""
#include "TextureManager.h"

class Serca
{
private:
	sf::Vector2f position;
	TextureManager tekstura_pelne;
	TextureManager tekstura_puste;
	sf::Sprite serce_pelne;
	sf::Sprite serce_puste;
public:
	Serca(float pos_x, float pos_y);
	void przesun(float x, float y);
	void Rysuj_pelne(sf::RenderWindow& window) { window.draw(serce_pelne); };
	void Rysuj_puste(sf::RenderWindow& window) { window.draw(serce_puste); };
	sf::Vector2f getPos() { return serce_pelne.getPosition(); }
	int getheight() { return serce_pelne.getTextureRect().height; };
	int getwidth() { return serce_pelne.getTextureRect().width; };
	void Zaladujteksture(sf::RenderWindow& window); //Konieczne do lataj¹cych serduszek
};