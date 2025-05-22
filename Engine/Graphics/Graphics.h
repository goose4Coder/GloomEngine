#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <memory>
#include "../Nodes/Node.h"


namespace Graphics{

    class BaseWallDrawer: public BaseNodes::Entity{
        public:
        BaseWallDrawer(): Entity(0,0){};
        BaseWallDrawer(float x,float y): Entity(x,y){};
        BaseWallDrawer(ALLEGRO_COLOR colorToSet) : Entity(0, 0) { this->color = colorToSet; }
        const void Draw(float x, float screenX, float screenY, float perpDistance,bool shaded) override;
        protected:
        std::string name="wall";
        float height=1;
        float width=1;
        ALLEGRO_COLOR color = al_map_rgb(0, 255, 0);
    };

    
}
#endif