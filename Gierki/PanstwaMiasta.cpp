#include <sstream> 
#include <time.h>
#include"PanstwaMiasta.h"


void PanstwaMiasta::StworzRanking()
{
	string ss;
	fstream plik;
	string NickView;
	int PointView;
	string linia;
	string nazwaPliku = this->NazwaPliku;

	plik.open(nazwaPliku, std::ios::in); //otworz plik
	try {
		if (plik.good() == true) // jesli jest ok to..
		{


			while (!plik.eof())// tak dlugo jak istnieje 
			{

				getline(plik, linia); // pobierz linie

				istringstream iss(linia);
				iss >> linia;
				NickView = linia; // linia z nickiem
				iss >> linia;
				PointView = atoi(linia.c_str()); // zmien na int
				DodajDoRankingu(pRanking, NickView, PointView); // dodaj do rankingu


			}
			plik.close(); // zamknij
		}

		else
		{
			throw ss;
		}
	}
	catch (string)
	{
		cout << "Blad odczytu pliku" << endl;
		Sleep(1000);
		system("cls");
		exit(5);
	}
}

PanstwaMiasta::PanstwaMiasta()
{
	this->nick = "gosc";
	this->punkty = 0;
	this->NazwaPliku = "PanstwaMiasta/PanstwaMiasta_ranking.txt";
	this->pList = nullptr;
	this->pHead = nullptr;
	this->pHead2 = nullptr;
	this->pRanking = nullptr;
	ALLEGRO_DISPLAY* display =Gracz::display;
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;


}

PanstwaMiasta::~PanstwaMiasta()
{

	while (pHead) popfrontTree();

	while (pHead2) popfrontTree2();

	while (pList) popfrontList();

	while (pRanking) popfrontRanking(this->pRanking);
	al_destroy_event_queue(kolejka);

}

bool PanstwaMiasta::Odpowiedz()
{
	bool done = false;
	ALLEGRO_EVENT ev1; // stworz event
	kolejka = al_create_event_queue(); // nowa kolejka
	al_register_event_source(kolejka, al_get_keyboard_event_source()); // uzyj klawiatury
	while (!done)
	{
		al_wait_for_event(kolejka, &ev1);

		if (ev1.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{

			done = true;
			exit(1);
			return false;

		}
		else  if (ev1.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ev1.keyboard.keycode == ALLEGRO_KEY_1)
			{
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_flip_display();
				return true;
			}
			else if (ev1.keyboard.keycode == ALLEGRO_KEY_2)
			{
				return false;

			}


		}
	}

}

