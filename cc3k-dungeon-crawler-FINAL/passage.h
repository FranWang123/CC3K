#ifndef __PASSAGE_H__
#define __PASSAGE_H__
#include <iostream>
#include <vector>
#include <utility>
#include "normalCell.h"


class Passage : public NormalCell {
public:
    Passage(char type, int row, int col, Character *c=nullptr);
    
    ~Passage() override;
    
    void prettyPrint() override;
    
    // int canPass(char c) override;
};

#endif

