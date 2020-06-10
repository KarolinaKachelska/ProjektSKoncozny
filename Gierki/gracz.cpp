
#include "gracz.h"
#include "PanstwaMiasta.h"
#include"ZgadnijKtoTo.h"
#include"Familiada.h"


Gracz::Gracz()
{
	this->nick = "gosc";
	this->nazwa = "";
	this->punkty = 0;
	this->pList = nullptr;
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;
	


}

Gracz::~Gracz()
{

	while (pList) popfrontList();
	al_destroy_event_queue(kolejka);

}

void Gracz::popfrontList()
{ //usun liste
	List* p = pList;
	if (p)
	{
		pList = p->pNext;
		delete p;
	}


}

void Gracz::wypiszPunkty()
{
	string ss;
	
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL); // czciaka
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 80, (0), ALLEGRO_ALIGN_LEFT, "Wyswietlane 5 sekund"); //komunikat
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 100, (0 + 40), ALLEGRO_ALIGN_LEFT, "HISTORIA TWOICH GIER :");//komunikat
	al_flip_display();
	fstream plik;
	string nazwaPliku = "Users/nick/" + this->nick + ".txt"; // znajd plik
	string linia;
	int wys = 60;
	int szer =80;
	
	try {
		plik.open(nazwaPliku, std::ios::in); // otwprz plik
		if (plik.good() == true) // jest ok?
		{


			while (!plik.eof())// czytaj jak dlugo istnieje
			{

				getline(plik, linia); // zabierz linie
				al_draw_text(Myfont, al_map_rgb(255, 255, 200),wys, szer, ALLEGRO_ALIGN_LEFT, linia.c_str());//komunikat
				szer=szer +50; // zwieksz szer by nastepny komunikat wyswietlil sie nizej


			}
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
	al_flip_display();
	al_rest(5);


}

void Gracz::ReadList()
{
	string ss;
	fstream plik;
	string linia;
	int punkty = 0;
	string nazwaPliku = "Users/lista.txt"; 
	plik.open(nazwaPliku, std::ios::in | std::ios::out);//otworz plik
	try {
		if (plik.good() == true)// jest ok?
		{


			while (!plik.eof())// jak dlugo istnieje
			{

				getline(plik, linia);// pobierz linie 
				MakeAList(this->pList, linia);// stworz liste 


			}
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

}

void Gracz::MakeAList(List*& pList, string nick)
{
	if (!pList) pList = new List{ nick,nullptr }; // jesli puste to stworz
	else
		return MakeAList(pList->pNext, nick); // jesli istnieje to idz dalej


}

void Gracz::Formularz()
{
	bool done = 0;
	ALLEGRO_EVENT ev1;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL); // czciaka
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Czy posiadasz juz konto ?"); // komunikat
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 640 / 2 - 100, (480 / 4 + 40), ALLEGRO_ALIGN_LEFT, "1 - TAK ");// komunikat
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 640 / 2 - 100, (480 / 4 + 80), ALLEGRO_ALIGN_LEFT, " 2 - NIE");// komunikat
	al_flip_display();
	while (!done) // czekamy na event
	{
		al_wait_for_event(kolejka, &ev1);

		if (ev1.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{

			done = true;
			exit(1);

		}
		else  if (ev1.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ev1.keyboard.keycode == ALLEGRO_KEY_1)
			{
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_flip_display();
				this->ZalogujSie(); // przejdz do funkcji "zaloguj sie"


			}
			if (ev1.keyboard.keycode == ALLEGRO_KEY_2)
			{
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_flip_display();
				this->ZarejestrujSie(); // przejdz do funkcji "zarejestruj sie"


			}
		}
	}	
}

string Gracz::WpiszNick()
{
	string nick = "";
	ALLEGRO_EVENT ev1; // event
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL); // czciaka

	bool done = 0;
	al_register_event_source(kolejka, al_get_keyboard_event_source()); // uzywam klawiatury

	al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Wpisz nick : "); // komunikat

	al_flip_display();
	while (!done)// czekam na event
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
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Wpisz nick : ");

				al_flip_display();
				nick = "";
				done = false;
			}

			else {

				nick.push_back(ev1.keyboard.keycode + 96); // pokazuj na biezaco
				al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 80, ALLEGRO_ALIGN_LEFT, nick.c_str());
				al_flip_display();
			}
		}
	}
	return nick; // zwroc wpisany nick

}

