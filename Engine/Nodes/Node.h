#ifndef NODE_H
#define NODE_H

#include <vector>
#include <array>
#include <memory>
#include <string>
#include <math.h>
#include "../Geoutils/GeoEntities.h"




namespace BaseNodes{
#define Grid std::array<std::array<int,1000>,1000>

    class Entity{
        public:
        Entity(float x, float y) { this->coordinates = Geoutils::Vector(x, y); };
        Entity(){  }
        virtual void Update() {};
        const virtual void Draw(float size, float screenX) {};
        virtual void Start();
        virtual std::vector<char> Save() {};
        
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
        Geoutils::Point coordinates=Geoutils::Vector(0,0);
    };


    class Camera: public BaseNodes::Entity{
        public:
        Camera(float x, float y, float distance, float angle, float screenWidth): BaseNodes::Entity(x,y){
            this->renderDistance=distance;
            this->angle=angle;
            this->focalDistance = screenWidth/2/tan(angle);
        };
        Camera() : BaseNodes::Entity(0,0) {

        };
        void DrawObjects(const Grid &level,const std::vector<std::shared_ptr<BaseNodes::Entity>> &drawables, float screenX, float screenY);
        protected:
        std::string name="Camera";
        float angle = 0;
        float renderDistance;
        float focalDistance;
    };

    class Scene{
        public:
        Scene(){ };
        Scene(std::string name){this->name=name;}
        const void Draw(float screenX, float screenY);
        void Start();
        void Update();
        void SetCamera(Camera camera) { this->activeCamera = camera; }
        void AppendEntity(std::shared_ptr<Entity>& entity);
        void Load(char *toLoad){};
        std::vector<char> Save();
        inline std::string GetName() { return this->name; }
        protected:
        std::string name;
        Camera activeCamera;
        std::vector<std::shared_ptr<Entity>> entities = std::vector<std::shared_ptr<Entity>>();
        std::vector<std::shared_ptr<Entity>> environnementSingletones= std::vector<std::shared_ptr<Entity>>();
        Grid level;
        Grid currentLevel;
        std::string name;
    };
}
#endif