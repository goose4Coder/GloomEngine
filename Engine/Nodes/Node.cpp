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
        for (float x = 0; x < screenX; x+=1)
        {
            
            float cameraX = 2 * x / screenX - 1; //x-coordinate in camera space
            float rayDirX = this->direction.x + this->planeVector.x * cameraX;
            float rayDirY = this->direction.y + this->planeVector.y * cameraX;
            auto ray = Geoutils::Vector(rayDirX,rayDirY);
            /*rays.push_back(Geoutils::Vector((x/screenX)*2-1,focalDistance));*/
            float deltaDistX = (ray.x == 0) ? 1e30 : std::abs(1 / ray.x);
            float deltaDistY = (ray.y == 0) ? 1e30 : std::abs(1 / ray.y);
            int stepX;
            int stepY;
            float sideDistX;
            float sideDistY;

            bool hit = 0; //was there a wall hit?
            int side;
            float mapX = floor(this->coordinates.x);
            float mapY = floor(this->coordinates.y);
            if (ray.x < 0)
            {
                stepX = -1;
                sideDistX = (this->coordinates.x - mapX) * deltaDistX;
            }
            else
            {
                stepX = 1;

                sideDistX = (mapX + 1.0 - this->coordinates.x) * deltaDistX;
            }
            if (ray.y < 0)
            {
                stepY = -1;
                sideDistY = (this->coordinates.y - mapY) * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (mapY + 1.0 - this->coordinates.x) * deltaDistY;
            }
            while (hit == 0)
            {
                //jump to next map square, either in x-direction, or in y-direction
                if (sideDistX < sideDistY)
                {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }
                else
                {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }

                //Check if ray has hit a wall
                if (mapX >= level.size() || mapY >= level.size() || mapX < 0 || mapY < 0) {
                    break;
                }
                if (level[size_t(mapX)][size_t(mapY)] != 0) hit = 1;
            }
            if (hit) {
                float perpWallDist = 1;
                if (side == 0) perpWallDist = (sideDistX - deltaDistX);
                else          perpWallDist = (sideDistY - deltaDistY);
                if (level[size_t(mapX)][size_t(mapY)] > 0) {
                    env[level[size_t(mapX)][size_t(mapY)]-1]->Draw(x, screenX, screenY, perpWallDist,bool(side));
                }
            }
        }
        
        
        
        
    }

    

}