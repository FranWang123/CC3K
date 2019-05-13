#include <iostream>
#include <vector>
#include <utility>
#include "stair.h"
using namespace std;

Stair::Stair(char type, int row, int col, Character *c):
NormalCell{type, row, col, c}{}

Stair::~Stair() {}

void Stair::prettyPrint(){
    cout << getType();
}

