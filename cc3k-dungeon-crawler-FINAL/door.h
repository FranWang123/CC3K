#ifndef __DOOR_H__
#define __DOOR_H__
#include <iostream>
#include <vector>
#include <utility>
#include "normalCell.h"

class Door : public NormalCell{
public:
    Door(char type, int row, int col, Character *c=nullptr);
    
    ~Door() override;
    
    void prettyPrint() override;
    
    // int canPass() override;
};

#endif
