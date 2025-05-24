#include "Graphics.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>

namespace Graphics{

const void BaseWallDrawer::Draw(float x, float screenX, float screenY, float perpDistance, bool shaded){
    float lineHeight = (screenY /2 /perpDistance)*this->height;
    /*std::cout << cameraPosition.x<< " " << renderPos.x << " " << renderPos.y << std::endl;*/
    auto colorN = this->color;
    if (shaded) {
        colorN.r /= 2;
        colorN.g /= 2;
        colorN.b /= 2;
    }
    al_draw_line(x, screenY / 2 + lineHeight, x, screenY / 2 - lineHeight, this->color, 1);
}



}