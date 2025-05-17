#include "Graphics.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>

namespace Graphics{

const void BaseWallDrawer::Draw(const Geoutils::Vector &cameraPosition,const Geoutils::Vector &renderPos, float screenX, float screenY, float focalDistance){
    auto delta=cameraPosition-renderPos;
    auto offsetX = screenX/2+(delta.x * focalDistance / delta.GetNorm());
    /*std::cout << cameraPosition.x<< " " << renderPos.x << " " << renderPos.y << std::endl;*/
    al_draw_filled_rectangle(offsetX,screenY/2*(delta.y+1)/delta.y*this->height, offsetX+this->width, screenY / 2 * (delta.y -1) / delta.y * this->height, this->color);
}



}