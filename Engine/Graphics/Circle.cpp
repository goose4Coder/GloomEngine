#include "Graphics.h"
#include <allegro5/allegro_primitives.h>

using namespace Graphics;

void CircleDrawer::Draw(){
    auto where=this->coordinates.GetCoordinates();
    al_draw_filled_circle(where.x,where.y, 20, al_map_rgb( 0, 255, 0 ) );
}