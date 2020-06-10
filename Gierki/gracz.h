
#ifndef gracz_h
#define gracz_h
#include <iostream>
#include<string>
#include <fstream>
#include<vector>
#include <windows.h> // funk. Sleep()
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "Struktury.h"

using namespace std;


class Gracz
{
public:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* kolejka;
	
	

protected:
	
	List* pList;
	
public:
	string nick;
	int punkty;
	string nazwa;
	//konstruktor
	Gracz();
	//destruktor
	~Gracz();
	// funkcja czyta liste uzytkownikow
	void ReadList();
	// funkcja tworzy liste uzytkownikow
	void MakeAList(List*& pList, string nick);
	// funkcja ktora prowadzi interakcje z uzywkownikiem ( albo przekierowywuje do zalogowania sie albo do zarejestrowania )
	void Formularz();
	// tutaj nowy uzytkownik sie rejestruje
	void ZarejestrujSie();
	// tutaj sie logujemy na wlasnie konto
	void ZalogujSie();
	// funkcja wykorzystywana w "zaloguj sie" i "zarejestruj sie" - sprawdza czy nick istnieje w bazie
	bool SprawdzamNick(string nick, List*& pList);
	// funkcja uzywana w "zarejestruj sie" - zapisuje nick do bazy 
	void SaveNick(string nick);
	// glowne menu, gdzie uzytkownik wybiera jaka czynnosc chce wykonac w tym programie
	bool UserMenu();
	// funkcja wypisuje punkty z histori gier uzytkownika
	void wypiszPunkty();
	// usuwanie listy nickow
	void popfrontList();
	// funkcja wykozystywana w "user menu", wypisuje kominikat na ekran
	void Show();
	// funkcja wykorzystywana w "user menu" - za pomoca tej funkcji wybieramy z klawiatury gre badz inna czynnosc
	int Write();
	// funkcja wykorzystywana w "zaloguj sie" i "zarejestruj sie" - wpisuje sie tu nick
	string WpiszNick();
};




#endif
