#include "Node.h"

namespace BaseNodes{
    void Node::UpdateRecursive(){
        this->Update();
        for (int i=0;i<this->children.size();i++){
            this->children[i]->UpdateRecursive();
        }
    }

    void Node::DrawRecursive(){
        this->Draw();
        for (int i=0;i<this->children.size();i++){
            this->children[i]->DrawRecursive();
        }
    }


    void Node::StartRecursive(){
        this->Start();
        for (int i=0;i<this->children.size();i++){
            this->children[i]->StartRecursive();
        }
    }

    void Node::AppendChild(Node *child){
        this->children.push_back(std::make_unique<Node>(child));
    }

}