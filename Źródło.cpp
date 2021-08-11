/*----------------------------------------------------------

Temat projektu: Space Invader

Zakres projektu:
1. Gra wzorowana na klasycznym Space Invader.
2. Punkty przydzielane za zestrzeliwanie obcych mno¿one przez mno¿nik poziomu trudnoœci.
3. Kilka mo¿liwoœci zmiany poziomu trudnoœci poprzez zmianê wartoœci parametrów.
4. Minimum 3 rodzaje przeciwników, ró¿ni¹cych siê tekstur¹ i zachowaniem.
5. Gra nieskoñczona, do czasu utraty ¿yæ.`1

Co zrealizowalem w biezacym tygodniu?
Dodane dŸwiêki przy trafieniu gracza, oraz przy ³apaniu serduszek.
Dodanie pomocy przy wciœnieciu F1
------------------------------------------------------------*/


/*----------------------------------------------------------

Program glowny

------------------------------------------------------------*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include <map>
#include <string>
#include <sstream>
#include <stdio.h>
#include <math.h>


typedef struct {
	std::string imie = "";
	float wynik = 0;
	int dzien = 0;
	int miesiac = 0;
	int rok = 0;
}Rekord;

/**********************************************************************************MENAD¯ER TEKSTUR******************************************************************************/
class TextureManager
{
private:
	std::map<std::string, sf::Texture> tekstury;
public:
	TextureManager() {};
	~TextureManager() {};
	void ZaladujTeksture(const std::string& nazwa, const std::string &fileName);
	sf::Texture& GetTexture(const std::string& texture);
};
void TextureManager::ZaladujTeksture(const std::string& nazwa, const std::string &fileName)
{
	sf::Texture tex;
	if (tex.loadFromFile(fileName))
		this->tekstury[nazwa] = tex; //Wk³adanie do mapy
}
sf::Texture& TextureManager::GetTexture(const std::string& texture)
{
	return this->tekstury.at(texture); //Wyci¹ganie tekstury z mapy
}
/**********************************************************************************T£O******************************************************************************/
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
	void przesuntlo1() {tlospr1.setPosition(0, -1080);} // Przesuwanie t³a, gdy to dojedzie do krawêdzi okna
	void przesuntlo2() { tlospr2.setPosition(0, -1080);} // Przesuwanie t³a, gdy to dojedzie do krawêdzi okna
	void dzwiek1() { sound[0].play(); } //DŸwiêk pocisków przy trafieniu przeciwnika
	void dzwiek2() { sound[1].play(); } //DŸwiêk pocisków przy trafieniu gracza
	void dzwiek3() { sound[2].play(); } //DŸwiêk przy ³apaniu serduszek
};

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
/**********************************************************************************GRACZ******************************************************************************/
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
public:
	int Zycia = 3; //Gdy gracz->Zycia==0 koniec gry.
};

Gracz::Gracz(float x_in, float y_in)
{
	position.x = x_in;
	position.y = y_in;
	statek.loadFromFile("statek.png");
	statekspr.setTexture(statek);
	statekspr.setPosition(position);
}

void Gracz::przesun(float x_in, float y_in)
{
	sf::Vector2f pos;
	pos.x = x_in;
	pos.y = y_in;
	statekspr.move(pos);
	position = statekspr.getPosition();
}
/**********************************************************************************STRZA£******************************************************************************/
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
	void rysuj(sf::RenderWindow &window);
	sf::Vector2f getPos() { return pociskspr.getPosition(); }
	void dzwiek();
	int getheight() { return pociskspr.getTextureRect().height; };
	int getwidth() { return pociskspr.getTextureRect().width; };
};
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
void Strzal::rysuj(sf::RenderWindow &window) {

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
const int MAX_LICZBA_POZIOMOW = 4;
const int MAX_LICZBA_POZIOMOW_OPCJI = 4;
/**********************************************************************************MENU******************************************************************************/
class Menu
{
private:
	sf::Vector2f position;
	sf::Texture tlom;
	sf::Sprite tlomspr;
	sf::Font font;
	sf::Text menu[MAX_LICZBA_POZIOMOW];
	int selectedItem = 0; //Zmienna wskazuj¹ca na to która opcja w menu jest obecnie zaznaczona przez u¿ytkownika
public:
	Menu(float width, float height);
	~Menu() {};
	void moveUp();
	void moveDown();
	int getSelectedItem() { return selectedItem; }
	void draw(sf::RenderWindow &window);
	sf::Sprite gettlo() { return tlomspr; };
};
Menu::Menu(float width, float height)
{
	tlom.loadFromFile("Menu.png");
	tlomspr.setTexture(tlom);
	position.x = 0;
	position.y = 0;
	tlomspr.setPosition(position);
	if (!font.loadFromFile("Roboto.ttf"))
		return;
	for (int i = 0; i < 4; i++)
	{
		menu[i].setFont(font);
		menu[i].setCharacterSize(50);
		if(i>0)
			menu[i].setFillColor(sf::Color::White);
	}
	menu[0].setFillColor(sf::Color::Cyan);
	menu[0].setString("Nowa gra");
	menu[0].setPosition(sf::Vector2f(width / 2.3, height / 3.5));
	menu[1].setString("Najlepsze wyniki");
	menu[1].setPosition(sf::Vector2f(width / 2.3, (height / 3.5) + 180));
	menu[2].setString("Opcje");
	menu[2].setPosition(sf::Vector2f(width / 2.3, (height / 3.5) + 330));
	menu[3].setString("Wyjscie");
	menu[3].setPosition(sf::Vector2f(width / 2.3, (height / 3.5) + 480));
}
void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
	{
		window.draw(menu[i]);
	}
}
void Menu::moveUp()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW) //Poruszaj siê po menu tylko jeœli wybrana opcja jest w zakresie 0-3
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;    //Nastêpuje zmiana. Wskazywany przedmiot jest o jeden mniejszy
		if (selectedItem < 0) //Jeœli wskazywana opcja jest na samej górze to nastêpi przeskok do opcji na samym dole.
			selectedItem = MAX_LICZBA_POZIOMOW - 1;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
}
void Menu::moveDown()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW) //analogicznie jak wy¿ej
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= MAX_LICZBA_POZIOMOW)
			selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
}
/**********************************************************************************WPROWADZENIE NAZWY******************************************************************************/
class WprowadzanieNazwy
{
private:
	sf::Font font;
	sf::Text Napis;
	sf::Text Napis2;
public:
	WprowadzanieNazwy();
	std::string nazwa_gracza = "";
	void draw(sf::RenderWindow &window) { window.draw(Napis); };
	void update(std::string nowa_nazwa) //Funkcja wywo³ywana za ka¿dym razem gdy wciœniêty jest przycisk. Dodaje do stringu jeden znak.
	{
		nazwa_gracza += nowa_nazwa;
		Napis2.setString(nazwa_gracza);
	}
	void draw_nazwe(sf::RenderWindow &window) { window.draw(Napis2); };
};
WprowadzanieNazwy::WprowadzanieNazwy()
{
	if (!font.loadFromFile("Roboto.ttf"))
		return;
	Napis.setFont(font);
	Napis.setFillColor(sf::Color::White);
	Napis.setCharacterSize(50);
	Napis.setString("Podaj nazwe gracza:");
	Napis.setPosition(sf::Vector2f(750, 460));
	Napis2.setFont(font);
	Napis2.setFillColor(sf::Color::White);
	Napis2.setCharacterSize(50);
	Napis2.setPosition(sf::Vector2f(800, 530));
	Napis2.setString(nazwa_gracza);
}
void myDelay(int opoznienie)
{
	sf::Clock zegar;
	sf::Time czas;
	while (1)
	{
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > opoznienie)
		{
			zegar.restart();
			break;
		}
	}
}
/**********************************************************************************PRZECIWNIK******************************************************************************/
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
	void Zaladujteksture1(sf::RenderWindow &window);
	void Zaladujteksture2(sf::RenderWindow &window);
	void Zaladujteksture3(sf::RenderWindow &window);
	void setPosition(float x_in, float y_in);
	int getheight() { return Przeciwnikspr.getTextureRect().height; };
	int getwidth() { return Przeciwnikspr.getTextureRect().width; };
};

