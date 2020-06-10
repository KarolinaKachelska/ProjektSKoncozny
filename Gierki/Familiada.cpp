#include <iostream>
#include<string>
#include <fstream>
#include <sstream> 
#include <windows.h> // funk. Sleep()
#include <time.h>
#include"Familiada.h"



Familiada::Familiada()
{
	this->nick = "gosc";
	this->punkty = 0;
	this->odp = "";
	//for (int n = 0; n < 5; n++)
	//	this->tablica[n] = "";
	this->NazwaPliku = "Familiada/Familiada_ranking.txt";
	this->pList = nullptr;
	this->pRanking = nullptr;
	ALLEGRO_DISPLAY* display = Gracz::display;
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;

}

Familiada::~Familiada()
{

	while (pList) popfrontList();

	while (pRanking) popfrontRanking(this->pRanking);

	al_destroy_event_queue(kolejka);
}

void Familiada::graj()
{

	bool czyGrac = true;
	bool done = false;
	ALLEGRO_EVENT ev1;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL);// ladujemy czciake
	ALLEGRO_EVENT_QUEUE* kolejka = NULL; // kolejka NULL
	kolejka = al_create_event_queue(); // nowa kolejka
	al_register_event_source(kolejka, al_get_keyboard_event_source()); // zczytuj z klawiatury
	this->odp = "";


	for (int i = 0; i < 5; i++) // dla piêciu razy zrób ...
	{
		losuj(); // wylosuj pytanie 
		al_draw_text(Myfont, al_map_rgb(255, 255, 200),50, 50, ALLEGRO_ALIGN_LEFT,this->nazwa.c_str()); // wyswieytl pytanie
		al_flip_display();

		while (!done) // poczekaj na odpowiedz
		{
			al_wait_for_event(kolejka, &ev1);

			if (ev1.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{

				done = true;
				exit(1);

			}
			else  if (ev1.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				if (ev1.keyboard.keycode == ALLEGRO_KEY_ENTER)
				{
					done = true;
				}
				else if (ev1.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) // jezeli backspace to zacznij wpisywac od nowa
				{
					al_clear_to_color(al_map_rgb(20, 75, 80));
					al_draw_text(Myfont, al_map_rgb(255, 255, 200), 50, 50, ALLEGRO_ALIGN_LEFT, this->nazwa.c_str());
					al_flip_display();
					odp = "";
					done = false;
				}


				else {

					this->odp.push_back(ev1.keyboard.keycode + 96);// wyswietlaj na bierzaco co sie pisze
					al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 120, ALLEGRO_ALIGN_LEFT, this->odp.c_str());
					al_flip_display();
				}


			}
		}


		this->odp = ZmienZnak(this->odp); // zmien znak jezeli jest taka potrzeba
		Sprawdz(); // sprawdz czy odpowiedz jest dobra
		al_clear_to_color(al_map_rgb(20, 75, 80)); // wyczysc ekran
		al_flip_display();
		done = false;
		this->odp = "";


	} // i tak 5 razy poprosze : )

	// wyswietl punkty uzyskane
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 40, ALLEGRO_ALIGN_LEFT, "Twoje punkty :  ");

	string pkt = to_string(punkty); // convert punktow z int na string
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 120, ALLEGRO_ALIGN_LEFT, pkt.c_str());
	al_flip_display();
	al_rest(2); // pokazuj przez 2 sekundy


	if (nick != "gosc") // jezeli nei grasz jakos gosc to ..
	{
		zapiszPunkty(); //.. zapisz punkty do pliku .txt
	}

	TheEnd(this->nick, this->punkty, this->pRanking, this->NazwaPliku); // przejdz do zakonczenia gry 
}

