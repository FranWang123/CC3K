#include <iostream>
#include <vector>
#include <utility>
#include "passage.h"
using namespace std;


Passage::Passage(char type, int row, int col, Character *c):
NormalCell{type, row, col, c}{}

Passage::~Passage(){}

void Passage::prettyPrint(){
    if(hasCharacter()){
        cout << getCharacter()->getName();
    } else {
        cout << getType();
    }
}
