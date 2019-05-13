
#ifndef enemy_hpp
#define enemy_hpp

#include "pc.h"
#include "character.h"
#include "treasure.h"
#include <vector>

class Troll;
class Vampire;
class Goblin;
class Drow;
class Elf;
class Shade;

class Enemy: public Character {
    PC * Target;
    bool moved;
    int damagePC;
public:
    Enemy(int initHP, int intAtk, int initDef, int Gold,
          PC * target, bool moved = false, int damagePC = 0);
    Enemy(PC *target);
    virtual ~Enemy();
    
    virtual void attack(PC *target) = 0;
    virtual void hurt(Troll *p)=0;
    virtual void hurt(Vampire *p)=0;
    virtual void hurt(Goblin *p)=0;
    virtual void hurt(Drow *p)=0;
    virtual void hurt(Shade *p)=0;
    
    void changeMoved();
    bool getMoved();
    
    int getDamagePC();
    void changeDamagePC(int amount);
};

class NormalEnemy: public Enemy {
    virtual void attack (PC *target) = 0;
public:
    NormalEnemy(int initHP, int intAtk, int initDef, int Gold,
                PC * target, bool moved = false, int damagePC = 0);
    virtual ~NormalEnemy();
    
    virtual void hurt(Troll *p);
    virtual void hurt(Vampire *p);
    virtual void hurt(Goblin *p);
    virtual void hurt(Drow *p);
    virtual void hurt(Shade *p);
};

class Elf: public NormalEnemy {
public:
    void attack(PC *target) override;
    Elf(PC *target);
    ~Elf() override;
    
};

class Dwarf: public NormalEnemy {
public:
    void attack(PC *target) override;
    Dwarf(PC *target);
    ~Dwarf() override;
};

class Halfling: public NormalEnemy {
public:
    void attack(PC *target) override;
    Halfling(PC *target);
    ~Halfling() override;
    void hurt(Troll *p) override;
    void hurt(Drow *p) override;
    void hurt(Vampire *p) override;
    void hurt(Shade *p) override;
    void hurt(Goblin *p) override;
    
};

class Orcs: public NormalEnemy {
public:
    void attack(PC *target) override;
    Orcs(PC *targte);
    ~Orcs() override;
};

class Merchant: public Enemy {
    std::vector<Item *> store;
public:
    void attack(PC *target) override;
    Merchant(PC *target);
    ~Merchant() override;
    void hurt(Troll *p) override;
    void hurt(Drow *p) override;
    void hurt(Vampire *p) override;
    void hurt(Shade *p) override;
    void hurt(Goblin *p) override;
};

class Dragon: public Enemy {
    Treasure * hoard;
public:
    void attack (PC *targte) override;
    Treasure * getHoard();
    void putHoard(Treasure *);
    Dragon(PC * target, Treasure * t);
    ~Dragon() override;
    void hurt(Troll *p) override;
    void hurt(Drow *p) override;
    void hurt(Vampire *p) override;
    void hurt(Shade *p) override;
    void hurt(Goblin *p) override;
};

class Human: public Enemy {
public:
    void attack (PC *target) override;
    Human(PC *target);
    ~Human() override;
    void hurt(Troll *p) override;
    void hurt(Drow *p) override;
    void hurt(Vampire *p) override;
    void hurt(Shade *p) override;
    void hurt(Goblin *p) override;
};

#endif /* enemy_hpp */
