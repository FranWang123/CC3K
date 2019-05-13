#include "pc.h"
#include <sstream>
using namespace std;


PC::PC(int initHP, int initAtk, int initDef, int damageE):
Character{initHP, initAtk, initDef,0}, max{initHP}, damageE{damageE}{
    name = '@';
}

PC::~PC() {}

void PC::changeDamageE(int amount) {
    damageE= amount;
}

int PC::getDamageE() {
    int result = damageE;
    damageE = 0;
    return result;
}

void PC::pickUpItem(Item &i) {
    i.useItem();
}

int PC::getMax() {
    return max;
}

int random6(int x, int y){
    int ran;
    ran = x + (rand() % (y - x + 1));
    return ran;
}

void PC::attack(Enemy  *target) {
    Shade *s = dynamic_cast<Shade *>(this);
    if(s){
        target->hurt(s);
    }
    
    
    Goblin *g = dynamic_cast<Goblin *>(this);
    if(g){
        target->hurt(g);
    }
    
    Drow *d = dynamic_cast<Drow *>(this);
    if(d){
        target->hurt(d);
    }
    
    Vampire *v = dynamic_cast<Vampire *>(this);
    if(v){
        target->hurt(v);
    }
    if (target->getHP() <= 0 && !g) {
        changeGold(target->getGold());
    } else if (target->getHP() <= 0 && g) {
        changeGold(5);
    }
}




int random3(int x, int y){
    int ran;
    ran = x + (rand() % (y - x + 1));
    return ran;
}



void PC::hurt(Merchant & m) {
    int effect = damage(&m);
    changeHP(effect);
}

void PC::hurt(Dragon & d) {
    int effect = damage(&d);
    changeHP(effect);
}

void PC::hurt(Elf & e) {
    int effect = damage(&e, 2);
    changeHP(effect);
}

void PC::hurt(Dwarf & d) {
    int effect = damage(&d);
    changeHP(effect);
}

void PC::hurt(Halfling & h) {
    int effect = damage(&h);
    changeHP(effect);
}

void PC::hurt(Orcs & o) {
    int effect = damage(&o);
    changeHP(effect);
}

void PC::hurt(Human & h) {
    int effect = damage(&h);
    changeHP(effect);
}


void Shade::attack(Enemy *target){
    target->hurt(this);
    if (target->getHP() == 0) {
        changeGold(target->getGold());
    }
}

void Troll::attack(Enemy *target){
    target->hurt(this);
    if (target->getHP() == 0) {
        changeGold(target->getGold());
    }
}

void Vampire::attack(Enemy *target){
    target->hurt(this);
    if (target->getName() == 'W') {
        int min = -5;
        VchangeHP(min);
    } else if (target->getName() != 'W') {
        int add = 5;
        VchangeHP(add);
    }
    if (target->getHP() <= 0) {
        changeGold(target->getGold());
    }
}


void Drow::attack(Enemy *target){
    target->hurt(this);
    if (target->getHP() == 0) {
        changeGold(target->getGold());
    }
}


Shade::Shade(): PC{125,15,15,0} {}

Shade::~Shade(){}

Troll::Troll() :
PC(120, 25, 15,0){}

Troll::~Troll(){}

void Troll::regainHealth(){
    changeHP(5);
}

Vampire::Vampire() :
PC(50, 25, 25,0) {}

Vampire::~Vampire() {}

void Vampire::VchangeHP(int effect) {
    changeCurHP(effect);
}

Goblin::Goblin() :
PC(110, 15, 20,0) {}

Goblin::~Goblin() {}

void Goblin::steal(){
    int amount = 5;
    changeGold(amount);
}

void Goblin::attack(Enemy *target) {
    target->hurt(this);
    if (target->getHP() == 0) {
        changeGold(5);
    }
}

Drow::Drow():
PC(150, 25, 15,0) {}

Drow::~Drow() {}

void Drow::pickUpItem(Item &i, int effect){
    i.useItem(effect);
}


void Troll::hurt(Merchant &m) {
    int effect = damage(&m);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Troll::hurt(Human &h) {
    int effect = damage(&h);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Troll::hurt(Dragon &d) {
    int effect = damage(&d);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Troll::hurt(Elf &e) {
    int effect = damage(&e,2);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Troll::hurt(Halfling &l) {
    int effect = damage(&l);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Troll::hurt(Dwarf &w) {
    int effect = damage(&w);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Troll::hurt(Orcs &o) {
    int effect = damage(&o);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}

void Vampire::hurt(Merchant &m) {
    int effect = damage(&m);
    int r = random6(0, 1);
    if (r == 0) {
        VchangeHP(effect);
        changeDamageE(effect);
    }
}
void Vampire::hurt(Human &h) {
    int effect = damage(&h);
    int r = random6(0, 1);
    if (r == 0) {
        VchangeHP(effect);
        changeDamageE(effect);
    }
}
void Vampire::hurt(Dragon &d) {
    int effect = damage(&d);
    int r = random6(0, 1);
    if (r == 0) {
        VchangeHP(effect);
        changeDamageE(effect);
    }
}
void Vampire::hurt(Elf &e) {
    int effect = damage(&e,2);
    int r = random6(0, 1);
    if (r == 0) {
        VchangeHP(effect);
        changeDamageE(effect);
    }
}
void Vampire::hurt(Halfling &l) {
    int effect = damage(&l);
    int r = random6(0, 1);
    if (r == 0) {
        VchangeHP(effect);
        changeDamageE(effect);
    }
}
void Vampire::hurt(Dwarf &w) {
    int effect = damage(&w);
    int r = random6(0, 1);
    if (r == 0) {
        VchangeHP(effect);
        changeDamageE(effect);
    }
}
void Vampire::hurt(Orcs &o) {
    int effect = damage(&o);
    int r = random6(0, 1);
    if (r == 0) {
        VchangeHP(effect);
        changeDamageE(effect);
    }
}

void Goblin::hurt(Merchant &m) {
    int effect = damage(&m);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Goblin::hurt(Human &h) {
    int effect = damage(&h);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Goblin::hurt(Dragon &d) {
    int effect = damage(&d);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Goblin::hurt(Elf &e) {
    int effect = damage(&e,2);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Goblin::hurt(Halfling &l) {
    int effect = damage(&l);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Goblin::hurt(Dwarf &w) {
    int effect = damage(&w);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Goblin::hurt(Orcs &o) {
    int effect = damage(&o, 1.5);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}

void Drow::hurt(Merchant &m) {
    int effect = damage(&m);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Drow::hurt(Human &h) {
    int effect = damage(&h);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Drow::hurt(Dragon &d) {
    int effect = damage(&d);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}

void Drow::hurt(Elf &e) {
    int effect = damage(&e);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Drow::hurt(Halfling &l) {
    int effect = damage(&l);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Drow::hurt(Dwarf &w) {
    int effect = damage(&w);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Drow::hurt(Orcs &o) {
    int effect = damage(&o);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}


void Shade::hurt(Merchant &m) {
    int effect = damage(&m);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Shade::hurt(Human &h) {
    int effect = damage(&h);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Shade::hurt(Dragon &d) {
    int effect = damage(&d);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}

void Shade::hurt(Elf &e) {
    int effect = damage(&e);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Shade::hurt(Halfling &l) {
    int effect = damage(&l);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Shade::hurt(Dwarf &w) {
    int effect = damage(&w);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}
void Shade::hurt(Orcs &o) {
    int effect = damage(&o);
    int r = random6(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamageE(effect);
    }
}



