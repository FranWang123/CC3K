#ifndef __STAIR_H__
#define __STAIR_H__
#include <iostream>
#include <vector>
#include <utility>
#include "normalCell.h"

class Stair : public NormalCell {
public:
    Stair(char type, int row, int col, Character *c=nullptr);
    
    ~Stair() override;
    
    void prettyPrint() override;
    
    // int canPass() override;
    
};

#endif
