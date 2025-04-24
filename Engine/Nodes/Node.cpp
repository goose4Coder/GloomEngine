#include "Node.h"
#include <iostream>

namespace BaseNodes{
    #define STEP_DISTANCE 1

    void Node::UpdateRecursive(){
        this->Update();
        for (int i=0;i<this->children.size();i++){
            this->children[i]->UpdateRecursive();
        }
    }

    const void Node::DrawRecursive(float size , float screenX) {
        this->Draw(size, screenX);
        for (int i=0;i<this->children.size();i++){
            this->children[i]->DrawRecursive(size,this->children[i]->GetPosition().x);
        }
    }


    void Node::StartRecursive(){
        this->Start();
        for (int i=0;i<this->children.size();i++){
            this->children[i]->StartRecursive();
        }
    }

    std::vector<char> Node::SaveRecursive(){
        auto toReturn=this->Save();
        for (int i=0;i<this->children.size();i++){
            auto child=this->children[i]->SaveRecursive();
            toReturn.insert(toReturn.end(),child.begin(),child.end());
        }
        return toReturn;
    }

    void Node::AppendChild(std::shared_ptr<Node> &child){
        this->children.push_back(std::shared_ptr<Node>(child));
    }

    void Camera::DrawObjects(const std::vector<std::shared_ptr<BaseNodes::Node>>& drawables, float screenX, float screenY){
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
    }

}