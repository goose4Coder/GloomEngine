#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <memory>
#include "../Nodes/Node.h"


namespace Graphics{
    using namespace BaseNodes;

    class Drawer: public SceneObject{
        public:
        Drawer(float x, float y): SceneObject(x,y){};
    };

    class CircleDrawer: public Drawer{
        public:
        CircleDrawer(float x,float y): Drawer(x,y){};
        void Update() override{};
        void Draw() override;
        void Start() override{};
    };
}
#endif