#pragma once
#include "External.h""
#include "TextureManager.h""

class Tlo
{
private:
	sf::Music muzyka_tla;
	sf::Vector2f position; //Trzyma pozycje pierwszego t³a
	sf::Vector2f position2; //Trzyma pozycje drugiego t³a
	sf::Texture tlo1;
	sf::Sprite tlospr1;
	sf::Texture tlo2;
	sf::Sprite tlospr2;
	sf::Sound sound[3];
	sf::SoundBuffer boom[3];
public:
	Tlo();
	TextureManager tekstura; //Do trzymania tekstury
	void przesun(float x_in, float y_in);  //Ruch t³a
	sf::Sprite gettlo1() { return tlospr1; }; //Rysowanie pierwszego t³a
	sf::Vector2f getPos1() { return tlospr1.getPosition(); } //Zwracanie pozycji, konieczne przy warunkach ifa
	sf::Sprite gettlo2() { return tlospr2; }; //Rysowanie drugiego t³a
	sf::Vector2f getPos2() { return tlospr2.getPosition(); } //Zwracanie pozycji, konieczne przy warunkach ifa
	void przesuntlo1() { tlospr1.setPosition(0, -1080); } // Przesuwanie t³a, gdy to dojedzie do krawêdzi okna
	void przesuntlo2() { tlospr2.setPosition(0, -1080); } // Przesuwanie t³a, gdy to dojedzie do krawêdzi okna
	void dzwiek1() { sound[0].play(); } //DŸwiêk pocisków przy trafieniu przeciwnika
	void dzwiek2() { sound[1].play(); } //DŸwiêk pocisków przy trafieniu gracza
	void dzwiek3() { sound[2].play(); } //DŸwiêk przy ³apaniu serduszek
};