void Gracz::ZarejestrujSie()
{
	bool h = true;
	bool done = 0;
	string nick="";
	ALLEGRO_EVENT ev1;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL); // czciaka
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Wpisz nick : "); // komunikat
	
	al_flip_display();
	while (h)
	{

		
		
		al_clear_to_color(al_map_rgb(20, 75, 80));
		al_flip_display();

		nick = WpiszNick(); // wpisz nick (uzytkownik)
		
		if (SprawdzamNick(nick, this->pList) == true) // sprawdz czy nick istnieje
		{
			
			al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "wybrany nick istnieje, wybierz inny  "); // komunikat

			al_flip_display();
			nick = "";
			done = false;

		}
		else
		{
			al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Udalo sie, nick jest twoj! "); // komunikat

			al_flip_display();
			
			h = false;
			SaveNick(nick); // zapisz nick do bazy danych (plik .txt)
			MakeAList(this->pList, nick); // dodaj do listy nick'ow
			this->nick = nick;
			UserMenu(); // przejdz do menu glownego

		}

	}


}

void Gracz::ZalogujSie()
{
	string nick = "";
	bool sprawdz = false;
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL); // czciaka
	ALLEGRO_EVENT ev1;
	

	bool done = 0;
	al_register_event_source(kolejka, al_get_keyboard_event_source()); // uzywam klawiatury

	nick = WpiszNick(); // wpisz nick (uzytkownik)
	sprawdz = SprawdzamNick(nick, this->pList);// sprawdz czy nick istnieje
	if (sprawdz == true)
	{
		this->nick = nick;

		UserMenu(); // przejdz do menu glownego

	}
	else
	{
		al_clear_to_color(al_map_rgb(20, 75, 80));
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4), ALLEGRO_ALIGN_LEFT, "Nie istnieje gracz o takiej nazwie ! ");// komunikat
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 40, ALLEGRO_ALIGN_LEFT, "1 - Zarejestruj sie ! ");// komunikat
		al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) - 220, (480 / 4) + 80, ALLEGRO_ALIGN_LEFT, "2 - wyjdz ");// komunikat
		al_flip_display();


		while (!done)
		{
			al_wait_for_event(kolejka, &ev1);

			if (ev1.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{

				done = true;
				exit(1);

			}
			else  if (ev1.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				if (ev1.keyboard.keycode == ALLEGRO_KEY_1)
				{
					al_clear_to_color(al_map_rgb(20, 75, 80));
					al_flip_display();
					ZarejestrujSie(); // przejdz do rejestracji
					done = true;
				}
				else if (ev1.keyboard.keycode == ALLEGRO_KEY_2)
				{
					done = true;
					exit(1);
				}


			}
		}

	}

}

bool Gracz::SprawdzamNick(string nick, List*& pList)
{
	if (pList)
	{
		if (pList->nick == nick) return true; // true - czyli istnieje
		else return SprawdzamNick(nick, pList->pNext);

	}

	return false;

}

void Gracz::SaveNick(string nick)
{
	string ss;
	string sss;
	ofstream zapis;
	zapis.open("Users/lista.txt", ios::out | ios::app); // otworz plik
	try {
		if (zapis.good() == true) // jest ok?
		{
			zapis << nick << endl; // zapisz nick

			zapis.close(); // zamknij
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
	
	string plik = "Users/nick/" + nick + ".txt"; // znajdz plik
	ofstream stworz;

	stworz.open(plik, ios::out | ios::app); // otworz plik
	try {
		if (stworz.good() == true) // jest ok ?
		{
			stworz << nick << endl;// zapisz nick
			stworz << "Panstwa-Miasta" << endl;// zapisz wyniki 
			stworz << "Zgadnij-Kto-To?" << endl;// zapisz wyniki 
			stworz << "Familiada" << endl;// zapisz wyniki 
			stworz.close(); //zamknij
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

void Gracz::Show()
{
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 22, NULL); // czciaka

	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 80, (0), ALLEGRO_ALIGN_LEFT, "-----------Panel Gracza -----------------"); // komunikat
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 100, (0 + 40), ALLEGRO_ALIGN_LEFT, "Wybierz:");// komunikat
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 100, (0 + 80), ALLEGRO_ALIGN_LEFT, " 1.Zagraj w Panstwa-Miasta");// komunikat
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 100, (0 + 120), ALLEGRO_ALIGN_LEFT, "2.Zagraj w Zgadnij Kto To?");// komunikat
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 100, (0 + 160), ALLEGRO_ALIGN_LEFT, "3.Zagraj w Familiade");// komunikat
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 100, (0 + 200), ALLEGRO_ALIGN_LEFT, " 4.Wyswietl Historie Gier");// komunikat
	al_draw_text(Myfont, al_map_rgb(255, 255, 200), 100, (0 + 240), ALLEGRO_ALIGN_LEFT, "5.Wyjdz");// komunikat
	al_flip_display();


}

