
#include "potion.h"
#include "pc.h"
#include "character.h"

using namespace std;


int random7(int x, int y){
    int ran;
    ran = x + (rand() % (y - x + 1));
    return ran;
}

Potion::Potion(PC* player, char itemType): Item{itemType, player} {}

Potion::~Potion() {}

string Potion::getPotionType() {
    return potionType;
}


RH::RH(PC* player): Potion(player) {potionType = "RH"; }
BA::BA(PC* player): Potion(player) {potionType = "BA"; }
BD::BD(PC* player): Potion(player) {potionType = "BD"; }
PH::PH(PC* player): Potion(player) {potionType = "PH"; }
WD::WD(PC* player): Potion(player) {potionType = "WD"; }
WA::WA(PC* player): Potion(player) {potionType = "WA"; }

RH::~RH() {}
BA::~BA() {}
BD::~BD() {}
PH::~PH() {}
WD::~WD() {}
WA::~WA() {}

void RH::useItem(int mag) {
    int rad = random7(1, 10);
    
    int max_HP = target->getMax();
    int cur_HP = target->getHP();
    Vampire *v = dynamic_cast<Vampire *>(target);
    if(v){
        
        v->VchangeHP(rad);
    } else {
        target->changeHP((rad*mag)/100);
    }
}

void BA::useItem(int mag) {
    int cur_Atk = target->getAtk();
    target->changeAtk((mag*5)/100);
}

void BD::useItem(int mag) {
    int cur_Def = target->getDef();
    target->changeDef((mag*5)/100);
}

void PH::useItem(int mag) {
    int rad0 = random7(1, 10);
    int rad = 0-rad0;
    
    int max_HP = target->getMax();
    int cur_HP = target->getHP();
    
    Vampire *v = dynamic_cast<Vampire *>(target);
    if(v){
        
        v->VchangeHP(rad);
    } else {
        target->changeHP((rad*mag)/100);
    }
}


void WA::useItem(int mag) {
    int cur_Atk = target->getAtk();
    target->changeAtk(0-(mag*5)/100);
}

void WD::useItem(int mag) {
    int cur_Def = target->getDef();
    target->changeDef(0-(mag*5)/100);
}
