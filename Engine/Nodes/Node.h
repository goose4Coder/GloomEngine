#ifndef NODE_H
#define NODE_H

#include <vector>
#include <memory>
#include "../Geoutils/GeoEntities.h"


namespace BaseNodes{
    class Node{
        public:
        Node(){ this->children=std::vector<std::unique_ptr<Node>>(); }
        void UpdateRecursive();
        void DrawRecursive();
        void StartRecursive();
        void AppendChild(Node *child);
        virtual void Update()=0;
        virtual void Draw()=0;
        virtual void Start()=0;
        protected:
        std::vector<std::unique_ptr<Node>> children;
    };

    class SceneObject: public Node{
        public:
        SceneObject(float x, float y):coordinates(Geoutils::Point(x,y)){};
        SceneObject():coordinates(Geoutils::Point(0,0)){};
        inline void Move(float x, float y){
            this->coordinates = Geoutils::Point(x,y);
        }
        inline void MoveBy(float x, float y){
            auto init = this->coordinates.GetCoordinates();
            this->coordinates = Geoutils::Point(init.x+x,init.y+y);
        }
        inline Geoutils::Point GetPosition(){return this->coordinates;}
        protected:
        Geoutils::Point coordinates;
    };

    class Scene: public Node{
        void Update() override{};
        void Draw() override{};
        void Start() override{};
    };
}
#endif