#include <stdio.h>
#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "CoordSystem.h"
#define NDEBUG

const double delta = 10;
const int hr = 200;


double myFunction(double x, double z) {

    return 0.01*x*x-0.01*z*z-200;
}

void refreshScreen(ALLEGRO_BITMAP *bg, ALLEGRO_BITMAP *sc, ALLEGRO_DISPLAY *display) {
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap(sc,0,0,0);
    al_flip_display();
    al_set_target_bitmap(sc);
    al_draw_bitmap(bg,0,0,0);
}

int main(int argc, char **argv){

    CoordSystem cosyst(Pos2(512,384),Pos3(1,0,0),Pos3(0,1,0),Pos3(0,0,1));
    //cosyst.addToBeta(M_PI/3);
    #ifdef DEBUG
    std::cout << cosyst.vx.x << "," << cosyst.vx.y << ", "<< cosyst.vx.z << ", " << cosyst.vx.alpha << ", " << cosyst.vx.beta << std::endl;
    std::cout << cosyst.vy.x << "," << cosyst.vy.y << ", "<< cosyst.vy.z << ", " << cosyst.vy.alpha << ", " << cosyst.vy.beta << std::endl;
    std::cout << cosyst.vz.x << "," << cosyst.vz.y << ", "<< cosyst.vz.z << ", " << cosyst.vz.alpha << ", " << cosyst.vz.beta << std::endl;
    #endif

   if(!al_init()){
      fprintf(stderr, "Failed to initialize Allegro.\n");
      return -1;
   }

   al_init_font_addon(); // initialize the font addon
   al_init_ttf_addon();// initialize the ttf (True Type Font) addon




   ALLEGRO_DISPLAY *display = al_create_display(1024,768);
   ALLEGRO_BITMAP *scr = NULL, *backgr = NULL;
   al_init_primitives_addon();

   if (!display){
      fprintf(stderr, "Failed to create display.\n");
      return -1;
   }

   ALLEGRO_FONT *font = al_load_ttf_font("angeline.ttf",72,0 );

   if (!font){
      fprintf(stderr, "Could not load 'pirulen.ttf'.\n");
      return -1;
   }

   scr = al_create_bitmap(1024, 768);
   backgr = al_create_bitmap(1024, 768);
   if ((!scr)||(!backgr)) {
      fprintf(stderr, "failed to create bitmap!\n");
      al_destroy_display(display);
      return -1;
   }

   al_set_target_bitmap(backgr);
   al_clear_to_color(al_map_rgb(50,10,70));
   al_draw_text(font, al_map_rgb(255,255,255), 640/2, (480/4),ALLEGRO_ALIGN_CENTRE, "Vlastni 3D grafy");



   al_set_target_bitmap(scr);
   al_draw_bitmap(backgr,0,0,0);
   refreshScreen(backgr, scr, display);

   Pos2 bod1=cosyst.getAbsPosition(Pos3(0.5,0,0));
   int y;

   while (true) {
       //parted according to z
       for (int z=-hr;z<hr;z+=delta) {
           y = myFunction(-hr-1,z);
           bod1=cosyst.pos3Topos2(Pos3(-hr-1,y,z));
           for (int x=-hr;x<hr;x++) {
                y=myFunction(x,z);
                bod1 = cosyst.drawLine(bod1,Pos3(x,y,z));
           }
       }
       //parted according to x
       for (int x=-hr;x<hr;x+=delta) {
           y = myFunction(x,-hr-1);
           bod1=cosyst.pos3Topos2(Pos3(x,y,-hr-1));
           for (int z=-hr;z<hr;z++) {
                y=myFunction(x,z);
                bod1 = cosyst.drawLine(bod1,Pos3(x,y,z));
           }
       }
       refreshScreen(backgr, scr, display);
       cosyst.addToAlpha(0.005);
   }

   al_destroy_display(display);

   return 0;
}
