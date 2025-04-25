#include "Node.h"
#include <iostream>

namespace BaseNodes{
    #define STEP_DISTANCE 1

    void Scene::AppendEntity(std::shared_ptr<Entity>& entity) {
        this->entities.push_back(std::shared_ptr<Entity>(entity));
    }

    const void Scene::Draw(float screenX, float screenY){\
        
        this->activeCamera.DrawObjects(this->currentLevel,this->entities,screenX,screenY);
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
        for (size_t i = 0; i < this->entities.size(); i++)
        {
            auto pos = this->entities[i]->GetPosition();
            this->currentLevel[pos.x][pos.y] = -i - 1;
        }
        for (size_t i = 0; i < this->entities.size(); i++)
        {
            this->entities[i]->Update();
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
    /*void Camera::DrawObjects(const std::vector<std::shared_ptr<BaseNodes::Node>>& drawables, float screenX, float screenY){
        for (size_t i = 0; i < drawables.size(); i++)
        {
            
            auto pos = drawables[i].get()->GetPosition();
            if(pos.y>0&&pos.GetNorm()<=this->renderDistance&&sin(this->angle)*pos.GetNorm()>=abs(pos.x)){
                std::cout << i << std::endl;
                drawables[i].get()->DrawRecursive(screenY/pos.GetNorm(),(this->focalDistance/pos.y)*pos.x);
            }

        }
        
    }

    const void Scene::Draw(float distance, float screenX, float screenY){
        this->activeCamera.DrawObjects(this->children, screenX, screenY);
    }*/

}