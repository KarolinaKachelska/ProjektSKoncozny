#ifndef wirtualna_h
#define wirtualna_h
#include <iostream>
#include<string>
#include"Gracz.h"
#include "end.h"
#include "Struktury.h"
using namespace std;



class Wirtualna : public End, public Gracz {
public:
	string NazwaPliku;
	Ranking* pRanking;
	//kontruktor
	Wirtualna();
	//destruktor
	~Wirtualna();

	//wirtualna funkcja tworzaca ranking
	virtual void StworzRanking() {};
	// wirtualna funkcja zapisujaca punkty po kazdej grze
	virtual void zapiszPunkty() {};
	// wirtualna funkcja G£ÓWNA (tu siê rozgrywa ca³a rozgrywka)
	virtual void graj() {};
};


#endif
