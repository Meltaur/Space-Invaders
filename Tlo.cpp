#include "External.h"

#include "T³o.h"

Tlo::Tlo()
{
	if (!muzyka_tla.openFromFile("space.ogg"))
		printf("Plik muzyczny nie zosta³ wczytany."); // error
	muzyka_tla.play();
	muzyka_tla.setLoop(true);
	muzyka_tla.setVolume(100);
	position.x = 0;
	position.y = 0;
	tlo1.loadFromFile("tlo.png");
	tlospr1.setTexture(tlo1);
	tlospr1.setPosition(position);
	position2.x = 0;
	position2.y = -1080;
	tlo2.loadFromFile("tlo2.png");
	tlospr2.setTexture(tlo2);
	tlospr2.setPosition(position2);
	if (!boom[0].loadFromFile("boom.wav"))
		printf("Plik muzyczny nie zostal wczytany. ");
	sound[0].setBuffer(boom[0]);
	if (!boom[1].loadFromFile("trafienie.wav"))
		printf("Plik muzyczny nie zostal wczytany. ");
	sound[1].setBuffer(boom[1]);
	if (!boom[2].loadFromFile("Serduszko.wav"))
		printf("Plik muzyczny nie zostal wczytany. ");
	sound[2].setBuffer(boom[2]);
}
void Tlo::przesun(float x_in, float y_in)
{
	sf::Vector2f pos;
	pos.x = x_in;
	pos.y = y_in;
	tlospr1.move(pos);
	position = tlospr1.getPosition();
	tlospr2.move(pos);
	position = tlospr2.getPosition();
}