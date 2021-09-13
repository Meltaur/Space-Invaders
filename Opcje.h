#pragma once
#include "External.h""

class Opcje {
private:
	sf::Font font;
	sf::Text Napis[6];
	sf::Text Suwaki[5];
	std::stringstream Liczby[4];
	int selectedItem = 0;
	std::string Tekstury[11] = { "Szaro-Niebieski", "Szaro-Zielony", "Szaro-Pomaranczowy", "Szaro-Fioletowy", "Szaro-Czerwony", "Czarno-Niebieski", "Czarno-Zielony", "Czarno-Pomaranczowy", "Czarno-Fioletowy", "Czarno-Czerwony", "Czarno-Zolty" };
public:
	Opcje();
	~Opcje();
	void interfejs(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	int getSelectedItem() { return selectedItem; }
	float liczniki[3] = { 3,3,3 };
	float mnoznik = 1;
	int tekstury = 0;
	void zmiana(int a);
	void powrot(int a);
	void przesuwanie_gora(int a);
	void przesuwanie_dol(int a);
	void przesuwanie_gora_kolor(int a);
	void przesuwanie_dol_kolor(int a);
};