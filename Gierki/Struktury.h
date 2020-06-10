#ifndef struktury_h
#define struktury_h
#include <iostream>
#include<string>

using namespace std;




struct List {
	// Lista jednokierunkowa do zapisu i odczytu nicków

	string nick;
	List* pNext;
};

struct Tree {  //beda tu zapisane nazwy panst i miast
	// lista jednokierunkowa do zapisu i odczytu Panstw/Miast
	Tree* pNext;

	string nazwa_P_M;

};

struct Ranking { // trzyma ranking z WSZYSTKICH GIER tych list  bedzie tyle ile gier
	//lista jednokierunkowa do zapisu i odczytu Rankingu Gier (kazda gra ma swoj wlasny ranking ) 
	string nick;
	int punkty;

	Ranking* pNext;


};

#endif

