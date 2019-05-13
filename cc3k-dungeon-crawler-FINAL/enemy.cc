#include "enemy.h"
#include "pc.h"
using namespace std;


Enemy::Enemy(int initHP, int initAtk, int initDef, int Gold, PC * target, bool moved, int damagePC)
: Character{initHP, initAtk, initDef, Gold}, Target(target), moved{moved},damagePC{damagePC} {}


Enemy::~Enemy() {
    Target = nullptr;
}

void Enemy::changeMoved() {
    moved = !moved;
}

bool Enemy::getMoved() {
    return moved;
}


void Enemy::changeDamagePC(int amount) {
    damagePC = amount;
}

int Enemy::getDamagePC() {
    int result = damagePC;
    damagePC = 0;
    return result;
}


int random2(int x, int y){
    int ran;
    ran = x + (rand() % (y - x + 1));
    return ran;
}


int random_gold(){
    int ran;
    ran = 0 + (rand() % (1 - 0 + 1));
    if (ran == 0) return 1;
    return 2;
}

NormalEnemy::NormalEnemy(int initHP, int initAtk, int initDef,
                         int Gold, PC * target, bool moved, int damagePC):
Enemy{initHP, initAtk, initDef, Gold, target, moved, damagePC}{}

NormalEnemy::~NormalEnemy() {}


//constructors
Human::Human(PC * target):
Enemy{140, 20, 20, 0, target}{
    name = 'H';
}

Dwarf::Dwarf(PC * target):
NormalEnemy{100, 20, 30, random_gold(), target}{
    name = 'W';
}

Elf::Elf(PC * target):
NormalEnemy{140, 30, 10, random_gold(), target}{
    name = 'E';
}

Orcs::Orcs(PC * target):
NormalEnemy{180, 30, 25, random_gold(), target}{
    name = 'O';
}

Merchant::Merchant(PC * target):
Enemy{30, 70, 5, 0, target}{
    name = 'M';
}

Dragon::Dragon(PC * target, Treasure *t):
Enemy{150, 20, 20, 0, target}{
    hoard = t;
    name = 'D';
}

Halfling::Halfling(PC * target):
NormalEnemy{100, 15, 20, random_gold(), target} {
    name = 'L';
}


Dwarf::~Dwarf(){}

Elf::~Elf(){}

Orcs::~Orcs(){}

Merchant::~Merchant(){}

Dragon::~Dragon(){}

Halfling::~Halfling(){}

Human::~Human(){}


void NormalEnemy::hurt(Troll *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
}

void NormalEnemy::hurt(Vampire *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
}

void NormalEnemy::hurt(Goblin *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
}

void NormalEnemy::hurt(Drow *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
}

void NormalEnemy::hurt(Shade *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
    
}


void Dragon::hurt(Troll *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
}

void Dragon::hurt(Vampire *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
    
}

void Dragon::hurt(Goblin *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
}

void Dragon::hurt(Drow *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
}

void Dragon::hurt(Shade *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
    
}


void Merchant::hurt(Troll *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
}

void Merchant::hurt(Vampire *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
}

void Merchant::hurt(Goblin *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
}

void Merchant::hurt(Drow *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
}

void Merchant::hurt(Shade *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
    
}

void Human::hurt(Troll *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
}

void Human::hurt(Vampire *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
}

void Human::hurt(Goblin *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
}

void Human::hurt(Drow *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
}

void Human::hurt(Shade *p) {
    int effect = damage(p);
    changeHP(effect);
    changeDamagePC(effect);
    
}


void Halfling::hurt(Troll *p) {
    int effect = damage(p);
    int r = random2(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamagePC(effect);
    }
}

void Halfling::hurt(Vampire *p) {
    int effect = damage(p);
    int r = random2(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamagePC(effect);
    }
}

void Halfling::hurt(Goblin *p) {
    cout << "TEN" << endl;
    int effect = damage(p);
    int r = random2(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamagePC(effect);
    }
}

void Halfling::hurt(Drow *p) {
    int effect = damage(p);
    int r = random2(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamagePC(effect);
    }
}


void Halfling::hurt(Shade *p) {
    int effect = damage(p);
    int r = random2(0, 1);
    if (r == 0) {
        changeHP(effect);
        changeDamagePC(effect);
    }
}

void Elf::attack(PC * player) {
    player->hurt(*this);
}


void Dwarf::attack(PC * player) {
    player->hurt(*this);
}

void Halfling::attack(PC * player) {
    player->hurt(*this);
}

void Orcs::attack(PC * player) {
    player->hurt(*this);
}

void Merchant::attack(PC * player) {
    player->hurt(*this);
}

void Dragon::attack(PC * player) {
    player->hurt(*this);
}

void Human::attack(PC * player) {
    player->hurt(*this);
}


Treasure * Dragon::getHoard(){
    return hoard;
}


void Dragon::putHoard(Treasure *t){
    hoard = t;
}
