#ifndef end_h
#define end_h
#include <iostream>
#include<string>
#include"Gracz.h"
using namespace std;


class End {

public:
	//funkcja utwarza ranking, który jest zapisywany jako plik .txt
	void DodajDoRankingu(Ranking*& pRanking, string nick, int punkty);
	//funkcja dodaje wynik do rankingu , który jest zapisywany jako plik .txt
	void ZapiszRanking(Ranking* Helper, string NazwaPliku);
	// funkcja koncowa, wystepuje po kazdej grze i wyswietla ranking dla uzytkownika ( zapisuje rozniez punkty do rankingu i do katalogu gracza)
	void TheEnd(string nick, int punkty, Ranking* pRanking, string NazwaPliku);
	// funkcja sprawdza czy dany wynik jest lepszy od ktoregos z rankingu
	void RekrutacjaDoRankingu(Ranking*& pRanking, int i, int punkty, string nick);
	// usuwanie rankingu ( na koniec programu )
	void popfrontRanking(Ranking*& pRanking);
	// funkcja zmienia znak z malej na duza litere
	string ZmienZnak(string znak);
	// funkcja wywolywana w TheEnd, wynisuje ona ranking na ekran
	void Wypisz(string pkt, Ranking* pRanking);

};

#endif

