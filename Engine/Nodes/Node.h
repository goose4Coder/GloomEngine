#ifndef NODE_H
#define NODE_H

#include <vector>
#include <array>
#include <memory>
#include <string>
#include <math.h>
#include <allegro5/allegro.h>
#include "../Geoutils/GeoEntities.h"




namespace BaseNodes{
    typedef struct ALLEGRO_KEYBOARD_STATE ALLEGRO_KEYBOARD_STATE;
#define Grid std::array<std::array<int,11>,11>

    class Entity{
        public:
        Entity(float x, float y) { this->coordinates = Geoutils::Vector(x, y); };
        Entity(){  }
        virtual void Update(ALLEGRO_KEYBOARD_STATE keyState, std::vector<std::shared_ptr<Entity>> entities, Entity &camera, std::vector<std::shared_ptr<Entity>> env) {};
        const virtual void Draw(const Geoutils::Vector &cameraPosition,const Geoutils::Vector &renderPos, float screenX, float screenY, float focalDistance) {};
        virtual void Start(){};
        
        inline const std::string GetName(){ return this->name;}
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
            this->focalDistance = (screenWidth/2)/tan(angle);
        };
        Camera() : BaseNodes::Entity(0,0) {

        };
        void DrawObjects(const Grid &level,const std::vector<std::shared_ptr<BaseNodes::Entity>> &entities,const std::vector<std::shared_ptr<BaseNodes::Entity>> &env, float screenX, float screenY);
        protected:
        std::string name="Camera";
        float angle = 0;
        float rotation = 0;
        float renderDistance=0;
        float focalDistance=0;
    };

    class Scene{
        public:
        Scene(){ };
        Scene(std::string name, Grid level){
            this->name=name;
            this->level=level;
            this->currentLevel = level;
        }
        const void Draw(float screenX, float screenY);
        void Start();
        void Update();
        
        inline void SetCamera(Camera camera) { 
            this->activeCamera = camera;
            this->activeCamera.Move(this->level.size()/2+1,this->level.size()/2+1);
         }
        void AppendEntity(std::shared_ptr<Entity> entity);
        void AppendEnv(std::shared_ptr<Entity> env);
        void Load(char *toLoad){};
        std::vector<char> Save();
        inline std::string GetName() { return this->name; }
        protected:
        ALLEGRO_KEYBOARD_STATE keyState;
        std::string name;
        Camera activeCamera;
        std::vector<std::shared_ptr<Entity>> entities = std::vector<std::shared_ptr<Entity>>();
        std::vector<std::shared_ptr<Entity>> environnementSingletones= std::vector<std::shared_ptr<Entity>>();
        Grid level;
        Grid currentLevel;
    };
}
#endif