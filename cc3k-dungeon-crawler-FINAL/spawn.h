#ifndef __SPAWN_H__
#define __SPAWN_H__
#include <iostream>
#include <vector>
#include <utility>
#include "normalCell.h"
#include "item.h"

class Spawn: public NormalCell {
    Item *item;
    
public:
    Spawn(char type, int row, int col, Character *c = nullptr, Item* item = nullptr);
    
    ~Spawn() override;
    
    void prettyPrint() override;
    
    // int canPass();
    
    void putItem(Item *);
    
    void removeItem();
    
    Item * getItem();
    
    bool hasItem();
};

#endif
