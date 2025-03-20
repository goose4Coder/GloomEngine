
#include "Engine.h"

using namespace GloomEngine;


void GloomEngine::Init(){
  currentScene.AppendChild(new Graphics::CircleDrawer(DISPLAY_WIDTH/2,DISPLAY_HEIGHT/2));
}

int GloomEngine::RunGame(){
    al_init();
     
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    bool redraw = true;

    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
   if(!display) {
      std::cout<<stderr<< "failed to create display!\n";
      al_destroy_timer(timer);
      return -1;
   }

    event_queue = al_create_event_queue();

    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
    }

    if(!event_queue) {
     al_destroy_display(display);
     al_destroy_timer(timer);
     std::cout<<"Err event qeue"<<std::endl;
     return -1;
    }

    if ( !al_init_primitives_addon() )
    {
        std::cout << "failed to init addons!" << std::endl;
        return false;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_clear_to_color(al_map_rgb(0,0,0));

    al_flip_display();

    GloomEngine::Init();
    currentScene.StartRecursive();

    al_start_timer(timer);
    

    while(notExitGame)
    {
     ALLEGRO_EVENT ev;
     al_wait_for_event(event_queue, &ev);
     
     if(ev.type == ALLEGRO_EVENT_TIMER) {
      currentScene.UpdateRecursive();
     }else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        break;
      }

     if (al_is_event_queue_empty(event_queue)){
      al_clear_to_color(al_map_rgb(0, 0, 0));
      currentScene.DrawRecursive();
      al_flip_display();
     }
    }

    
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
     
     
}