Przeciwnik::Przeciwnik(float x_in, float y_in, int a)
{
	if (a == 0)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1SN.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2SN.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3SN.png");
	}
	else if ( a== 1)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1SZ.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2SZ.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3SZ.png");
	}
	else if (a == 2)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1SP.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2SP.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3SP.png");
	}
	else if (a == 3)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1SF.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2SF.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3SF.png");
	}
	else if (a == 4)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1SC.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2SC.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3SC.png");
	}
	else if (a == 5)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1CN.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2CN.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3CN.png");
	}
	else if (a == 6)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1CZ.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2CZ.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3CZ.png");
	}
	else if (a == 7)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1CP.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2CP.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3CP.png");
	}
	else if (a == 8)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1CF.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2CF.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3CF.png");
	}
	else if (a == 9)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1CC.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2CC.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3CC.png");
	}
	else if (a == 10)
	{
		tekstura1.ZaladujTeksture("Tekstura przeciwnika 1", "Przeciwnik1CY.png");
		tekstura2.ZaladujTeksture("Tekstura przeciwnika 2", "Przeciwnik2CY.png");
		tekstura3.ZaladujTeksture("Tekstura przeciwnika 3", "Przeciwnik3CY.png");
	}
	position.x = x_in;
	position.y = y_in;
	Przeciwnikspr.setPosition(position);
}
void Przeciwnik::przesun(float x_in, float y_in)
{
	sf::Vector2f pos;
	pos.x = x_in;
	pos.y = y_in;
	Przeciwnikspr.move(pos);
	position = Przeciwnikspr.getPosition();
}
void Przeciwnik::Zaladujteksture1(sf::RenderWindow &window)
{
	this->Przeciwnikspr.setTexture(this->tekstura1.GetTexture("Tekstura przeciwnika 1"));
	window.draw(Przeciwnikspr);
}
void Przeciwnik::Zaladujteksture2(sf::RenderWindow &window)
{
	this->Przeciwnikspr.setTexture(this->tekstura2.GetTexture("Tekstura przeciwnika 2"));
	window.draw(Przeciwnikspr);
}
void Przeciwnik::Zaladujteksture3(sf::RenderWindow &window)
{
	this->Przeciwnikspr.setTexture(this->tekstura3.GetTexture("Tekstura przeciwnika 3"));
	window.draw(Przeciwnikspr);
}
void Przeciwnik::setPosition(float x_in, float y_in)
{
	sf::Vector2f pos;
	pos.x = x_in;
	pos.y = y_in;
	Przeciwnikspr.setPosition(pos);
}
/**********************************************************************************KABOOM******************************************************************************/
class Kaboom
{
private:
	sf::Vector2f position;
	sf::Clock zegar; // Zegar do odstêpu miêdzy klatkami animacji
	sf::Sprite eksplozja;
public:
	Kaboom(float pos_x, float pos_y);
	sf::Sprite Boom(float deltatime, sf::Texture &tekstura);
	sf::IntRect animacja;
};
Kaboom::Kaboom(float pos_x, float pos_y)
{
	animacja.top = 0;
	animacja.left = 0;
	animacja.width = 128;
	animacja.height = 128;
	position.x = pos_x;
	position.y = pos_y;
}
sf::Sprite Kaboom::Boom(float deltatime, sf::Texture &tekstura) //Funkcja wywo³ywana w ka¿dej klatce programu. Uaktualnia klatkê animacji.
{
	float time = 0.5f, totaltime = 0.0f; //Zmienna time to granica do której d¹¿y zmienna totaltime. Zmienna totaltime jest zwiêkszana co klatkê o delta time.
	eksplozja.setTexture(tekstura);
	eksplozja.setTextureRect(animacja);
	eksplozja.setPosition(position);
	do {
		if (time >= totaltime) // Jeœli totaltime nie przekroczy³o granicy to zmieñ klatkê
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
	} while (animacja.top < 1024 && animacja.left < 1024); //Gdy tekstura dojdzie do krawêdzi pêtla siê przerywa.
	animacja.top = 0;
	animacja.left = 0;
	return eksplozja;
}
/**********************************************************************************SERCA******************************************************************************/
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
	void Rysuj_pelne(sf::RenderWindow &window) { window.draw(serce_pelne); };
	void Rysuj_puste(sf::RenderWindow &window) { window.draw(serce_puste); };
	sf::Vector2f getPos() { return serce_pelne.getPosition(); }
	int getheight() { return serce_pelne.getTextureRect().height; };
	int getwidth() { return serce_pelne.getTextureRect().width; };
	void Zaladujteksture(sf::RenderWindow &window); //Konieczne do lataj¹cych serduszek
};

Serca::Serca(float pos_x, float pos_y)
{
	position.x = pos_x;
	position.y = pos_y;
	tekstura_pelne.ZaladujTeksture("Tekstura serca", "heart_full.png");
	tekstura_puste.ZaladujTeksture("Tekstura pustego serca", "heart_empty.png");
	serce_pelne.setTexture(tekstura_pelne.GetTexture("Tekstura serca"));
	serce_puste.setTexture(tekstura_puste.GetTexture("Tekstura pustego serca"));
	serce_pelne.setPosition(pos_x, pos_y);
	serce_puste.setPosition(pos_x, pos_y);
}
void Serca::przesun(float x, float y)
{
	sf::Vector2f pos;
	pos.x = x;
	pos.y = y;
	serce_pelne.move(pos);
	position = serce_pelne.getPosition();
}
void Serca::Zaladujteksture(sf::RenderWindow &window)
{
	this->serce_pelne.setTexture(this->tekstura_pelne.GetTexture("Tekstura serca"));
	window.draw(serce_pelne);
}
/**********************************************************************************WYNIK******************************************************************************/
class Wynik
{
private:
	sf::Font font;
	sf::Text Napis;
	sf::Text Napis2;
	std::stringstream ssuma;
	Rekord *rekordy;
public:
	Wynik();
	void draw(sf::RenderWindow &window) { window.draw(Napis); window.draw(Napis2); };
	void update();
	void Dodaj_Rekord(std::string nazwa_in, float suma_in);
public:
	float suma = 0;
};

