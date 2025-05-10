#include "Graphics.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>

namespace Graphics{

const void BaseWallDrawer::Draw(const Geoutils::Vector &cameraPosition,const Geoutils::Vector &renderPos, float screenX, float screenY, float focalDistance){
    auto delta=cameraPosition-renderPos;
    auto scaleX = delta.y/focalDistance*100;
    al_draw_filled_rectangle(screenX/2+((delta.x+this->halfWidth)*scaleX),screenY/2+screenY/2/delta.GetNorm(),screenX/2+((delta.x-this->halfWidth)*scaleX),screenY/2-halHeight/delta.GetNorm(), al_map_rgb(0,255,0));
}



}