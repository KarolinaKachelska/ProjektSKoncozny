#include <iostream>
#include<string>
#include <fstream>
#include <sstream> 
#include <windows.h> // funk. Sleep()
#include <time.h>
#include "ZgadnijktoTo.h"


ZgadnijKtoTo::ZgadnijKtoTo()
{

	this->nick = "gosc";
	this->punkty = 0;
	this->odpA = "";
	this->odpB = "";
	this->odpC = "";
	for (int n = 0; n < 33; n++)
		this->tablica[n] = "";
	this->NazwaPliku = "ZgadnijKtoTo/ZgadnijKtoTo_ranking.txt";
	this->pList = nullptr;
	this->pRanking = nullptr;
	ALLEGRO_DISPLAY* display = Gracz::display;
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;


}

ZgadnijKtoTo::~ZgadnijKtoTo()
{

	while (pList) popfrontList();

	while (pRanking) popfrontRanking(this->pRanking);


}

bool ZgadnijKtoTo::SprawdzOdpowiedz(char pyt, int int_pyt)
{
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 22, NULL); // ladujemy czciake
	string ss;
	try {
		if (pyt >= 65 && pyt <= 122) // sprawdzamy chy to litera
		{
			
			string Poprodpowiedz = "";
			Poprodpowiedz = ZmienZnak(Poprodpowiedz + pyt); // zmieniamy znak jesli taka potrzeba

			if (Poprodpowiedz == "A")Poprodpowiedz = this->odpA; 
			else if (Poprodpowiedz == "B") Poprodpowiedz = this->odpB;
			else if (Poprodpowiedz == "C") Poprodpowiedz = this->odpC;

			if (Poprodpowiedz == this->nazwa) { // jesli odpowiedz uzytkownika sie zgadza z poprawna odpowiedzia to..
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_flip_display();

				al_draw_text(Myfont, al_map_rgb(255, 255, 200), 10, 50, ALLEGRO_ALIGN_LEFT, "jej <3"); // wyswietl komunikat
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), 10, 90, ALLEGRO_ALIGN_LEFT, "Twoje punkty :  ");
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), 80, 140, ALLEGRO_ALIGN_LEFT, to_string(punkty).c_str()); // convert to string
				al_flip_display();
				al_rest(1);


				this->punkty = punkty;
				if (nick != "gosc") // jezeli nie gra gosc to ..
				{
					zapiszPunkty(); // zapisz punkty 
				}
				al_clear_to_color(al_map_rgb(20, 75, 80)); // wyczysc ekran
				al_flip_display();
				
				TheEnd(this->nick, this->punkty, this->pRanking, this->NazwaPliku); // przejdz do podsumowania gry
				return false;

			}
			else { // jesli nie to ..
				punkty = 0;
				al_clear_to_color(al_map_rgb(20, 75, 80));// wyczysc ekran
				al_flip_display();

				al_draw_text(Myfont, al_map_rgb(255, 255, 200), 10, 50, ALLEGRO_ALIGN_LEFT, "smutne, nie udalo ci sie ;c"); // wyswietl komunikat
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), 80, 90, ALLEGRO_ALIGN_LEFT, "Twoje punkty :  ");
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), 120, 150, ALLEGRO_ALIGN_LEFT, to_string(punkty).c_str());// convert to string
				al_flip_display();
				al_rest(1);
				this->punkty = punkty;
				if (nick != "gosc") // jezeli nie gra gosc to ..
				{
					zapiszPunkty(); // zapisz punkty 
				}
				al_clear_to_color(al_map_rgb(20, 75, 80)); // wyczysc ekran
				al_flip_display();
				TheEnd(this->nick, this->punkty, this->pRanking, this->NazwaPliku);// przejdz do podsumowania gry
				return false;


			}
			
			return true;

		}
		else if (int_pyt >= 1 && int_pyt <= 16) // jesli to liczba to ..
		{
			punkty--; // odejmij punkt za kazde zadanie pytanie
			WybierzPytanie(int_pyt); // wyswietl odpowiedz na zadane pytanie
			
			return false;
		}
		else throw ss; // jezeli to ani liczba ani litera to wyrzuc watek
	}
	catch (string) // zlap
	{
		cout << "Blad! nie wpisales ani odpowiedzi, ani numeru pytania !" << endl; // error?
		Sleep(1000);
		system("cls");
		exit(5);
	}


}

