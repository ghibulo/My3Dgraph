

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "CoordSystem.h"

const double delta = 10;

double myFunction(double x, double z) {

    return 0.01*x*x+0.01*z*z;
}

int main(int argc, char **argv){

    CoordSystem cosyst(Pos2(320,240),Pos3(1,0,0),Pos3(0,1,0),Pos3(0,0,1));


   if(!al_init()){
      fprintf(stderr, "Failed to initialize Allegro.\n");
      return -1;
   }

   al_init_font_addon(); // initialize the font addon
   al_init_ttf_addon();// initialize the ttf (True Type Font) addon

   ALLEGRO_DISPLAY *display = al_create_display(640,480);
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

   al_clear_to_color(al_map_rgb(50,10,70));
   al_draw_text(font, al_map_rgb(255,255,255), 640/2, (480/4),ALLEGRO_ALIGN_CENTRE, "Vlastni 3D grafy");
   Pos2 bod1=cosyst.getAbsPosition(Pos3(0.5,0,0));
   Pos2 bod2=cosyst.getAbsPosition(Pos3(100,200,0));

   int y;
   for (int z=-100;z<100;z+=delta) {
       y = myFunction(-101,z);
       bod1=cosyst.getAbsPosition(Pos3(-101,y,z));
       for (int x=-100;x<100;x++) {
            y=myFunction(x,z);
            bod2=cosyst.getAbsPosition(Pos3(x,y,z));
            al_draw_line(bod1.x, bod1.y, bod2.x, bod2.y,al_map_rgb(255,0,255) , 1);
            bod1=bod2;
            //al_rest(0.5);
            //al_flip_display();
       }
   }

      for (int x=-100;x<100;x+=delta) {
       y = myFunction(x,-101);
       bod1=cosyst.getAbsPosition(Pos3(x,y,-101));
       for (int z=-100;z<100;z++) {
            y=myFunction(x,z);
            bod2=cosyst.getAbsPosition(Pos3(x,y,z));
            al_draw_line(bod1.x, bod1.y, bod2.x, bod2.y,al_map_rgb(255,0,255) , 1);
            bod1=bod2;
            //al_rest(0.5);
            //al_flip_display();
       }
   }


   al_flip_display();

   al_rest(10.0);

   al_destroy_display(display);

   return 0;
}
