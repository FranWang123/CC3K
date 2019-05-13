#include <iostream>
#include <vector>
#include <utility>
#include "treasure.h"
#include "pc.h"


Treasure::Treasure(int value, bool protect, PC* player, char itemType):
Item{itemType, player},protect{protect}, value{value} {}

Treasure::~Treasure() {}

int Treasure::getValue() {
    return value;
}
bool Treasure::isProtect() {
    return protect;
}

void Treasure::useItem(int mag) {
    target->changeGold(getValue());
}

void Treasure::changeProtect(bool f) {
    protect = f;
}

Small::Small(PC* player):
Treasure{1, false, player}{}

Normal::Normal(PC* player):
Treasure{2, false, player} {}

MH::MH(PC* player):
Treasure{4, false, player} {}

DH::DH(PC* player):
Treasure{6, true, player} {}


Small::~Small(){}

Normal::~Normal(){}

MH::~MH(){}

DH::~DH(){}