void PanstwaMiasta::graj()
{
	ALLEGRO_EVENT ev1;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL); // czciaka
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;
	kolejka = al_create_event_queue(); // nowa kolejka
	al_register_event_source(kolejka, al_get_keyboard_event_source());// uzyj klawiatury
	bool check = false;
	bool czyGrac = true;
	int punkty = 0;
	string nazwaPliku = "PanstwaMiasta/panstwa.txt";
	czytajPlik(pHead, nazwaPliku); // zapisz nazwy Panstw 
	string nazwaPliku2 = "PanstwaMiasta/miasta.txt";
	czytajPlik(pHead2, nazwaPliku2); // zapisz nazwy miast
	char litera;
	string pkt;
	srand((unsigned)time(NULL)); // losuj wedlug czasu

	do
	{
		litera = rand() % 26 + 65; // losuj
		if (litera == 'Q' || litera == 'X' || litera == 'Y' || litera == 'V') litera = 'Z'; // jezeli takei litery wylosujesz to zmien
		
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Wylosowana litera: ");//kominikat na ekran
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 40, ALLEGRO_ALIGN_LEFT, &litera);
		al_flip_display();
		wpiszNazweP(litera);// wpisz nazwe Panstwa
		check = sprawdzP(pHead, litera); // sprawdz czy istnieje

		if (check == false)
		{
			al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Smutne, nie udalo ci sie ;c ");//kominikat na ekran
			al_flip_display();
			al_rest(1);
			al_clear_to_color(al_map_rgb(20, 75, 80));
			al_flip_display();
			czyGrac = false;
		}
		else {
			al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Wylosowana litera: ");//kominikat na ekran
			al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 40, ALLEGRO_ALIGN_LEFT, &litera);
			al_flip_display();
			wpiszNazweM(litera); // wpisz nazwe miasta
			check = sprawdzM(pHead2, litera); // sprawdz czy istnije
			
			if (check == false)
			{
				pkt = to_string(punkty);
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Smutne, nie udalo ci sie ;c ");//kominikat na ekran
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4)+40, ALLEGRO_ALIGN_LEFT, "Twoje punkty : ");
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4)+80, ALLEGRO_ALIGN_LEFT, pkt.c_str() );
				al_flip_display();
				al_rest(2);
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_flip_display();
				czyGrac = false;
			}
			else
			{
				punkty++;
				pkt = to_string(punkty);
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Jej, dales rade <3 ");//kominikat na ekran
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 40, ALLEGRO_ALIGN_LEFT, "Twoje punkty : ");
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 80, ALLEGRO_ALIGN_LEFT, pkt.c_str());
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4)+120, ALLEGRO_ALIGN_LEFT, "Czy chcesz dalej grac? ");
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 160, ALLEGRO_ALIGN_LEFT, "1 - TAK ");
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 200, ALLEGRO_ALIGN_LEFT, "2 - NIE ");
				al_flip_display();
				
				czyGrac = Odpowiedz();// czekam na odpowiedz uzytkownika

				
			}
		}





	} while (czyGrac);

	this->punkty = punkty;
	if (nick != "gosc")// jezeli uzytkownik nie gra jako gosc to ..
	{
		zapiszPunkty(); //.. zapisz jego punkty
	}

	TheEnd(this->nick, this->punkty, this->pRanking, this->NazwaPliku); // przejdz do etapu koncowego rozgrywki
}

void PanstwaMiasta::czytajPlik(Tree*& pHead, string nazwaPliku)
{
	string ss;
	fstream plik;
	string linia;
	plik.open(nazwaPliku, std::ios::in | std::ios::out); // otworz plik
	try {
		if (plik.good() == true) // jest opk ?
		{


			while (!plik.eof())// tak dlugo jak istnieje
			{
				getline(plik, linia); // pobierz linie

				dodajDrzewo(pHead, linia); // zapisz do listy

			}
			plik.close();//zamknij


		}

		else
		{
			throw ss;
		}
	}
	catch (string)
	{
		cout << "Blad odczytu pliku" << endl;
		Sleep(1000);
		system("cls");
		exit(5);
	}

}

void PanstwaMiasta::dodajDrzewo(Tree*& pHead, string slowo)
{
	if (!pHead) pHead = new Tree{ nullptr, slowo };// jesli puste do wpisz
	else {
		return dodajDrzewo(pHead->pNext, slowo);// jesli cos jest to przejdz dalej

	}
}

bool PanstwaMiasta::sprawdzP(Tree* pHead, char litera)
{
	while (pHead)// jak istnieje to..
	{
		if (pHead->nazwa_P_M == this->nazwa && nazwa[0] == litera) // sprawdz czy to samo
		{
			return true;
		}
		else pHead = pHead->pNext;// jak nie to idz dalej
	}

	return false;
}

bool PanstwaMiasta::sprawdzM(Tree* pHead, char litera)
{
	while (pHead)// jak istnieje to..
	{
		if (pHead->nazwa_P_M == this->nazwa && nazwa[0] == litera) // sprawdz czy to samo
		{
			return true;
		}
		else pHead = pHead->pNext;// jak nie to idz dalej
	}


	return false;
}

