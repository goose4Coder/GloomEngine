#ifndef NODE_H
#define NODE_H

#include <vector>
#include <memory>
#include <string>
#include <math.h>
#include "../Geoutils/GeoEntities.h"


namespace BaseNodes{
    class Node{
        public:
        Node(){ this->children=std::vector<std::shared_ptr<Node>>(); }
        void UpdateRecursive();
        const void DrawRecursive(float size, float screenX);
        void StartRecursive();
        std::vector<char> SaveRecursive();
        void AppendChild(std::shared_ptr<Node> &child);
        inline const std::string GetName(){ return this->name;}
        virtual void Update(){};
        const virtual void Draw(float size, float screenX){};
        virtual void Start(){};
        inline void Move(float x, float y){
            this->coordinates = Geoutils::Point(x,y);
        }
        inline void MoveBy(float x, float y){
            this->coordinates = Geoutils::Point(this->coordinates.x+x,this->coordinates.y+y);
        }
        inline const Geoutils::Point GetPosition(){return this->coordinates;}
        virtual std::vector<char> Save(){ return std::vector<char>(0);}
        protected:
        std::string name="BaseNode";
        std::vector<std::shared_ptr<Node>> children;
        Geoutils::Point coordinates=Geoutils::Vector(0,0);
    };

    class SceneObject: public Node{
        public:
        SceneObject(float x, float y){ this -> coordinates = Geoutils::Vector(x,y);};
        SceneObject(){ };
        protected:
        std::string name="SceneObject";
        
    };

    class Camera: public BaseNodes::SceneObject{
        public:
        Camera(float x, float y, float distance, float angle, float screenWidth): BaseNodes::SceneObject(x,y){ 
            this->renderDistance=distance;
            this->angle=angle;
            this->focalDistance = screenWidth/2/tan(angle);
        };
        Camera() : BaseNodes::SceneObject(0,0) {

        };
        void DrawObjects(const std::vector<std::shared_ptr<BaseNodes::Node>> &drawables, float screenX, float screenY);
        protected:
        std::string name="Camera";
        float angle;
        float renderDistance;
        float focalDistance;
    };

    class Scene: public Node{
        public:
        Scene(){};
        Scene(std::string name){this->name=name;}
        void Update() override{};
        const void Draw(float size, float screenX) override {};
        const void Draw(float size, float screenX, float screenY);
        void Start() override{};
        void SetCamera(Camera camera) { this->activeCamera = camera; }
        virtual void Load(char *toLoad){};
        protected:
        Camera activeCamera;
    };
}
#endif