Wynik::Wynik()
{
	if (!font.loadFromFile("Roboto.ttf"))
		return;
	Napis.setFont(font);
	Napis.setFillColor(sf::Color::White);
	Napis.setCharacterSize(30);
	Napis.setString("Wynik:");
	Napis.setPosition(sf::Vector2f(20, 10));
	Napis2.setFont(font);
	Napis2.setFillColor(sf::Color::White);
	Napis2.setCharacterSize(30);
	Napis2.setPosition(sf::Vector2f(110, 10));
	ssuma << suma;
	Napis2.setString(ssuma.str());
}
void Wynik::update()
{
	ssuma.str(std::string());
	ssuma << suma;
	Napis2.setString(ssuma.str());
}
void Wynik::Dodaj_Rekord(std::string nazwa_in, float suma_in)
{
	rekordy = new Rekord();
	rekordy->imie = nazwa_in;
	rekordy->wynik = suma_in;
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	rekordy->dzien = now->tm_mday;
	rekordy->miesiac = now->tm_mon + 1;
	rekordy->rok = now->tm_year + 1900;
	FILE *fp;
	fp = fopen("Rekordy.dat", "a+");
	if (fp == NULL)
		fp = fopen("Rekordy.dat", "w+");
	fwrite(rekordy, sizeof(Rekord), 1, fp);
	fclose(fp);
	delete rekordy;
}
/**********************************************************************************NAJLEPSZE WYNIKI******************************************************************************/
class Najlepsze_wyniki {
private:
	sf::Font font;
	sf::Text Napis[4];
	sf::Text Najlepsze[4][10];
	Rekord *rekordy, *bufor;
	FILE *fp;
	std::stringstream Licznik;
	std::stringstream Bufor1;
	std::stringstream Bufor2;
	std::stringstream Bufor3;
	std::string Imie;
	int liczba_rekordow, szukaj;
public:
	Najlepsze_wyniki();
	~Najlepsze_wyniki() {fclose(fp);}
	void interfejs(sf::RenderWindow &window)
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
	void update();
};

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
	fp = fopen("Rekordy.dat", "r+");
	rekordy = new Rekord[10];
	bufor = new Rekord[10];
	if (fp != NULL)
	{
		fseek(fp, 0, SEEK_END);
		liczba_rekordow = ftell(fp) / sizeof(Rekord);
		rewind(fp);
		do {
			szukaj = 0;
			for (int i = 0; i < liczba_rekordow-1; i++)
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
		fp = fopen("Rekordy.dat", "w+");
	}
}
/**********************************************************************************OPCJE******************************************************************************/
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
	void interfejs(sf::RenderWindow &window)
	{
		for (int i = 0; i < 6; i++)
		{
			window.draw(Napis[i]);
			if (i < 5)
			{
				window.draw(Suwaki[i]);
			}
		}
	}
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