void PanstwaMiasta::wpiszNazweM(char literka)
{
	bool done = false;
	ALLEGRO_EVENT ev1;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL); // czciaka
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;
	kolejka = al_create_event_queue(); // nowa kolejka
	al_register_event_source(kolejka, al_get_keyboard_event_source()); // uzywaj klawiatury
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4)+120, ALLEGRO_ALIGN_LEFT, "Wpisz nazwe wybranej Stolicy :  "); // komunikat na ekran

	al_flip_display();
	
	string nazwa="";
	while (!done)// czekaj an event
	{
		al_wait_for_event(kolejka, &ev1);

		if (ev1.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev1.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
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
			else if (ev1.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
			{
				
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Wylosowana litera: ");// komunikat na ekran
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 40, ALLEGRO_ALIGN_LEFT, &literka);// komunikat na ekran
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 120, ALLEGRO_ALIGN_LEFT, "Wpisz nazwe wybranej Stolicy :  ");// komunikat na ekran

				al_flip_display();
				nazwa = "";
				done = false;
			}


			else {

				nazwa.push_back(ev1.keyboard.keycode + 96); // wyswietlaj na bierzaco co uzytkownik wpisuje
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 160, ALLEGRO_ALIGN_LEFT, nazwa.c_str());// komunikat na ekran
				al_flip_display();
			}
		}
	}

	al_clear_to_color(al_map_rgb(20, 75, 80)); // wyczysc ekran
	al_flip_display();
	
	nazwa = ZmienZnak(nazwa); // zmien znak jesli jest taka potrzeba
	this->nazwa = nazwa;

}

void PanstwaMiasta::wpiszNazweP(char literka)
{
	bool done = false;
	ALLEGRO_EVENT ev1;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL);// czciaka
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;
	kolejka = al_create_event_queue();// nowa kolejka
	al_register_event_source(kolejka, al_get_keyboard_event_source()); // uzywaj klawiatury
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 120, ALLEGRO_ALIGN_LEFT, "Wpisz nazwe Panstwa : ");// komunikat na ekran
    al_flip_display();
	
	string nazwa = "";
	while (!done)// czekaj an event
	{
		al_wait_for_event(kolejka, &ev1);

		if (ev1.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev1.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
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
			else if (ev1.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
			{
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Wylosowana litera: ");// komunikat na ekran
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 40, ALLEGRO_ALIGN_LEFT, &literka);// komunikat na ekran
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 120, ALLEGRO_ALIGN_LEFT, "Wpisz nazwe Panstwa : ");// komunikat na ekran

				al_flip_display();
				nazwa = "";
				done = false;
			}


			else {

				nazwa.push_back(ev1.keyboard.keycode + 96);// wyswietlaj na bierzaco co uzytkownik wpisuje
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 160, ALLEGRO_ALIGN_LEFT, nazwa.c_str());// komunikat na ekran
				al_flip_display();
			}
		}
	}

	al_clear_to_color(al_map_rgb(20, 75, 80)); // wyczysc ekran
	al_flip_display();

	nazwa = ZmienZnak(nazwa);// zmien znak jesli jest taka potrzeba
	this->nazwa = nazwa;


}

void PanstwaMiasta::zapiszPunkty()
{
	string ss;
	string sss;
	string linia;
	fstream plik;
	string linia1;
	string linia2;
	string linia3;
	string linia4;
	string nazwaPliku = "Users/nick/" + this->nick + ".txt";// znajd plik
	plik.open(nazwaPliku, ios::in); // otworz plik
	try {
		if (plik.good() == true) // jest ok ?
		{

			getline(plik, linia1);//pobierz linie
			getline(plik, linia2);//pobierz linie
			getline(plik, linia3);//pobierz linie
			getline(plik, linia4);//pobierz linie




			plik.close();// zamknij
		}

		else
		{
			throw ss;
		}
	}
	catch (string)
	{
		cout << "Blad odczytu pliku" << endl;
		Sleep(1000);
		system("cls");
		exit(5);
	}
	plik.open(nazwaPliku, ios::out);// otworz plik
	try {
		if (plik.good() == true) // jest ok ?
		{

			plik << linia1 << endl; // zapisz linie
			plik << linia2 + " " + to_string(this->punkty) << endl;// zapisz linie
			plik << linia3 << endl;// zapisz linie
			plik << linia4 << endl;// zapisz linie

			plik.close(); // zamknij
		}

		else
		{
			throw sss;
		}
	}
	catch (string)
	{
		cout << "Blad odczytu pliku" << endl;
		Sleep(1000);
		system("cls");
		exit(5);
	}


}

void PanstwaMiasta::popfrontTree()
{ // usun liste
	Tree* p = pHead;
	if (p)
	{
		pHead = p->pNext;
		delete p;
	}

}

void PanstwaMiasta::popfrontTree2()
{// usun liste
	Tree* p = pHead2;
	if (p)
	{
		pHead2 = p->pNext;
		delete p;
	}
}