void ZgadnijKtoTo::graj()
{
	// uzywane zminne 
	int los;
	int los2;
	int los3;
	char pyt=' ';
	char pyt2[2] = { ' ',' ' };
	int punkty = 16;
    int int_pyt;
	string string_pyt="";
	bool done = false;
	ALLEGRO_EVENT ev1;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 22, NULL); // zaladuj czciake
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;
	kolejka = al_create_event_queue(); // nowa kolejka
	al_register_event_source(kolejka, al_get_keyboard_event_source()); // zaladuj klawiature
    srand((unsigned)time(NULL)); // losuj wedlug czasu
    bool czyLitera = false;
	los = rand() % 16 + 1; // losuj
	los2 = rand() % 16 + 1; // losuj
	while (los == los2) los2 = rand() % 16 + 1; // sprawdz czy nie wylosowalo tego samego
	los3 = rand() % 16 + 1; // losuj 
	while (los == los3 || los2 == los3) los3 = rand() % 16 + 1;// sprawdz czy nie wylosowalo tego samego
    tablica[0] = "";
	WybierzPostac(los); // wybierz dobra odpowiedz
	string odp2 = WybierzDodatkowa(los2); // wybierz dodatkowa
	string odp3 = WybierzDodatkowa(los3); // wybierz dodatkowa
	losujKolejnoscOdpowiedzi(odp2, odp3); // losuj kolejnosc wyswietlania odpowiedzi
	WyswietlPytania(); // wyswietl mozliwe pytania
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 10, 10, ALLEGRO_ALIGN_LEFT, "Wybierz numer pytania lub wybierz litere Twojej odpowiedzi ! "); // wyswietl komunikat
	al_flip_display();
	int i = 0;
	do { while (!done) // petla w ktorej uzytkownik bedzie wpisywal odpowiedzi badz pytania
		{ al_wait_for_event(kolejka, &ev1);
	        if (ev1.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{  done = true;  exit(1); }
			else  if (ev1.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				if (ev1.keyboard.keycode == ALLEGRO_KEY_ENTER)
				{  done = true;  }

				else {
					pyt2[i]=ev1.keyboard.keycode+21;
					pyt = ev1.keyboard.keycode + 96;  i++;
				}
            }
		}

		string_pyt.push_back(pyt2[0]);
		if(i==2)  string_pyt.push_back(pyt2[1]);
		int_pyt = atoi(string_pyt.c_str());
		cout << string_pyt << endl;
		czyLitera = SprawdzOdpowiedz(pyt, int_pyt); // sprawdz czy odpowiedz jest dobra
		done = czyLitera;
        string_pyt = "";
		int_pyt = 0;
		pyt2[0] = ' ';
		pyt2[1] = ' ';
		pyt = ' ';
		i = 0;
	} while (czyLitera == false);
	

}

void ZgadnijKtoTo::WybierzPostac(int los)
{

	string ss;
	fstream plik;
	string linia;
	string nazwaPliku = "ZgadnijKtoTo/Postac" + to_string(los) + ".txt"; // wybierz plik z postacia 
	plik.open(nazwaPliku, std::ios::in); // otworz plik 
	try {
		if (plik.good() == true) // jezeli okt o ..
		{


			while (!plik.eof()) // tak dlugo az jest 
			{
				getline(plik, linia); // bierz linie

				this->nazwa = linia; // daj jako nazwa postaci

				for (int i = 1; i < 17; i++) // dla 17 pytan , odczytuj 17 razy
				{
					getline(plik, linia); // bierz linie z pytaniem
					tablica[i] = linia; // zapisz ja
					getline(plik, linia); // bierz linie z odpowiedzia 
					tablica[i + 16] = linia; // zapisz je 
				}





			}
			plik.close(); // zamknij


		}

		else // jezeli nie jest to to wyrzuc watek
		{
			throw ss;
		}
	}
	catch (string) // zlap
	{
		cout << "Blad odczytu pliku" << endl; // error?
		Sleep(1000);
		system("cls");
		exit(5);
	}




}

string ZgadnijKtoTo::WybierzDodatkowa(int los2)
{

	string ss;
	fstream plik;
	string linia;
	string nazwaPliku = "ZgadnijKtoTo/Postacie.txt"; // wybierz plik z postacia 
	plik.open(nazwaPliku, std::ios::in);// otworz plik 
	try {
		if (plik.good() == true)// jezeli ok to ..
		{

			for (int i = 1; i < los2 + 1; i++) 
			{

				getline(plik, linia);// bierz linie


			}

			return linia;// zwroc linie
			plik.close(); // zamknij

		}


		else// jezeli nie jest to to wyrzuc watek
		{
			throw ss;
		}
	}
	catch (string)// zlap
	{
		cout << "Blad odczytu pliku" << endl;// error?
		Sleep(1000);
		system("cls");
		exit(5);
	}


	return "";
}

