#include <iostream>
#include<string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Gracz.h"


using namespace std;



int main()
{
   
    ALLEGRO_EVENT ev1; // tworzenie event'u
    Gracz G1; // tworzenie klasy Gracza
    ALLEGRO_SAMPLE* sample = NULL; // to do muzyki
    ALLEGRO_BITMAP* icon; // to do ikony programu
    
    ALLEGRO_SAMPLE_INSTANCE* sampleInstance = NULL; // to tez do muzyki
    
    G1.ReadList();  // czytamy liste nick'ow
    

    if (!al_init())
    {
        fprintf(stderr, "Failed to initialize allegro!\n");
        return -1;
    }
    // tutaj dodajemy wrzystkie rzeczy z biblioteki allegro jakie bedziemy uzywac
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_audio();////////////////////////
    al_init_acodec_addon(); ///////////////////


    al_reserve_samples(5);/////////////////
    sample = al_load_sample("mjusik.ogg");/////////////// dolaczamy muzyke
    sampleInstance = al_create_sample_instance(sample);/// tworzymy muzyke
    al_set_sample_instance_playmode(sampleInstance, ALLEGRO_PLAYMODE_LOOP); // zapetlamy muzyke
    al_attach_sample_instance_to_mixer(sampleInstance, al_get_default_mixer());

    /* Allokujemy pami�� dla kolejki i sprawdzamy czy funkcja nie zwr�ci�a b��du */
    G1.kolejka = al_create_event_queue();
    

    if (G1.kolejka == NULL)
    {
        fprintf(stderr, "Failed to create event queue!\n");
        return -1;
    }
    
    G1.display = al_create_display(640, 480); // tworzymy display
    if (G1.display == NULL)
    {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }

    if (!al_install_keyboard()) ///setup the keyboard
    {
        al_show_native_message_box(NULL, "Error!", "Failed to install keyboard.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    icon = al_load_bitmap("icon.bmp"); // dolaczamy obrazek jaki ma miec ickona programu
    al_set_window_title(G1.display, "ORDI Game"); // tworzymy tytul aplikaci
    al_set_display_icon(G1.display, icon); // dolaczamy ikone
   
    al_register_event_source(G1.kolejka, al_get_display_event_source(G1.display)); // tworzymy event - wyswietlanie okna
    al_register_event_source(G1.kolejka, al_get_keyboard_event_source()); // tworzymy event- uzywanie klawiatury
    ALLEGRO_BITMAP* obrazek = al_load_bitmap("logo.png"); 
    al_draw_bitmap(obrazek, 0, 0, 0);  // wy�wietlenie bitmapy "obrazek" na "Backbuffer" (bufor ekranu)
    al_flip_display(); // wy�wietlenie aktualnego bufora na ekran
   //al_play_sample_instance(sampleInstance);
   al_play_sample(sample, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0); // zagraj muzyke raz !
   al_rest(4); // tutaj na 4 sekundy zastopuj wyswietlanie
    al_clear_to_color(al_map_rgb(20, 75, 80)); // wyczysc ekran do koloru
    al_flip_display();
    //al_stop_sample_instance(sampleInstance);
    string write= "";
    ALLEGRO_FONT* Myfont = al_load_ttf_font("arial.ttf", 32, NULL); // zalacz czciake

    bool done = 0;
    //tutaj wyswietlamy na ekran 
    al_draw_text(Myfont, al_map_rgb(255, 255, 200), (640 / 2) -220 , (480 / 4), ALLEGRO_ALIGN_LEFT, "----------- Panel Gry ------------");
    al_draw_text(Myfont, al_map_rgb(255, 255, 200), 640 / 2 - 100, (480 / 4 + 40), ALLEGRO_ALIGN_LEFT, "Wybierz:");
    al_draw_text(Myfont, al_map_rgb(255, 255, 200), 640 / 2 - 100 , (480 / 4 +80), ALLEGRO_ALIGN_LEFT, "1.Zaloguj sie");
    al_draw_text(Myfont, al_map_rgb(255, 255, 200), 640 / 2 - 100, (480 / 4 +120), ALLEGRO_ALIGN_LEFT, "2.Graj jako gosc");
    al_draw_text(Myfont, al_map_rgb(255, 255, 200), 640 / 2 - 100, (480 / 4 +160), ALLEGRO_ALIGN_LEFT, "3.Wyjdz");

    al_flip_display();

    // petla do wpisywania odpowiedzi przez uzytkownika
    while (!done)
    {
        
        
        al_wait_for_event(G1.kolejka, &ev1);
        
        if (ev1.type == ALLEGRO_EVENT_DISPLAY_CLOSE) // jezeli przycisk close to zamknij program
        {
        
        done = true;
        exit(1);

        }
        else  if(ev1.type == ALLEGRO_EVENT_KEY_DOWN)  // jezeli jakis przycisk na klawiaturze to ...
        {
            if (ev1.keyboard.keycode == ALLEGRO_KEY_1 ) // jezeli jeden to ...
            {
                al_clear_to_color(al_map_rgb(20, 75, 80));
                al_flip_display();
                G1.Formularz();//.. przejdz do Formularza
                done = true;
               
               
            }
            if (ev1.keyboard.keycode == ALLEGRO_KEY_2) // jezeli dwa to..
            {
                al_clear_to_color(al_map_rgb(20, 75, 80));
                al_flip_display();
                G1.UserMenu(); // .. przejdz jakos gosc do menu gry
                done = true;
             

            }
            if (ev1.keyboard.keycode == ALLEGRO_KEY_3) // jezlei 3 to wyjdz
            {
               
                done = true;
               

            }
        }

            
       
    }
    
    // tutaj na koniec programu usuwamy wszystko co zalaczylismy z ALLEGRO
    al_destroy_bitmap(obrazek); 
    al_destroy_bitmap(icon);
    al_destroy_sample(sample);
    al_destroy_sample_instance(sampleInstance);
    al_destroy_display(G1.display);

       
    return 0;
}
