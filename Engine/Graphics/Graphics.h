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
        const void Draw(const Geoutils::Vector &cameraPosition,const Geoutils::Vector &renderPos, float screenX, float screenY, float focalDistance) override;
        protected:
        std::string name="wall";
        float halHeight=240;
        float halfWidth=370;
    };

    
}
#endif