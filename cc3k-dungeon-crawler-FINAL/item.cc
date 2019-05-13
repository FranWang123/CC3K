#include <stdio.h>
#include "item.h"

char Item::getType() {
    return itemType;
}
int Item::getRow() {
    return row;
}

int Item::getCol() {
    return col;
}

Item::Item(char itemType, PC* target): row{0},
col{0}, itemType{itemType}, target{target} {}

Item::~Item() {target=nullptr;}

void Item::changePosition(int x, int y) {
    row = x;
    col = y;
}


void Item::useItem(int mag) {}
