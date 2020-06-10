#ifndef PanstwaMiasta_h
#define PanstwaMiasta_h
#include <iostream>
#include<string>
#include "Wirtualna.h"
using namespace std;


class PanstwaMiasta : public Wirtualna
{
private:
	Tree* pHead;
	Tree* pHead2;


public:
	//konstrunktor
	PanstwaMiasta();
	//destruktor
	~PanstwaMiasta();

	////////////////////////
	//funkcja ktora na poczatku gry tworzy ranking
	void StworzRanking();
	// funkcja w ktorej jest prowadzona rozgrywka
	void graj();
	// funkcja ktora zapisuje punkty po grze do pliku .txt
	void zapiszPunkty();
	/////////////////////
	// czyta plik .txt z nazwami Panstw/Miast
	void czytajPlik(Tree*& pHead, string nazwaPliku);
	// tworzy liste (poczatkowo mialo byc drzewo st¹d ta nazwa) nazw Panstw/Miast
	void dodajDrzewo(Tree*& pHead, string slowo);
	// Sprawdza czy istnieje wpisane panstwo
	bool sprawdzP(Tree* pHead, char litera);
	// Sprawdza czy istnieje wpisane misto
	bool sprawdzM(Tree* pHead, char litera);
	// tutaj uzytkownik wpisuje nazwe Miasta
	void wpiszNazweM(char literka);
	// tutaj uzytkownik wpisuje nazwe Panstwa
	void wpiszNazweP(char literka);
	// usuwa liste Panstw
	void popfrontTree2();
	// usuwa liste Miast
	void popfrontTree();
	// uzytkownik tutaj wprowadza odpowiedz na pytanie czy chce grac dalej 
	bool Odpowiedz();
};






#endif
