#include <iostream>
#include <vector>
#include <utility>
#include "spawn.h"
using namespace std;

Spawn::Spawn(char type, int row, int col, Character* c, Item *item):
NormalCell{type, row, col, c}, item{item} {}

Spawn::~Spawn() {
    item=nullptr;
}


void Spawn::prettyPrint(){
    if(hasCharacter() && hasItem()){
    } else if(hasCharacter()){
        cout << getCharacter()->getName();
    } else if (hasItem()) {
        cout << getItem()->getType();
    } else {
        cout << getType();
    }
}


void Spawn::putItem(Item *i){
    item = i;
}


void Spawn::removeItem(){
    item = nullptr;
}


Item * Spawn::getItem(){
    return item;
}


bool Spawn::hasItem(){
    return (item != nullptr);
}

