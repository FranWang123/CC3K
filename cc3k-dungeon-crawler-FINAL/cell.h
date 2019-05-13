#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include <vector>
#include <utility>
#include "item.h"
class Cell {
    char type;
    int row;
    int col;
    
    
public:
    Cell(char type, int row, int col);
    
    virtual ~Cell();
    
    virtual void prettyPrint()=0;
    
    // virtual int canPass(char type)=0;
    
    int getRow();
    
    int getCol();
    
    char getType();
    
};

#endif
