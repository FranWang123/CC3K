#ifndef __NORMAL_CELL_H__
#define __NORMAL_CELL_H__
#include <iostream>
#include <vector>
#include <utility>
#include "cell.h"
#include "character.h"

class NormalCell : public Cell {
    Character *charTarget;
    // std::vector<Cell*> neighbours;
    
public:
    
    NormalCell(char type, int row, int col, Character* charTarget = nullptr);
    
    virtual ~NormalCell();
    
    // void attach(Cell *c);
    
    void putCharacter(Character *c);
    
    void removeCharacter();
    
    Character *getCharacter();
    
    bool hasCharacter();
};


#endif