Opcje::Opcje()
{
	if (!font.loadFromFile("Roboto.ttf"))
		return;
	for (int i = 0; i < 6; i++)
	{
		Napis[i].setFont(font);
		Napis[i].setFillColor(sf::Color::White);
		Napis[i].setCharacterSize(50);
		if (i < 5)
		{
			Suwaki[i].setFont(font);
			Suwaki[i].setFillColor(sf::Color::White);
			Suwaki[i].setCharacterSize(50);
			Suwaki[i].setPosition(sf::Vector2f(1300, 300 + (i * 150)));
			if (i < 3)
			{
				Liczby[i] << liczniki[i];
				Suwaki[i].setString(Liczby[i].str());
				Liczby[i].str(std::string(""));
			}
		}
	}
	Napis[0].setString("Opcje");
	Napis[0].setPosition(sf::Vector2f(900, 200));
	Napis[1].setString("Czestotliwosc strzalow przeciwnikow");
	Napis[1].setFillColor(sf::Color::Cyan);
	Napis[1].setStyle(sf::Text::Bold);
	Napis[1].setPosition(sf::Vector2f(100, 300));
	Napis[2].setString("Predkosc pociskow przeciwnikow");
	Napis[2].setPosition(sf::Vector2f(100, 450));
	Napis[3].setString("Czestotliwosc pojawiania sie dodatkowych zyc");
	Napis[3].setPosition(sf::Vector2f(100, 600));
	Napis[4].setString("Kolor statkow przeciwnikow");
	Napis[4].setPosition(sf::Vector2f(100, 750));
	Napis[5].setString("Mnoznik punktow");
	Napis[5].setPosition(sf::Vector2f(100, 900));
	Suwaki[3].setString(Tekstury[0]);
	Liczby[3] << mnoznik;
	Suwaki[4].setString("x" + Liczby[3].str() + ".0");
	Liczby[3].str(std::string(""));
}
void Opcje::moveUp()
{
	if (selectedItem + 1 >= 0 && selectedItem + 1 < MAX_LICZBA_POZIOMOW_OPCJI + 1)
	{
		Napis[selectedItem + 1].setFillColor(sf::Color::White);
		Napis[selectedItem + 1].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = MAX_LICZBA_POZIOMOW_OPCJI - 1;
		Napis[selectedItem + 1].setFillColor(sf::Color::Cyan);
		Napis[selectedItem + 1].setStyle(sf::Text::Bold);
	}
}
void Opcje::moveDown()
{
	if (selectedItem + 1 >= 0 && selectedItem < MAX_LICZBA_POZIOMOW_OPCJI + 1)
	{
		Napis[selectedItem + 1].setFillColor(sf::Color::White);
		Napis[selectedItem + 1].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem + 1 >= MAX_LICZBA_POZIOMOW_OPCJI + 1)
			selectedItem = 0;
		Napis[selectedItem + 1].setFillColor(sf::Color::Cyan);
		Napis[selectedItem + 1].setStyle(sf::Text::Bold);
	}
}
void Opcje::zmiana(int a)
{
	Napis[a + 1].setFillColor(sf::Color::White);
	Napis[a + 1].setStyle(sf::Text::Regular);
	Suwaki[a].setFillColor(sf::Color::Cyan);
	Suwaki[a].setStyle(sf::Text::Bold);
}
void Opcje::powrot(int a)
{
	Napis[a + 1].setFillColor(sf::Color::Cyan);
	Napis[a + 1].setStyle(sf::Text::Bold);
	Suwaki[a].setFillColor(sf::Color::White);
	Suwaki[a].setStyle(sf::Text::Regular);
}
void Opcje::przesuwanie_gora(int a)
{
	if (liczniki[a] >= 1 && liczniki[a] < 6)
	{
		liczniki[a]++;
		Liczby[a] << liczniki[a];
		Suwaki[a].setString(Liczby[a].str());
		Liczby[a].str(std::string(""));
		mnoznik = mnoznik + 0.1;
		Liczby[3] << mnoznik;
		if (mnoznik >= 0.99 && mnoznik <= 1.01)
		{
			Suwaki[4].setString("x" + Liczby[3].str() + ".0");
		}
		else
		{
			Suwaki[4].setString("x" + Liczby[3].str());
		}
		Liczby[3].str(std::string(""));
	}
	if (mnoznik >= 1.89)
	{
		mnoznik = 2;
		Liczby[3] << mnoznik;
		Suwaki[4].setString("x" + Liczby[3].str() + ".0");
		Liczby[3].str(std::string(""));
	}
}
void Opcje::przesuwanie_dol(int a)
{
	if (liczniki[a] > 1 && liczniki[a] <= 6)
	{
		liczniki[a]--;
		Liczby[a] << liczniki[a];
		Suwaki[a].setString(Liczby[a].str());
		Liczby[a].str(std::string(""));
		if (mnoznik >= 2)
		{
			mnoznik = 1.8;
			Liczby[3] << mnoznik;
			Suwaki[4].setString("x" + Liczby[3].str());
			Liczby[3].str(std::string(""));
		}
		else
		{
			mnoznik = mnoznik - 0.1;
			Liczby[3] << mnoznik;
			if (mnoznik >= 0.99 && mnoznik <= 1.01)
			{
				Suwaki[4].setString("x" + Liczby[3].str() + ".0");
			}
			else
			{
				Suwaki[4].setString("x" + Liczby[3].str());
			}
			Liczby[3].str(std::string(""));
		}
	}
}
void Opcje::przesuwanie_gora_kolor(int a)
{
	if (tekstury >= 0 && tekstury < 10)
	{
		tekstury++;
		Suwaki[3].setString(Tekstury[tekstury]);
	}
}
void Opcje::przesuwanie_dol_kolor(int a)
{
	if (tekstury > 0 && tekstury <= 10)
	{
		tekstury--;
		Suwaki[3].setString(Tekstury[tekstury]);
	}
}
/**********************************************************************************ESCAPE******************************************************************************/
class Escape
{
private:
	sf::Font font;
	sf::Text Napis[5];
	sf::Text F1[7];
	std::stringstream Liczba;
	int selectedItem = 0;
public:
	Escape();
	void drukuj_p(sf::RenderWindow &window)
	{
		for (int i = 0; i < 3; i++)
		{
			window.draw(Napis[i]);
		}
	}
	void drukuj_k(sf::RenderWindow &window)
	{
		for (int i = 3; i < 5; i++)
		{
			window.draw(Napis[i]);
		}
	}
	void drukuj_F1(sf::RenderWindow &window)
	{
		for (int i = 0; i < 7; i++)
		{
			window.draw(F1[i]);
		}
	}
	int getSelectedItem() { return selectedItem; }
	bool czy_pauza = false;
	bool czy_F1 = false;
	void moveRight();
	void moveLeft();
	void ustaw_wynik(int wynik) 
	{
		Liczba << wynik;
		Napis[4].setString(Liczba.str());
		Liczba.str(std::string(""));
	}
};