int Gracz::Write()
{
	ALLEGRO_EVENT ev1; // event
	ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 22, NULL); // czciaka
	ALLEGRO_EVENT_QUEUE* kolejka = NULL;
	kolejka = al_create_event_queue(); // nowa kolejka
	bool done = false;
	al_register_event_source(kolejka, al_get_keyboard_event_source()); // uzywam klawiatury

	while (!done) // czekaj na event
	{
		al_wait_for_event(kolejka, &ev1);

		if (ev1.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev1.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		{

			done = true;
			exit(1);

		}
		else  if (ev1.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ev1.keyboard.keycode == ALLEGRO_KEY_1)
			{
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_flip_display();
				return 1;
				done = true;


			}
			if (ev1.keyboard.keycode == ALLEGRO_KEY_2)
			{
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_flip_display();
				return 2;
				done = true;


			}
			if (ev1.keyboard.keycode == ALLEGRO_KEY_3)
			{
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_flip_display();
				al_destroy_event_queue(kolejka);
				return 3;
				done = true;


			}
			if (ev1.keyboard.keycode == ALLEGRO_KEY_4)
			{
				al_clear_to_color(al_map_rgb(20, 75, 80));
				al_flip_display();
				if (this->nick != "gosc")
				{
					wypiszPunkty(); // pokaz na ekran punkty gracza

					al_clear_to_color(al_map_rgb(20, 75, 80));
					al_flip_display();
					UserMenu(); // przejdz do menu glownego
					done = true;
				}
				else
				{
					al_draw_text(Myfont, al_map_rgb(255, 255, 200), 10, (480 / 4 + 40), ALLEGRO_ALIGN_LEFT, "Grasz jako gosc, nie masz histori gier! ");
					al_flip_display();
					al_rest(2);
					al_clear_to_color(al_map_rgb(20, 75, 80));
					al_flip_display();
					UserMenu(); // przejdz do menu glownego
					done = true;

				}

			}
			if (ev1.keyboard.keycode == ALLEGRO_KEY_5)
			{
				done = true;
				exit(1);


			}
		}
	}


}

bool Gracz::UserMenu()
{
	

	al_clear_to_color(al_map_rgb(20, 75, 80));
	al_flip_display();
	vector< Wirtualna*> Wir; // wektor klasy wirtualna

	PanstwaMiasta* PanstwaMiasta1 = new PanstwaMiasta; 
	Wir.push_back(PanstwaMiasta1); // dodaj do wektora
	ZgadnijKtoTo* ZgadnijKtoTo1 = new ZgadnijKtoTo;
	Wir.push_back(ZgadnijKtoTo1);// dodaj do wektora
	Familiada* f1 = new Familiada;
	Wir.push_back(f1);// dodaj do wektora
	int s = Wir.size(); // wielkosc wektora
	for (int i = 0; i < s; i++) // dla wielkosci wektora rob:
	{

		Wir[i]->StworzRanking(); // stworz ranking 
		Wir[i]->nick = this->nick; // zapisz nick do zmiennej

	}

	Show(); // pokaz komunikat

	
	int spr =Write(); // uzytkownik cos wpisuje
	if (spr == 1) PanstwaMiasta1->graj(); // jesli wybral 1 to graj w Panstwa Miasta
	else if (spr == 2) ZgadnijKtoTo1->graj();// jesli wybral 2 to graj w ZgadnijktoTo
	else if (spr == 3) f1->graj();
	// jesli wybral 3 to graj w Familiade

	return false;
}
