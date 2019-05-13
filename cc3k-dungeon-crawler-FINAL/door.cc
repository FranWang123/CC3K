#include <iostream>
#include <vector>
#include <utility>
#include "door.h"
using namespace std;

Door::Door(char type, int row, int col, Character *c): NormalCell{type, row, col, c} {}

Door::~Door() {}

void Door::prettyPrint(){
    if(hasCharacter()){
        
        cout << getCharacter()->getName();
    } else {
        cout << getType();
    }
}