Escape::Escape()
{
	if (!font.loadFromFile("Roboto.ttf"))
		return;
	for (int i = 0; i < 5; i++)
	{
		Napis[i].setFont(font);
		Napis[i].setFillColor(sf::Color::White);
		Napis[i].setCharacterSize(50);
	}
	Napis[0].setPosition(sf::Vector2f(650, 400));
	Napis[0].setString("Czy chcesz zakonczyc rozgrywke?");
	Napis[1].setFillColor(sf::Color::Cyan);
	Napis[1].setStyle(sf::Text::Bold);
	Napis[1].setString("Tak");
	Napis[1].setPosition(sf::Vector2f(800, 460));
	Napis[2].setString("Nie");
	Napis[2].setPosition(sf::Vector2f(1100, 460));
	Napis[3].setString("Twoj wynik to:");
	Napis[3].setPosition(sf::Vector2f(830, 400));
	Napis[4].setPosition(sf::Vector2f(850, 460));
	for (int i = 0; i < 7; i++)
	{
		F1[i].setFont(font);
		F1[i].setFillColor(sf::Color::White);
		F1[i].setCharacterSize(50);
		if (i >= 1)
			F1[i].setPosition(sf::Vector2f(100, 100+(100*i)));
	}
	F1[0].setString("Pomoc");
	F1[0].setPosition(sf::Vector2f(900, 100));
	F1[1].setString("A-> Poruszanie statkiem w lewo");
	F1[2].setString("D-> Poruszanie statkiem w prawo");
	F1[3].setString("Spacja-> Wystrzal");
	F1[4].setString("Celem gry jest zestrzelenie jak najwiekszej liczby przeciwnikow i unikanie ich pociskow.");
	F1[5].setString("Przeciwnicy pozostawiaja czasami serca. Zbieraj je, by zwiekszec liczbe zyc.");
	F1[6].setString("Wcisnij F1, by wylaczyc pomoc.");
}
void Escape::moveRight()
{
	if (selectedItem == 0)
	{
		Napis[selectedItem + 1].setFillColor(sf::Color::White);
		Napis[selectedItem + 1].setStyle(sf::Text::Regular);
		selectedItem++;
		Napis[selectedItem + 1].setFillColor(sf::Color::Cyan);
		Napis[selectedItem + 1].setStyle(sf::Text::Bold);
	}
}
void Escape::moveLeft()
{
	if (selectedItem == 1)
	{
		Napis[selectedItem + 1].setFillColor(sf::Color::White);
		Napis[selectedItem + 1].setStyle(sf::Text::Regular);
		selectedItem--;
		Napis[selectedItem + 1].setFillColor(sf::Color::Cyan);
		Napis[selectedItem + 1].setStyle(sf::Text::Bold);
	}
}
/**********************************************************************************MAIN******************************************************************************/
int main()
{
	sf::Texture Wybuch;
	Wybuch.loadFromFile("explosion.png");
	srand(time(NULL));
	int menu_selected_flag = 0;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Space Invader", sf::Style::Fullscreen);
	Menu menu(window.getSize().x, window.getSize().y);
	Opcje *o1 = new Opcje;
	WprowadzanieNazwy *Wprowadzanie = new WprowadzanieNazwy;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					myDelay(50);
					menu.moveUp();
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					myDelay(50);
					menu.moveDown();
				}
				if (menu_selected_flag == 0)
				{
/**********************************************************************************WPROWADZANIE NAZWY******************************************************************************/
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
					{
						std::string str;
						sf::RenderWindow Imie_gracza(sf::VideoMode(1920, 1080), "Space Invader", sf::Style::Fullscreen);
						Imie_gracza.setFramerateLimit(60);
						while (Imie_gracza.isOpen())
						{
							menu_selected_flag = 1;
							std::string Nazwa = "";
							sf::Event event;
							while (Imie_gracza.pollEvent(event))
							{
								switch (event.type)
								{
								case sf::Event::TextEntered:
									if (event.text.unicode < 128 && event.text.unicode != 13 && event.text.unicode != 8 && Wprowadzanie->nazwa_gracza.length() <= 12 && event.text.unicode != 32)
									{
										Nazwa += static_cast<char>(event.text.unicode);
										Wprowadzanie->update(Nazwa);
									}
									else if (event.text.unicode == 13)
									{
										menu_selected_flag = 0;
										Imie_gracza.close();
									}
									else if (event.text.unicode == 8 && Wprowadzanie->nazwa_gracza.length() > 0)
									{
										Wprowadzanie->nazwa_gracza.pop_back();
										Wprowadzanie->update(Nazwa);
									}
									else if (event.text.unicode == 32){}
									break;
								}
								if (event.key.code == sf::Keyboard::Escape)
								{
									Wprowadzanie->nazwa_gracza = "";
									Imie_gracza.close();
									menu_selected_flag = 0;
								}
							}
							Imie_gracza.clear();
							Imie_gracza.draw(menu.gettlo());
							Wprowadzanie->draw(Imie_gracza);
							Wprowadzanie->draw_nazwe(Imie_gracza);
							Imie_gracza.display();
						}
/*****************************************************************************ROZPOCZÊCIE GRY***********************************************************************************/
						if (Wprowadzanie->nazwa_gracza != "") {
							Escape *e = new Escape;
							Wynik *w1 = new Wynik;
							Serca serce1(1790, 0);
							Serca serce2(1830, 0);
							Serca serce3(1870, 0);
							bool strzelanie = false;
							int licznik = 0;
							Tlo tlo;
							Gracz gracz1(900, 950);
							std::vector<Strzal> pociskvec;
							std::vector<Strzal> pociskvecp;
							std::vector <Przeciwnik>  tablica;
							std::vector <Kaboom *>  wybuchy;
							std::vector<Serca> serca;
							int a;
							sf::Clock zegar;
							sf::Clock zegar2;
							sf::Clock zegar3;
							float deltatime = 0.0f;
							bool Czy_A_wcisniete = false;
							bool Czy_D_wcisniete = false;
							bool Czy_Space_wcisniete = false;
							int czas = 700;
							Przeciwnik *widmo = new Przeciwnik(100, 0, 1);
							sf::RenderWindow Gra(sf::VideoMode(1920, 1080), "Space Invader", sf::Style::Fullscreen);
							Gra.setFramerateLimit(60);
							while (Gra.isOpen())
							{
								deltatime = zegar3.restart().asSeconds();
								sf::Event event;
								while (Gra.pollEvent(event))
								{
/*************************************************************************STEROWANIE, WCISKANIE GUZIKÓW***************************************************************************************/
									switch (event.type)
									{
									case sf::Event::KeyPressed:
										if (event.key.code == sf::Keyboard::A)
											Czy_A_wcisniete = true;
										else if (event.key.code == sf::Keyboard::D)
											Czy_D_wcisniete = true;
										else if (event.key.code == sf::Keyboard::Space)
											Czy_Space_wcisniete = true;
										break;
									case sf::Event::KeyReleased:
										if (event.key.code == sf::Keyboard::A)
											Czy_A_wcisniete = false;
										else if (event.key.code == sf::Keyboard::D)
											Czy_D_wcisniete = false;
										else if (event.key.code == sf::Keyboard::Space)
											Czy_Space_wcisniete = false;
										break;
									default:
										break;
									}
									if (event.key.code == sf::Keyboard::Escape)
									{
										e->czy_pauza = true;
									}
									else if (event.key.code == sf::Keyboard::Right && e->czy_pauza==true)
									{
										myDelay(50);
										e->moveRight();
									}
									else if (event.key.code == sf::Keyboard::Left && e->czy_pauza == true)
									{
										myDelay(50);
										e->moveLeft();
									}
									else if (event.key.code == sf::Keyboard::Enter && e->czy_pauza == true && e->getSelectedItem() == 0 && gracz1.Zycia != 0 && e->czy_F1==false)
									{
										w1->Dodaj_Rekord(Wprowadzanie->nazwa_gracza, w1->suma);
										menu_selected_flag = 0;
										Gra.close();
									}
									else if (event.key.code == sf::Keyboard::Enter && e->czy_pauza == true && e->getSelectedItem() == 1 && gracz1.Zycia != 0 && e->czy_F1 == false)
									{
										e->czy_pauza = false;
									}
									else if (event.key.code == sf::Keyboard::Enter && e->czy_pauza == true && gracz1.Zycia == 0)
									{
										w1->Dodaj_Rekord(Wprowadzanie->nazwa_gracza, w1->suma);
										menu_selected_flag = 0;
										Gra.close();
										e->czy_pauza = false;
									}
									else if (event.key.code == sf::Keyboard::F1 && e->czy_pauza == false && e->czy_F1 == false && czas>600)
									{
										e->czy_pauza = true;
										e->czy_F1 = true;
										czas = 0;
										break;
									}
									else if (event.key.code == sf::Keyboard::F1 && e->czy_pauza == true && e->czy_F1 == true && czas>600)
									{
										czas = 0;
										e->czy_pauza = false;
										e->czy_F1 = false;
										break;
									}
								}
									czas = czas + zegar.getElapsedTime().asMilliseconds();
/****************************************************************************STEROWANIE STATKIEM************************************************************************************/
								if (e->czy_pauza == false)
								{
									if (Czy_A_wcisniete == true && Czy_D_wcisniete == false && Czy_Space_wcisniete == false && gracz1.getPos().x >= 15)
									{
										gracz1.przesun(-10, 0);
									}
									if (Czy_A_wcisniete == true && Czy_D_wcisniete == false && Czy_Space_wcisniete == true && gracz1.getPos().x >= 15)
									{
										if (zegar2.getElapsedTime().asMilliseconds() > 300.0f) {
											strzelanie = true;
											zegar2.restart();
										}
										gracz1.przesun(-10, 0);
									}
									if (Czy_A_wcisniete == false && Czy_D_wcisniete == true && Czy_Space_wcisniete == false && gracz1.getPos().x <= 1785)
									{
										gracz1.przesun(10, 0);
									}
									if (Czy_A_wcisniete == false && Czy_D_wcisniete == true && Czy_Space_wcisniete == true && gracz1.getPos().x <= 1785)
									{
										if (zegar2.getElapsedTime().asMilliseconds() > 300.0f) {
											strzelanie = true;
											zegar2.restart();
										}
										gracz1.przesun(10, 0);
									}
									if (Czy_A_wcisniete == false && Czy_D_wcisniete == false && Czy_Space_wcisniete == true)
									{
										if (zegar2.getElapsedTime().asMilliseconds() > 300.0f) {
											strzelanie = true;
											zegar2.restart();
										}
									}
									if (Czy_A_wcisniete == true && Czy_D_wcisniete == true && Czy_Space_wcisniete == true)
									{
										if (zegar2.getElapsedTime().asMilliseconds() > 300.0f) {
											strzelanie = true;
											zegar2.restart();
										}
									}
/**********************************************************************TWORZENIE TABLIC PRZECIWNIKÓW******************************************************************************************/
									if (tablica.size() <= 0)
									{
										licznik = 0;
										widmo->setPosition(100, 0);
										for (int i = 0; i < 11; i++)
										{
											for (int j = 0; j < 4; j++)
											{
												a = rand() % 3;
												if (a == 0)
												{
													Przeciwnik przeciwnik(150 + (150 * (i)), -440 + (120 * (j)), o1->tekstury);
													przeciwnik.Rodzaj = 1;
													tablica.push_back(przeciwnik);
												}
												else if (a == 1)
												{
													Przeciwnik przeciwnik(150 + (150 * (i)), -440 + (120 * (j)), o1->tekstury);
													przeciwnik.Rodzaj = 2;
													tablica.push_back(przeciwnik);
												}
												else if (a == 2)
												{
													Przeciwnik przeciwnik(150 + (150 * (i)), -440 + (120 * (j)), o1->tekstury);
													przeciwnik.Rodzaj = 3;
													tablica.push_back(przeciwnik);
												}
											}
										}
									}
								}
/**************************************************************************RYSOWANIE T£A I GRACZA**************************************************************************************/
									Gra.clear();
									Gra.draw(tlo.gettlo1());
									Gra.draw(tlo.gettlo2());
									Gra.draw(gracz1.getGracz());
/***************************************************************************WYSTRZELIWANIE POCISKOW PRZECIWNIKA*************************************************************************************/
									for (unsigned int i = 0; i < tablica.size(); i++)
									{
										int wspolczynnik = 1200 / (o1->liczniki[0] / o1->liczniki[0] + (0.4*o1->liczniki[0] - 1));
										if (tablica.size() < 33)
										{
											wspolczynnik = (wspolczynnik / 4) * 3;
										}
										else if (tablica.size() < 22)
										{
											wspolczynnik = (wspolczynnik / 4) * 2;
										}
										else if (tablica.size() < 11)
										{
											wspolczynnik = (wspolczynnik / 4);
										}
										else
										{
											wspolczynnik = 1500 / (o1->liczniki[0]);
										}
										int a = rand() % wspolczynnik;
										if (tablica[i].Rodzaj == 1)
										{
											tablica[i].Zaladujteksture1(Gra);
											if (a == 0 && e->czy_pauza == false)
											{
												Strzal strzal(tablica[i].getPos().x + 45, tablica[i].getPos().y + 100);
												strzal.Rodzaj = 1;
												pociskvecp.push_back(strzal);
											}
										}
										if (tablica[i].Rodzaj == 2)
										{
											tablica[i].Zaladujteksture2(Gra);
											if (a == 0 && e->czy_pauza == false)
											{
												Strzal strzal(tablica[i].getPos().x + 45, tablica[i].getPos().y + 80);
												strzal.Rodzaj = 2;
												pociskvecp.push_back(strzal);
											}
										}
										if (tablica[i].Rodzaj == 3)
										{
											tablica[i].Zaladujteksture3(Gra);
											if (a == 0 && e->czy_pauza == false)
											{
												Strzal strzal(tablica[i].getPos().x + 45, tablica[i].getPos().y + 80);
												strzal.Rodzaj = 3;
												pociskvecp.push_back(strzal);
											}
										}
/***********************************************************************RUCH PRZECIWNIKÓW*****************************************************************************************/
										if(e->czy_pauza==false)
										{
											if (widmo->getPos().y <= 540 && licznik == 0)
											{
												tablica[i].przesun(0, 1);
											}
											else if (widmo->getPos().y > 540 && widmo->getPos().x >= 0 && licznik == 1)
											{
												tablica[i].przesun(-1, 0);
											}
											else if (licznik == 2 && widmo->getPos().x <= 200)
											{
												tablica[i].przesun(1, 0);
											}
											else if (licznik == 3 && widmo->getPos().x >= 100)
											{
												tablica[i].przesun(-1, 0);
											}
											else if (licznik == 4 && widmo->getPos().y <= 740)
											{
												tablica[i].przesun(0, 1);
											}
											else if (licznik == 5 && widmo->getPos().x <= 200)
											{
												tablica[i].przesun(1, 0);
											}
											else if (licznik == 6 && widmo->getPos().x >= 0)
											{
												tablica[i].przesun(-1, 0);
											}
										}
									}
									if (e->czy_pauza == false)
									{
										if (widmo->getPos().y >= 0 && widmo->getPos().y <= 540 && licznik == 0)
										{
											widmo->przesun(0, 1);
											if (widmo->getPos().y == 541)
												licznik++;
										}
										else if (widmo->getPos().y > 540 && widmo->getPos().x >= 0 && licznik == 1)
										{
											widmo->przesun(-1, 0);
											if (widmo->getPos().x == -1)
												licznik++;
										}
										else if (licznik == 2 && widmo->getPos().x <= 200)
										{
											widmo->przesun(1, 0);
											if (widmo->getPos().x == 201)
												licznik++;
										}
										else if (licznik == 3 && widmo->getPos().x >= 100)
										{
											widmo->przesun(-1, 0);
											if (widmo->getPos().x == 99)
												licznik++;
										}
										else if (licznik == 4 && widmo->getPos().y <= 740)
										{
											widmo->przesun(0, 1);
											if (widmo->getPos().y == 741)
												licznik++;
										}
										else if (licznik == 5 && widmo->getPos().x <= 200)
										{
											widmo->przesun(1, 0);
											if (widmo->getPos().x == 201)
												licznik++;
										}
										else if (licznik == 6 && widmo->getPos().x >= 0)
										{
											widmo->przesun(-1, 0);
											if (widmo->getPos().x == -1)
												licznik--;
										}
									}
/******************************************************************************STRZELANIE GRACZA**********************************************************************************/
									if (strzelanie == true)
									{
										Strzal pocisk(gracz1.getPos().x + 53, gracz1.getPos().y);
										pociskvec.push_back(pocisk);
										strzelanie = false;
									}
									for (unsigned int i = 0; i < pociskvec.size(); i++)
									{
										bool czy_trafiony = false;
										pociskvec[i].getPocisk();
										pociskvec[i].rysuj(Gra);
										for (int j = 0; j < tablica.size(); j++)
										{
											if (pociskvec[i].getPos().y <= tablica[j].getPos().y + tablica[j].getheight() && pociskvec[i].getPos().y >= tablica[j].getPos().y && pociskvec[i].getPos().x >= tablica[j].getPos().x - 21 && pociskvec[i].getPos().x <= tablica[j].getPos().x + tablica[j].getwidth())
											{
												tlo.dzwiek1();
												int wspolczynnik = 10 + (o1->liczniki[2] * 10);
												int a = rand() % wspolczynnik;
												if (a == 0)
												{
													Serca serce(tablica[j].getPos().x + 40, tablica[j].getPos().y + 20);
													serca.push_back(serce);
												}
												Kaboom *wybuch = new Kaboom(tablica[j].getPos().x, tablica[j].getPos().y);
												wybuchy.push_back(wybuch);
												tablica.erase(tablica.begin() + j);
												czy_trafiony = true;
												j = tablica.size();
												w1->suma = w1->suma + (10 * o1->mnoznik);
												w1->update();
											}
										}
										if (i == 0) {
											pociskvec[i].dzwiek();
										}
										if (e->czy_pauza == false)
										{
											pociskvec[i].przesun(0, -30);
										}
										if (pociskvec[i].getPos().y <= -10 || czy_trafiony == true)
										{
											pociskvec.erase(pociskvec.begin());
										}
									}
/*****************************************************************************RUCH SPADAJ¥CYCH SERDUSZEK***********************************************************************************/
									for (int i = 0; i < serca.size(); i++)
									{
										serca[i].Zaladujteksture(Gra);
										if (e->czy_pauza == false)
										{
											serca[i].przesun(0, 10);
										}
										if ((serca[i].getPos().y >= gracz1.getPos().y - serca[i].getheight() && serca[i].getPos().x >= gracz1.getPos().x - serca[i].getwidth() && serca[i].getPos().x <= gracz1.getPos().x + gracz1.getwidth())
											|| (serca[i].getPos().y > 1080))
										{
											if (serca[i].getPos().y >= gracz1.getPos().y - serca[i].getheight() && serca[i].getPos().x >= gracz1.getPos().x - serca[i].getwidth() && serca[i].getPos().x <= gracz1.getPos().x + gracz1.getwidth() && gracz1.Zycia < 3)
											{
												gracz1.Zycia++;
												tlo.dzwiek3();
											}
											serca.erase(serca.begin() + i);
										}
									}
/***********************************************************************POCISKI PRZECIWNIKOW*****************************************************************************************/
									for (unsigned int i = 0; i < pociskvecp.size(); i++)
									{
										pociskvecp[i].getPocisk();
										pociskvecp[i].rysuj(Gra);
										float predkosc = 6 + o1->liczniki[1];
										if (e->czy_pauza==false)
										{
											if (pociskvecp[i].Rodzaj == 1)
											{
												pociskvecp[i].przesun(0, predkosc);
											}
											if (pociskvecp[i].Rodzaj == 2 && pociskvecp[i].czy_odbity == false)
											{
												pociskvecp[i].przesun(predkosc / sqrt(2), predkosc / sqrt(2));
												if (pociskvecp[i].getPos().x >= 1920 - pociskvecp[i].getwidth())
												{
													pociskvecp[i].czy_odbity = true;
												}
											}
											if (pociskvecp[i].Rodzaj == 2 && pociskvecp[i].czy_odbity == true)
											{
												pociskvecp[i].przesun(-predkosc / sqrt(2), predkosc / sqrt(2));
											}
											if (pociskvecp[i].Rodzaj == 3 && pociskvecp[i].czy_odbity == false)
											{
												pociskvecp[i].przesun(-predkosc / sqrt(2), predkosc / sqrt(2));
												if (pociskvecp[i].getPos().x <= 0)
												{
													pociskvecp[i].czy_odbity = true;
												}
											}
											if (pociskvecp[i].Rodzaj == 3 && pociskvecp[i].czy_odbity == true)
											{
												pociskvecp[i].przesun(predkosc / sqrt(2), predkosc / sqrt(2));
											}
										}
										if ((pociskvecp[i].getPos().y >= gracz1.getPos().y - pociskvecp[i].getheight() && pociskvecp[i].getPos().x >= gracz1.getPos().x - pociskvecp[i].getwidth() && pociskvecp[i].getPos().x <= gracz1.getPos().x + gracz1.getwidth())
											|| (pociskvecp[i].getPos().y > 1080))
										{
											if (pociskvecp[i].getPos().y >= gracz1.getPos().y - pociskvecp[i].getheight() && pociskvecp[i].getPos().x >= gracz1.getPos().x - pociskvecp[i].getwidth() && pociskvecp[i].getPos().x <= gracz1.getPos().x + gracz1.getwidth())
											{
												tlo.dzwiek2();
												gracz1.Zycia--;
											}
											pociskvecp.erase(pociskvecp.begin() + i);
										}
									}
									w1->draw(Gra);
/*********************************************************************************WYBUCHY*******************************************************************************/
									for (unsigned int i = 0; i < wybuchy.size(); i++)
									{
										Gra.draw(wybuchy[i]->Boom(deltatime, Wybuch));
										if (wybuchy.size() > 5)
										{
											wybuchy.erase(wybuchy.begin());
										}
									}
/*********************************************************************************¯YCIA*******************************************************************************/
									if (gracz1.Zycia == 3)
									{
										serce1.Rysuj_pelne(Gra);
										serce2.Rysuj_pelne(Gra);
										serce3.Rysuj_pelne(Gra);
									}
									else if (gracz1.Zycia == 2)
									{
										serce1.Rysuj_pelne(Gra);
										serce2.Rysuj_pelne(Gra);
										serce3.Rysuj_puste(Gra);
									}
									else if (gracz1.Zycia == 1)
									{
										serce1.Rysuj_pelne(Gra);
										serce2.Rysuj_puste(Gra);
										serce3.Rysuj_puste(Gra);
									}
									else if (gracz1.Zycia == 0)
									{
										serce1.Rysuj_puste(Gra);
										serce2.Rysuj_puste(Gra);
										serce3.Rysuj_puste(Gra);
										e->czy_pauza = true;
									}
/********************************************************************************T£O I PAUZY********************************************************************************/
									if (zegar.getElapsedTime().asMilliseconds() > 5.0f && e->czy_pauza==false) {
										tlo.przesun(0, 1);
										zegar.restart();
									}
									if (tlo.getPos1().y >= 1080)
									{
										tlo.przesuntlo1();
									}
									if (tlo.getPos2().y >= 1080)
									{
										tlo.przesuntlo2();
									}
								if (e->czy_pauza == true && gracz1.Zycia != 0 && e->czy_F1 == false)
								{
									e->drukuj_p(Gra);
								}
								else if(e->czy_pauza == true && gracz1.Zycia == 0 && e->czy_F1 == false)
								{
									e->ustaw_wynik(w1->suma);
									e->drukuj_k(Gra);
								}
								else if (e->czy_pauza == true && gracz1.Zycia != 0 && e->czy_F1 == true)
								{
									e->drukuj_F1(Gra);
								}
								Gra.display();
							}
						}
					}
/**************************************************************************************NAJLEPSZE WYNIKI**************************************************************************/
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
					{
						Najlepsze_wyniki *najlepsze_w = new Najlepsze_wyniki;
						najlepsze_w->update();
						sf::RenderWindow Najlepsze(sf::VideoMode(1920, 1080), "Space Invader", sf::Style::Fullscreen);
						Najlepsze.setFramerateLimit(60);
						while (Najlepsze.isOpen())
						{
							menu_selected_flag = 1;
							sf::Event event;
							while (Najlepsze.pollEvent(event))
							{
								if (event.key.code == sf::Keyboard::Escape)
								{
									menu_selected_flag = 0;
									Najlepsze.close();
								}
							}
							Najlepsze.clear();
							Najlepsze.draw(menu.gettlo());
							najlepsze_w->interfejs(Najlepsze);
							Najlepsze.display();
						}
						delete najlepsze_w;
					}
/**********************************************************************************OPCJE******************************************************************************/
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
					{
						int opcja_selected_flag = 0;
						sf::RenderWindow Opcje(sf::VideoMode(1920, 1080), "Space Invader", sf::Style::Fullscreen);
						Opcje.setFramerateLimit(60);
						sf::Clock Zegar;
						int czas = 0;
						while (Opcje.isOpen())
						{
							menu_selected_flag = 1;
							sf::Event event;
							if (opcja_selected_flag == 1)
							{
								czas = czas + Zegar.getElapsedTime().asMilliseconds();
							}
							while (Opcje.pollEvent(event))
							{
								if (event.key.code == sf::Keyboard::Escape && opcja_selected_flag == 0)
								{
									menu_selected_flag = 0;
									Opcje.close();
								}
								if (event.type == sf::Event::KeyPressed)
								{
									if (event.key.code == sf::Keyboard::Up && opcja_selected_flag == 0)
									{
										myDelay(50);
										o1->moveUp();
									}
									if (event.key.code == sf::Keyboard::Down && opcja_selected_flag == 0)
									{
										myDelay(50);
										o1->moveDown();
									}

									if (event.key.code == sf::Keyboard::Enter && o1->getSelectedItem() == 0 && opcja_selected_flag == 0)
									{
										o1->zmiana(o1->getSelectedItem());
										opcja_selected_flag = 1;
									}
									if (event.key.code == sf::Keyboard::Enter && o1->getSelectedItem() == 1 && opcja_selected_flag == 0)
									{
										o1->zmiana(o1->getSelectedItem());
										opcja_selected_flag = 1;
									}
									if (event.key.code == sf::Keyboard::Enter && o1->getSelectedItem() == 2 && opcja_selected_flag == 0)
									{
										o1->zmiana(o1->getSelectedItem());
										opcja_selected_flag = 1;
									}
									if (event.key.code == sf::Keyboard::Enter && o1->getSelectedItem() == 3 && opcja_selected_flag == 0)
									{
										o1->zmiana(o1->getSelectedItem());
										opcja_selected_flag = 1;
									}

									if (event.key.code == sf::Keyboard::Enter && o1->getSelectedItem() == 0 && opcja_selected_flag == 1 && czas > 1)
									{
										czas = 0;
										o1->powrot(o1->getSelectedItem());
										opcja_selected_flag = 0;
									}
									if (event.key.code == sf::Keyboard::Enter && o1->getSelectedItem() == 1 && opcja_selected_flag == 1 && czas > 1)
									{
										czas = 0;
										o1->powrot(o1->getSelectedItem());
										opcja_selected_flag = 0;
									}
									if (event.key.code == sf::Keyboard::Enter && o1->getSelectedItem() == 2 && opcja_selected_flag == 1 && czas > 1)
									{
										czas = 0;
										o1->powrot(o1->getSelectedItem());
										opcja_selected_flag = 0;
									}
									if (event.key.code == sf::Keyboard::Enter && o1->getSelectedItem() == 3 && opcja_selected_flag == 1 && czas > 1)
									{
										czas = 0;
										o1->powrot(o1->getSelectedItem());
										opcja_selected_flag = 0;
									}

									if (event.key.code == sf::Keyboard::Up && opcja_selected_flag == 1 && o1->getSelectedItem() == 0)
									{
										o1->przesuwanie_gora(o1->getSelectedItem());
										myDelay(50);
									}
									if (event.key.code == sf::Keyboard::Down && opcja_selected_flag == 1 && o1->getSelectedItem() == 0)
									{
										o1->przesuwanie_dol(o1->getSelectedItem());
										myDelay(50);
									}
									if (event.key.code == sf::Keyboard::Up && opcja_selected_flag == 1 && o1->getSelectedItem() == 1)
									{
										o1->przesuwanie_gora(o1->getSelectedItem());
										myDelay(50);
									}
									if (event.key.code == sf::Keyboard::Down && opcja_selected_flag == 1 && o1->getSelectedItem() == 1)
									{
										o1->przesuwanie_dol(o1->getSelectedItem());
										myDelay(50);
									}
									if (event.key.code == sf::Keyboard::Up && opcja_selected_flag == 1 && o1->getSelectedItem() == 2)
									{
										o1->przesuwanie_gora(o1->getSelectedItem());
										myDelay(50);
									}
									if (event.key.code == sf::Keyboard::Down && opcja_selected_flag == 1 && o1->getSelectedItem() == 2)
									{
										o1->przesuwanie_dol(o1->getSelectedItem());
										myDelay(50);
									}
									if (event.key.code == sf::Keyboard::Up && opcja_selected_flag == 1 && o1->getSelectedItem() == 3)
									{
										o1->przesuwanie_gora_kolor(o1->getSelectedItem());
										myDelay(50);
									}
									if (event.key.code == sf::Keyboard::Down && opcja_selected_flag == 1 && o1->getSelectedItem() == 3)
									{
										o1->przesuwanie_dol_kolor(o1->getSelectedItem());
										myDelay(50);
									}
								}
							}
							Opcje.clear();
							Opcje.draw(menu.gettlo());
							o1->interfejs(Opcje);
							Opcje.display();
						}
/****************************************************************************************************************************************************************/
					}
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 3)
					{
						window.close();
					}
				}
			}
		}
		window.clear();
		window.draw(menu.gettlo());
		if (menu_selected_flag == 0)
		menu.draw(window);
		window.display();
	}
	return 0;
}