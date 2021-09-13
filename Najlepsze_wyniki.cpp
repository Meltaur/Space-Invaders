#include "External.h"
#include "Najlepsze_Wyniki.h"

Najlepsze_wyniki::Najlepsze_wyniki()
{
	if (!font.loadFromFile("Roboto.ttf"))
		return;
	for (int i = 0; i < 4; i++)
	{
		Napis[i].setFont(font);
		Napis[i].setFillColor(sf::Color::White);
		Napis[i].setCharacterSize(50);
	}
	Napis[0].setString("Najlepsze Wyniki");
	Napis[0].setPosition(sf::Vector2f(800, 200));
	Napis[1].setString("Wynik");
	Napis[1].setPosition(sf::Vector2f(400, 300));
	Napis[2].setString("Imie Gracza");
	Napis[2].setPosition(sf::Vector2f(900, 300));
	Napis[3].setString("Data");
	Napis[3].setPosition(sf::Vector2f(1400, 300));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Najlepsze[i][j].setFont(font);
			Najlepsze[i][j].setFillColor(sf::Color::White);
			Najlepsze[i][j].setCharacterSize(50);
			if (j == 0)
			{
				Najlepsze[i][j].setFillColor(sf::Color::Cyan);
			}
			if (i == 0)
			{
				Najlepsze[i][j].setPosition(sf::Vector2f(50, 350 + (70 * j)));
			}
			if (i >= 1)
			{
				Najlepsze[i][j].setPosition(sf::Vector2f(400 + (500 * (i - 1)), 350 + (70 * j)));
			}
			if (i == 0)
			{
				Licznik << j + 1;
				Najlepsze[i][j].setString(Licznik.str() + ".");
				Licznik.str(std::string());
			}
		}
	}
}

void Najlepsze_wyniki::update()
{
	err = fopen_s(&fp,"Rekordy.dat", "r+");
	rekordy = new Rekord[10];
	bufor = new Rekord[10];
	if (err == NULL)
	{
		fseek(fp, 0, SEEK_END);
		liczba_rekordow = ftell(fp) / sizeof(Rekord);
		rewind(fp);
		do {
			szukaj = 0;
			for (int i = 0; i < liczba_rekordow - 1; i++)
			{
				fseek(fp, i * sizeof(Rekord), SEEK_SET);
				fread(rekordy, sizeof(Rekord), 1, fp);
				fread(bufor, sizeof(Rekord), 1, fp);
				if (rekordy->wynik < bufor->wynik)
				{
					fseek(fp, i * sizeof(Rekord), SEEK_SET);
					fwrite(bufor, sizeof(Rekord), 1, fp);
					fwrite(rekordy, sizeof(Rekord), 1, fp);
					szukaj = 1;
				}
			}
		} while (szukaj == 1);
		rewind(fp);
		fread(rekordy, sizeof(Rekord), 10, fp);
		for (int j = 0; j < 10; j++)
		{
			for (int i = 1; i < 4; i++)
			{
				if (i == 1 && rekordy->imie != "")
				{
					Bufor1 << rekordy->wynik;
					Najlepsze[i][j].setString(Bufor1.str());
					Bufor1.str(std::string());
				}
				else if (i == 2)
				{
					Imie = rekordy->imie;
					Najlepsze[i][j].setString(Imie);
				}
				else if (i == 3 && rekordy->imie != "")
				{
					Bufor1 << rekordy->dzien;
					Bufor2 << rekordy->miesiac;
					Bufor3 << rekordy->rok;
					if (rekordy->dzien > 10 && rekordy->miesiac > 10)
					{
						Najlepsze[i][j].setString(Bufor1.str() + "-" + Bufor2.str() + "-" + Bufor3.str());
					}
					else if (rekordy->dzien > 10 && rekordy->miesiac < 10)
					{
						Najlepsze[i][j].setString(Bufor1.str() + "-0" + Bufor2.str() + "-" + Bufor3.str());
					}
					else if (rekordy->dzien < 10 && rekordy->miesiac > 10)
					{
						Najlepsze[i][j].setString("0" + Bufor1.str() + "-" + Bufor2.str() + "-" + Bufor3.str());
					}
					else if (rekordy->dzien < 10 && rekordy->miesiac < 10)
					{
						Najlepsze[i][j].setString("0" + Bufor1.str() + "-0" + Bufor2.str() + "-" + Bufor3.str());
					}
					Bufor1.str(std::string());
					Bufor2.str(std::string());
					Bufor3.str(std::string());
				}
			}
			rekordy++;
		}
	}
	else
	{
		err = fopen_s(&fp, "Rekordy.dat", "w+");
	}
}

void Najlepsze_wyniki::interfejs(sf::RenderWindow& window)
{
	for (int i = 0; i < 4; i++)
	{
		window.draw(Napis[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			window.draw(Najlepsze[i][j]);
		}
	}
}