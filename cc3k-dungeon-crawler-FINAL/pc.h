#ifndef _PC_H_
#define _PC_H_
#include <string>
#include <iostream>
#include "character.h"
// #include "item.h"
#include "enemy.h"

class Item;

class Enemy;
class Merchant;
class Human;
class Dragon;
class Elf;
class Halfling;
class Elf;
class Dwarf;
class Orcs;

class PC: public Character {
    int max;
    int damageE;
public:
    PC(int, int, int, int);
    virtual ~PC();
    void pickUpItem(Item &i);
    int getMax();
    virtual void attack(Enemy* target)=0;
    // void attack(Enemy *target);
    // void attack(Elf *target);
    // void attack(Dwarf  *target);
    // void attack(Halfling  *target);
    // void attack(Orcs  *target);
    // void attack(Merchant  *target);
    // void attack(Dragon  *target);
    // void attack(Human  *target);
    virtual void hurt(Merchant &m)=0;
    virtual void hurt(Human &h)=0;
    virtual void hurt(Dragon &d)=0;
    virtual void hurt(Elf &e)=0;
    virtual void hurt(Halfling &l)=0;
    virtual void hurt(Dwarf &w)=0;
    virtual void hurt(Orcs &o)=0;
    void changeDamageE(int amount);
    int getDamageE();
};

class Shade: public PC{
public:
    Shade();
    ~Shade() override;
    void hurt(Merchant &m);
    void hurt(Human &h);
    void hurt(Dragon &d);
    void hurt(Elf &e);
    void hurt(Halfling &l);
    void hurt(Dwarf &w);
    void hurt(Orcs &o);
    void attack(Enemy *target) override;
};

class Troll: public PC{
    int stealHP;
public:
    Troll();
    ~Troll() override;
    void regainHealth();
    void hurt(Merchant &m);
    void hurt(Human &h);
    void hurt(Dragon &d);
    void hurt(Elf &e);
    void hurt(Halfling &l);
    void hurt(Dwarf &w);
    void hurt(Orcs &o);
    void attack(Enemy *target) override;
};

class Vampire: public PC{
public:
    ~Vampire() override;
    Vampire();
    void VchangeHP(int effet);
    void attack(Enemy *target) override;
    void hurt(Merchant &m);
    void hurt(Human &h);
    void hurt(Dragon &d);
    void hurt(Elf &e);
    void hurt(Halfling &l);
    void hurt(Dwarf &w);
    void hurt(Orcs &o);
    
};

class Goblin: public PC{
    int stealGold;
public:
    Goblin();
    ~Goblin() override;
    void steal();
    void attack(Enemy *target) override;
    void hurt(Merchant &m);
    void hurt(Human &h);
    void hurt(Dragon &d);
    void hurt(Elf &e);
    void hurt(Halfling &l);
    void hurt(Dwarf &w);
    void hurt(Orcs &o);
    
};

class Drow: public PC{
    int potionMagnify;
public:
    Drow();
    ~Drow() override;
    void pickUpItem(Item &i, int effect);
    void hurt(Merchant &m);
    void hurt(Human &h);
    void hurt(Dragon &d);
    void hurt(Elf &e);
    void hurt(Halfling &l);
    void hurt(Dwarf &w);
    void hurt(Orcs &o);
    void attack(Enemy *target) override;
};

#endif
