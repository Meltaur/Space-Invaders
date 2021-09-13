#include "External.h""
#include "Strza³.h"

Strzal::Strzal(float x_in, float y_in)
{
	pocisk.loadFromFile("pocisk.png");
	position.x = x_in;
	position.y = y_in;
	pociskspr.setPosition(position);
}
void Strzal::przesun(double x_in, double y_in)
{
	sf::Vector2f pos;
	pos.x = x_in;
	pos.y = y_in;
	pociskspr.move(pos);
	position = pociskspr.getPosition();
}
void Strzal::rysuj(sf::RenderWindow& window) {

	pociskspr.setTexture(pocisk);
	window.draw(pociskspr);
}
void Strzal::dzwiek()
{
	if (czy_wystrzelony == false) {
		if (!wystrzal.loadFromFile("flaunch.ogg"))
			printf("Plik muzyczny nie zostal wczytany. ");
		sound.setBuffer(wystrzal);
		sound.play();
		czy_wystrzelony = true;
	}
}