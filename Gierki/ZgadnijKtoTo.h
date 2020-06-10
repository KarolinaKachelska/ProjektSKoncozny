#ifndef ZgadnijKtoTo_h
#define ZgadnijKtoTo_h
#include <iostream>
#include<string>
#include"Gracz.h"
#include "Wirtualna.h"
using namespace std;


class ZgadnijKtoTo : public Wirtualna
{
private:

	string odpA;
	string odpB;
	string odpC;
	string tablica[33];

public:
	//konstrunktor
	ZgadnijKtoTo();
	//destruktor
	~ZgadnijKtoTo();

	/////////////////
	//funkcja ktora na poczatku gry tworzy ranking
	void StworzRanking();
	// funkcja w ktorej jest prowadzona rozgrywka
	void graj();
	// funkcja ktora zapisuje punkty po grze do pliku .txt
	void zapiszPunkty();
	/////////////////
	// program wybiera postac, ktora uzytkownik bedzie zgadywal
	void WybierzPostac(int los);
	// program wybiera dwie dodatkowe odpowiedzi
	string WybierzDodatkowa(int los2);
	// program tutaj losuje kolejnosc wyswietlania odpowiedzi, by dobra odpowiedz nei byla zawsze w tym samym miejscu
	void losujKolejnoscOdpowiedzi(string odp2, string odp3);
	// funkcja wyswietlajaca mozliwe pytania
	void WyswietlPytania();
	//wyswietla odpowiedz na zadane pytanie
	void WybierzPytanie(int pyt);
	// funkcja ktora sprawdza czy odpowiedz to litera czy numer pytania i ktora w zaleznosci od typu odpowiedzi 
	//sprawdza koncowa odpowiedz, badz wyswietla odpowiedz na zadane pytanie (przekierowujac do funkcji ktora to robi)
	bool SprawdzOdpowiedz(char pyt, int int_pyt);

};




#endif