void Familiada::losuj()
{
	srand((unsigned)time(NULL));
	int los = rand() % 17 + 1; // losuj
	string ss;
	fstream plik;
	string linia;
	string nazwaPliku = "Familiada/Pytanie" + to_string(los) + ".txt"; // wybierz nazwe pliku 
	plik.open(nazwaPliku, ios::in); // otworz
	try {
		if (plik.good() == true) // jezeli jest ok to ..
		{



			getline(plik, linia); // pobierz linijke  z pytaniem

			this->nazwa = linia; // zapisz do zmiennej

			for (int i = 0; i < 5; i++) // 5 razy zapisz do tablicy odpowiedzi na pytania
			{
				getline(plik, linia);

				this->tablica[i] = linia;

			}



			plik.close();


		}

		else
		{
			throw ss;
		}// wyrzuc watek jesli nie ok
	}
	catch (string)
	{
		cout << "Blad odczytu pliku" << endl; // error?
		Sleep(1000);
		system("cls");
		exit(5);

	}


}

void Familiada::Sprawdz()
{
	bool check = false;
	for (int i = 0; i < 5; i++) // dla 5 prob sprawdz czy odpowiedz wpisana przez uzytkownika jest rowna odpowiedzi z tablicy 
	{
		if (this->odp == tablica[i])
		{
			this->punkty += 20 - i * 4; // system punktacji ( kazde nastepne przesuneicie petli zmienja liczbe punktow !)
			check = true;
			i = 10;
		}


	}

	if (check == false) this->punkty += 0;

}

void Familiada::StworzRanking()
{
	string ss;
	fstream plik;
	string NickView;
	int PointView;
	string linia;
	plik.open(this->NazwaPliku, std::ios::in); // otworz plik
	try {
		if (plik.good() == true) // jest ok to ..
		{


			while (!plik.eof()) // ...tak dlugo jak jest to ..
			{

				getline(plik, linia);//.. pobierz linie..

				istringstream iss(linia);
				iss >> linia;
				NickView = linia; // zapisz nick z linii
				iss >> linia;
				PointView = atoi(linia.c_str());// convert string na int
				DodajDoRankingu(pRanking, NickView, PointView); // dodaj do rankingu 


			}
			plik.close(); // zamknij 
		}


		else
		{ // wyrzuc watek jesli nie ok 
			throw ss;
		}
	}
	catch (string)
	{
		cout << "Blad odczytu pliku" << endl; // error??
		Sleep(1000);
		system("cls");
		exit(5);
	}

}

void Familiada::zapiszPunkty()
{
	string ss;
	string sss;
	string linia;
	fstream plik;
	string linia1;
	string linia2;
	string linia3;
	string linia4;
	string nazwaPliku = "Users/nick/" + this->nick + ".txt"; // wybierz nazwe pliku ( inna dla kazdego z graczy)
	plik.open(nazwaPliku, ios::in); // otworz plik
	try {
		if (plik.good() == true) // jest ok ? 
		{

			getline(plik, linia1); //pobierz linie
			getline(plik, linia2);//pobierz linie
			getline(plik, linia3);//pobierz linie
			getline(plik, linia4);//pobierz linie



			plik.close(); // zamknij
		}

		else // nie ejst ok, wyrzuc watek
		{
			throw ss;
		}
	}
	catch (string)
	{
		cout << "Blad odczytu pliku" << endl; //error?
		Sleep(1000);
		system("cls");
		exit(5);

	}
	plik.open(nazwaPliku, ios::out);// otwirz plik
	try {
		if (plik.good() == true) // jest ok ?
		{

			plik << linia1 << endl; // zapisz linie
			plik << linia2 << endl;// zapisz linie
			plik << linia3 << endl;// zapisz linie
			plik << linia4 + " " + to_string(this->punkty);// zapisz linie  z convertem na string

			plik.close(); // zaknij
		}

		else
		{
			throw sss; // nie jest ok , wyrzuc watek
		}
	}
	catch (string)
	{
		cout << "Blad odczytu pliku" << endl; // error?
		Sleep(1000);
		system("cls");
		exit(5);

	}



}
