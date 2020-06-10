#ifndef Familiada_h
#define Familiada_h
#include <iostream>
#include<string>
#include"Gracz.h"
#include "Wirtualna.h"
using namespace std;


class Familiada : public Wirtualna
{
private:

	string odp;


public:
	//tablica do przochowywania 5 mozliwych odpowiedzi
	string tablica[5];
	//konstrunktor
	Familiada();
	//destruktor
	~Familiada();

	////////////
	// funkcja w ktorej jest prowadzona rozgrywka
	void graj();
	//funkcja ktora na poczatku gry tworzy ranking
	void StworzRanking();
	// funkcja ktora zapisuje punkty po grze do pliku .txt
	void zapiszPunkty();
	///////////////
	// funkcja losuje pytania z bazy danych  (.txt)
	void losuj();
	// funkcja sprawdza czy wpisana odpowiedz istnieje w tablicy z odpowiedziami
	void Sprawdz();


};

#endif

