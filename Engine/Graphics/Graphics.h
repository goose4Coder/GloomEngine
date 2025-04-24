#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <memory>
#include "../Nodes/Node.h"


namespace Graphics{

    class Drawer: public BaseNodes::SceneObject{
        public:
        Drawer(float x, float y): BaseNodes::SceneObject(x,y){};
    };

    

    class CircleDrawer: public Drawer{
        public:
        CircleDrawer(float x,float y): Drawer(x,y){};
        void Update() override{};
        const void Draw(float size, float screenX) override;
        void Start() override{};
        protected:
        std::string name="circle";
    };

    class RectangleDrawer : public Drawer {
    public:
        RectangleDrawer(float x, float y, float width, float height) : Drawer(x, y) {
            this->width=width;
            this->height = height;
        };
        RectangleDrawer(float x, float y) : Drawer(x, y) {};
        void Update() override {};
        const void Draw(float size, float screenX) override;
        void Start() override {};
    protected:
        std::string name = "rectangle";
        float height=3;
        float width=1;
    };
    
}
#endif