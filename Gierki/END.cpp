#include <iostream>
#include<string>
#include <fstream>
#include <iomanip>
#include <windows.h> // funk. Sleep()
#include "end.h"


void End::DodajDoRankingu(Ranking*& pRanking, string nick, int punkty)
{
	if (!pRanking) pRanking = new Ranking{ nick,punkty,nullptr }; // jezeli pusty to dodaj
	else
	{
		return DodajDoRankingu(pRanking->pNext, nick, punkty); // jezeli nie to przewin dalej
	}

}

string End::ZmienZnak(string znak)
{
	if (znak[0] > 95) // zmieniamy mala litere na duza
	{
		znak[0] = znak[0] - 32;
	}

	return znak;
}

void End::ZapiszRanking(Ranking* View, string NazwaPliku)
{

	string ss;


	ofstream zapis;
	zapis.open(NazwaPliku, ios::out | ios::trunc); // otwieramy plik .txt
	try {
		if (zapis.good() == true) // jezeli ok to..
		{


			while (View != nullptr && View->nick != "") 
			{
				zapis << View->nick << " " << View->punkty << endl; // zapisz nick i punkty od gracza
				View = View->pNext; // a nastepnie przejdz do nastepnego

			}

			zapis.close(); // zamknij

		}


		else
		{
			throw ss; // wyrzuc watek  jesli nie jest ok 
		}
	}
	catch (string) // i teraz go zlap 
	{
		cout << "Blad odczytu pliku" << endl; // error ?
		Sleep(1000);
		system("cls");
		exit(5);
	}

}

void End::Wypisz(string pkt, Ranking* pRanking)
{  // odt¹d ......
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 22, NULL);
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 50, 50, ALLEGRO_ALIGN_LEFT, "Liczba uzyskanych punktow : ");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 50, ALLEGRO_ALIGN_LEFT, pkt.c_str());
	al_flip_display();
	Ranking* View = pRanking;
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 50, 90, ALLEGRO_ALIGN_LEFT, " -----------RANKING------------------");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 80, 120, ALLEGRO_ALIGN_LEFT, "#1 ---");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 140, 120, ALLEGRO_ALIGN_LEFT, View->nick.c_str());
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 190, 120, ALLEGRO_ALIGN_LEFT, "   ");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 230, 120, ALLEGRO_ALIGN_LEFT, to_string(View->punkty).c_str());
	View = View->pNext;
	//......

	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 80, 160, ALLEGRO_ALIGN_LEFT, "#2 ---");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 140, 160, ALLEGRO_ALIGN_LEFT, View->nick.c_str());
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 190, 160, ALLEGRO_ALIGN_LEFT, "   ");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 230, 160, ALLEGRO_ALIGN_LEFT, to_string(View->punkty).c_str());
	View = View->pNext;
	//......
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 80, 200, ALLEGRO_ALIGN_LEFT, "#3 ---");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 140, 200, ALLEGRO_ALIGN_LEFT, View->nick.c_str());
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 190, 200, ALLEGRO_ALIGN_LEFT, "   ");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 230, 200, ALLEGRO_ALIGN_LEFT, to_string(View->punkty).c_str());
	View = View->pNext;
	//......
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 80, 240, ALLEGRO_ALIGN_LEFT, "#4 ---");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 140, 240, ALLEGRO_ALIGN_LEFT, View->nick.c_str());
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 190, 240, ALLEGRO_ALIGN_LEFT, "   ");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 230, 240, ALLEGRO_ALIGN_LEFT, to_string(View->punkty).c_str());
	View = View->pNext;
	//......
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 80, 280, ALLEGRO_ALIGN_LEFT, "#5 ---");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 140, 280, ALLEGRO_ALIGN_LEFT, View->nick.c_str());
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 190, 280, ALLEGRO_ALIGN_LEFT, "   ");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 230, 280, ALLEGRO_ALIGN_LEFT, to_string(View->punkty).c_str());
	al_flip_display();
	al_rest(3);
	al_clear_to_color(al_map_rgb(20, 75, 80));
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 50, 90, ALLEGRO_ALIGN_LEFT, "1 - PanelGracza");
	al_flip_display();
	//... dotad FUNKCJA WYPOISUJE KOMINITAK NA EKRAN

}

void End::TheEnd(string nick, int punkty, Ranking* pRanking, string NazwaPliku)
{
	al_clear_to_color(al_map_rgb(20, 75, 80));// wyczysc do koloru
	bool done = false;
	ALLEGRO_EVENT ev1;// event
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 22, NULL); // zaladuj czciake
	ALLEGRO_EVENT_QUEUE* kolejka = NULL; // w poczekalni NULL
	kolejka = al_create_event_queue(); // nowa kolejka
	string pkt = to_string(punkty); // conwertuj punkty z int na string
	al_register_event_source(kolejka, al_get_keyboard_event_source());
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 50, 50, ALLEGRO_ALIGN_LEFT, "Liczba uzyskanych punktow : " );
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 50, ALLEGRO_ALIGN_LEFT, pkt.c_str()); // wyswietla komunikat o liczbie punktow
	al_flip_display();
	
	int k = 1;
	RekrutacjaDoRankingu(pRanking, k, punkty, nick); // sprwdzamy czy ilosc punktow jest wystarczajaca by zaliczyc gracza do rankingu
	
	Wypisz(pkt, pRanking); // wypisuje kominikat na ekran

	ZapiszRanking(pRanking, NazwaPliku); // zapisujemy ranking
	
	while (!done) // czekamy an event
	{
		al_wait_for_event(kolejka, &ev1);

		if (ev1.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev1.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		{

			done = true;
			exit(1);

		}
		else  if (ev1.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ev1.keyboard.keycode == ALLEGRO_KEY_1)// jesli jeden to idz do glownego menu
			{
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_flip_display();
				Gracz G1;
				
				G1.nick = nick;
				G1.UserMenu();


			}

			// jesli cos innego to czekaj na wybrany komunikat
			
		}
	}

		
	

	 
}

void End::RekrutacjaDoRankingu(Ranking*& pRanking, int i, int punkty, string nick)
{
	if (pRanking) // jezeli istnieje
	{
		if (pRanking->punkty < punkty) // punkty rankingowe sa mniejsze od podanych
		{
			pRanking = new Ranking{ nick,punkty,pRanking }; // to zapisz je do rankingu
			cout << "Twoje miejsce :  " << i << endl;
		}

		else {
			i = i + 1;
			return RekrutacjaDoRankingu(pRanking->pNext, i, punkty, nick); // jezeli nie to sprobuj z nastepnym najlepszym wynikiem 

		}
	}
	else {
		pRanking = new Ranking{ nick,punkty,nullptr }; // jezeli ranking jest pusty to utworz go
	}
}

void End::popfrontRanking(Ranking*& pRanking)
{
	Ranking* p = pRanking; // usuwamy ranking
	if (p)
	{
		pRanking = p->pNext;
		delete p;
	}


}
