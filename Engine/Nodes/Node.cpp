#include "Node.h"
#include "../Graphics/Graphics.h"
#include <iostream>

namespace BaseNodes{
    #define STEP_DISTANCE 1

    void Scene::AppendEntity(std::shared_ptr<Entity> entity) {
        this->entities.push_back(std::shared_ptr<Entity>(entity));
    }
    void Scene::AppendEnv(std::shared_ptr<Entity> env) {
        this->environnementSingletones.push_back(std::shared_ptr<Entity>(env));
    }

    const void Scene::Draw(float screenX, float screenY){
        
        this->activeCamera.DrawObjects(this->currentLevel,this->entities,this->environnementSingletones,screenX,screenY);
        this->currentLevel = this->level;
    }

    void Scene::Start() {
        for (size_t i = 0; i < this->entities.size(); i++)
        {
            this->entities[i]->Start();
        }
        this->currentLevel = this->level;
    }

    void Scene::Update() {
        al_get_keyboard_state(&this->keyState);
        this->activeCamera.Update(this->keyState, this->entities,this->activeCamera,this->environnementSingletones);
        for (size_t i = 0; i < this->entities.size(); i++)
        {
            auto pos = this->entities[i]->GetPosition();
            if (pos.x<currentLevel.size()&& pos.x > 0&& pos.y < currentLevel.size() && pos.y > 0)
            this->currentLevel[pos.x][pos.y] = -int(i) - 1;
        }
        for (size_t i = 0; i < this->entities.size(); i++)
        {
            this->entities[i]->Update(this->keyState, this->entities, this->activeCamera, this->environnementSingletones);
        }
    }

    std::vector<char> Scene::Save() {
        auto toReturn = std::vector<char>();
        auto saving = std::vector<char>();
        for (size_t i = 0; i < this->entities.size(); i++)
        {
            saving = this->entities[i]->Save();
            toReturn.insert(toReturn.end(), saving.begin(), saving.end());
        }
        return toReturn;

    }
    void Camera::DrawObjects(const Grid &level,const std::vector<std::shared_ptr<BaseNodes::Entity>> &entities,const std::vector<std::shared_ptr<BaseNodes::Entity>> &env, float screenX, float screenY){
        std::vector<Geoutils::Vector> rays = std::vector<Geoutils::Vector>();
        rays.push_back(Geoutils::Vector(1, 0).Rotate(1.57 - this->angle));
        for (float i = 1.57-this->angle; i < 1.57 + this->angle; i+=0.5)
        {
            rays.push_back(Geoutils::Vector(1,0).Rotate(i+this->rotation));
        }
        float deltaX = 0;
        for (size_t i = 0; i < rays.size(); i++)
        {
            size_t toDraw = 0;
            float distance = 0;

            float toDrawX = 0;
            float toDrawY = 0;
            deltaX=0;
            for (size_t x = 0; x < level.size(); x++)
            {
                int toDraw = 0;
                distance = 10000;
                
                toDrawX = 0;
                toDrawY = 0;
                //here error
                // std::cout << "cast "<<i<<" on "<<x<<std::endl;
                auto y = rays[i].y/rays[i].x*(x-this->coordinates.x)+this->coordinates.y;
                if((Geoutils::Vector(x,y)-this->coordinates).GetNorm()<distance&&y<level.size()&&y>=0&&cos(-this->rotation)*(x - this->coordinates.x)<=0){
                    if (level[size_t(x)][size_t(y)]!=0) {
                       /* std::cout << "hit ray " << x << " " << y << " h" << level[size_t(x)][size_t(y)] << std::endl;*/
                    }
                    else {
                       /* std::cout << "non hit ray " << x << " " << y << " h" << level[size_t(x)][size_t(y)] << std::endl;*/
                    }
                    distance = (Geoutils::Vector(x,y)-this->coordinates).GetNorm();
                    deltaX= x-this->coordinates.x;
                    toDraw = level[size_t(x)][size_t(y)];
                    toDrawX = x;
                    toDrawY = y;
                    
                }
                if (toDraw > 0) {
                    env[-1 + level[size_t(toDrawX)][size_t(toDrawY)]]->Draw(this->coordinates, Geoutils::Vector(toDrawX, toDrawY), screenX, screenY, this->focalDistance);
                }
                else if (toDraw < 0) {
                    entities[-1 - level[size_t(toDrawX)][size_t(toDrawY)]]->Draw(this->coordinates, Geoutils::Vector(toDrawX, toDrawY), screenX, screenY, this->focalDistance);
                }
                /*level[size_t(toDrawX)][size_t(toDrawY)] = 0;*/

            }
            
        }
        
        
        
    }

    

}