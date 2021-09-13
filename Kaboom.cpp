#include "External.h""

#include "Kaboom.h"

Kaboom::Kaboom(float pos_x, float pos_y)
{
	animacja.top = 0;
	animacja.left = 0;
	animacja.width = 128;
	animacja.height = 128;
	position.x = pos_x;
	position.y = pos_y;
}
sf::Sprite Kaboom::Boom(float deltatime, sf::Texture& tekstura) //Funkcja wywo�ywana w ka�dej klatce programu. Uaktualnia klatk� animacji.
{
	float time = 0.5f, totaltime = 0.0f; //Zmienna time to granica do kt�rej d��y zmienna totaltime. Zmienna totaltime jest zwi�kszana co klatk� o delta time.
	eksplozja.setTexture(tekstura);
	eksplozja.setTextureRect(animacja);
	eksplozja.setPosition(position);
	do {
		if (time >= totaltime) // Je�li totaltime nie przekroczy�o granicy to zmie� klatk�
		{
			if (animacja.left == 1024)
			{
				animacja.top += 128;
				animacja.left = 0;
			}
			else {
				animacja.left += 128;
				totaltime = 0.0f; //Zerowanie totaltime
			}
		}
		else
		{
			totaltime += deltatime; //Dodawanie deltatime to totaltime.
		}
		eksplozja.setTextureRect(animacja);
		return eksplozja;
	} while (animacja.top < 1024 && animacja.left < 1024); //Gdy tekstura dojdzie do kraw�dzi p�tla si� przerywa.
	animacja.top = 0;
	animacja.left = 0;
	return eksplozja;
}