void ZgadnijKtoTo::losujKolejnoscOdpowiedzi(string odp2, string odp3)
{

	int Kolejnosc = rand() % 6 + 1; // losuj
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 12, NULL); // zaladuj czciake
	switch (Kolejnosc)
	{ // wybuierz jedno z wylosowanych
	case 1:
		
		this->odpA = this->nazwa;// dobra odpowiedz
		this->odpB = odp2;
		this->odpC = odp3;
		break;

	case 2:
		
		this->odpA = odp2;
		this->odpB = this->nazwa;// dobra odpowiedz
		this->odpC = odp3;

		break;
	case 3:
		
		this->odpA = odp3;
		this->odpB = odp2;
		this->odpC = this->nazwa;// dobra odpowiedz

		break;



	case 4:
		
		this->odpA = odp2;
		this->odpB = odp3;
		this->odpC = this->nazwa;// dobra odpowiedz

		break;
	case 5:
		
		this->odpA = odp3;
		this->odpB = this->nazwa;// dobra odpowiedz
		this->odpC = odp2;

		break;
	case 6:
		
		this->odpA = this->nazwa; // dobra odpowiedz
		this->odpB = odp3;
		this->odpC = odp2;
		break;

	}
	// wyswietl odpowiedzi
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 50, ALLEGRO_ALIGN_LEFT, "Mozliwe Odpowiedzi: ");

	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 70, ALLEGRO_ALIGN_LEFT, "A. ");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 70, ALLEGRO_ALIGN_LEFT, this->odpA.c_str());

	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 110, ALLEGRO_ALIGN_LEFT, "B. ");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 110, ALLEGRO_ALIGN_LEFT, odpB.c_str());

	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 450, 150, ALLEGRO_ALIGN_LEFT, "C. ");
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 500, 150, ALLEGRO_ALIGN_LEFT, odpC.c_str());
	al_flip_display();
}

void ZgadnijKtoTo::WyswietlPytania()
{
	int wys=10;
	int szer=70;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 12, NULL);// zaladuj czciake
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 10, 45, ALLEGRO_ALIGN_LEFT, "Pytania: "); // wyswietl komunikat

	for (int i = 1; i < 17; i++) // dla 17 razy
	{
		
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), wys, szer, ALLEGRO_ALIGN_LEFT, tablica[i].c_str()); // wyswietl pytanie
		szer = szer + 15; // zmien szerokosc, by nastepne pytanie bylo nizej
	}
	al_flip_display();

}

void ZgadnijKtoTo::WybierzPytanie(int pyt)
{
	int wys = 350;
	int szer = 55 +15*pyt; //+15
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 12, NULL); // zaladuj czciake
	
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), wys, szer, ALLEGRO_ALIGN_LEFT, tablica[pyt+16].c_str()); // wyswietl odpowiedz na pytanie ktore zadal uzytkownik
	al_flip_display();
}

void ZgadnijKtoTo::zapiszPunkty()
{
	string ss;
	string sss;
	string linia;
	fstream plik;
	string linia1;
	string linia2;
	string linia3;
	string linia4;
	string nazwaPliku = "Users/nick/" + this->nick + ".txt";// wybierz plik z gracza
	plik.open(nazwaPliku, ios::in);// otworz plik 
	try
	{
		if (plik.good() == true)// jezeli ok to ..
		{

			getline(plik, linia1);// bierz linie
			getline(plik, linia2);// bierz linie
			getline(plik, linia3);// bierz linie
			getline(plik, linia4);// bierz linie



			plik.close();// zamknij
		}

		else// jezeli nie jest to to wyrzuc watek
		{
			throw ss;
		}
	}
	catch (string)// zlap
	{
		cout << "Blad odczytu pliku" << endl;// error?
		Sleep(1000);
		system("cls");
		exit(5);
	}

	plik.open(nazwaPliku, ios::out);// otworz plik 
	try {
		if (plik.good() == true)// jezeli ok to ..
		{

			plik << linia1 << endl; // zapisz linie
			plik << linia2 << endl;// zapisz linie
			plik << linia3 + " " + to_string(this->punkty) << endl; // konvert na string // zapisz linie
			plik << linia4 << endl;// zapisz linie 

			plik.close();// zamknij
		}

		else// jezeli nie jest to to wyrzuc watek
		{
			throw sss;
		}
	}
	catch (string)// zlap
	{
		cout << "Blad odczytu pliku" << endl;// error?
		Sleep(1000);
		system("cls");
		exit(5);
	}



}

void ZgadnijKtoTo::StworzRanking()
{

	fstream plik;
	string ss;
	string NickView;
	int PointView;
	string linia;
	string nazwaPliku = this->NazwaPliku;
	plik.open(nazwaPliku, std::ios::in);// otworz plik 
	try {
		if (plik.good() == true)// jezeli ok to ..
		{


			while (!plik.eof())
			{

				getline(plik, linia);

				istringstream iss(linia);
				iss >> linia;
				NickView = linia; // zabierz nick z pliku .txt
				iss >> linia;
				PointView = atoi(linia.c_str()); // convert na int
				DodajDoRankingu(this->pRanking, NickView, PointView); // dodaj do rankingu


			}
			plik.close();// zamknij
		}

		else// jezeli nie jest to to wyrzuc watek
		{
			throw ss;
		}
	}
	catch (string)// zlap
	{
		cout << "Blad odczytu pliku" << endl;// error?
		Sleep(1000);
		system("cls");
		exit(5);
	}



}


