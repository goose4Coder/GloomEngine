#include "Graphics.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>

namespace Graphics{

const void CircleDrawer::Draw(float size, float screenX){
    auto where=this->coordinates;
    al_draw_filled_circle(370+screenX,240, size, al_map_rgb( 0, 255, 0 ) );
}

const void RectangleDrawer::Draw(float size, float screenX) {
    auto where = this->coordinates;
    al_draw_filled_rectangle(370 + screenX + this->width/2*size, 240 + this->height / 2 * size, 370 + screenX - this->width / 2 * size, 240 - this->height / 2 * size, al_map_rgb(0, 255, 0));
    /*al_draw_filled_rectangle(370 + screenX + this->width / 2 * size, 250, screenX, 240, al_map_rgb(0, 255, 0));*/
}

}