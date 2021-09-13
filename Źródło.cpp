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

#include "External.h""
#include "TextureManager.h"
#include "T³o.h"
#include "Gracz.h"
#include "Strza³.h"
#include "Menu.h"
#include "WprowadzanieNazwy.h"
#include "Przeciwnik.h"
#include "Kaboom.h"
#include "Serce.h"
#include "Wynik.h"
#include "Rekord.h"
#include "Najlepsze_Wyniki.h"
#include "Opcje.h"
#include "Escape.h"

void myDelay(int opoznienie);

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