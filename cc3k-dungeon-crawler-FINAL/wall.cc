#include <iostream>
#include <vector>
#include <utility>
#include "wall.h"
using namespace std;

Wall::Wall(char type, int row, int col): Cell(type, row, col) {}

Wall::~Wall(){}

void Wall::prettyPrint(){
    cout << getType();
}

