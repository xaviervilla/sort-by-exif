#include "ModelList.hpp"

ModelList::ModelList(){
    this->headModel = new Model();
    this->tailModel = headModel->next();
}


ModelList::ModelList(std::string model){
    this->headModel = new Model(model);
    this->tailModel = headModel->next();
}


void ModelList::addModel(std::string model, bool display){
    // Create node for our new model
    Model *temp = new Model(model);
    
    // This is the case when the linked list is empty
    if(!headModel->modelString().compare("NULL")){
        if(display)
            std::cout <<  "Desired device detected:\t";
        std::cout  << model << std::endl;
        headModel = temp;
        tailModel = temp->next();
    }
    
    // This is the case when the list is not empty
    else{
        // Iterate through our linked list to find match
        Model *it = headModel;
        while(it->next() != tailModel){
            if(it->matches(model)){
                return;
            }
            it = it->next();
        }
        if(it->matches(model)){
            return;
        }
        if(display)
            std::cout <<  "Desired device detected:\t";
        std::cout  << model << std::endl;
        it->setNext(temp);
        tailModel = it->next()->next();
    }
}

void ModelList::printList(){
    Model *temp = headModel;
    while(temp!=NULL){
        std::cout << temp->modelString() << std::endl;
        temp = temp->next();
    }
}

Model* ModelList::getHead(){
    return this->headModel;
}

Model* ModelList::getTail(){
    return this->tailModel;
}

bool ModelList::unwanted(std::string model){
    
    Model *it = headModel;
    while(it!=tailModel){
        if(it->matches(model)){
            return false; // we have  wanted model
        }
        it = it->next();
    }
    
    return true;
}

ModelList::~ModelList(){
    Model *it = headModel;
    Model *tmp;
    while(it!=tailModel){
        tmp = it;
        it = it->next();
        delete tmp;
    }
    delete it;
}