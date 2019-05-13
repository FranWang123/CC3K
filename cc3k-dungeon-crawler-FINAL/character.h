#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include <string>
#include <iostream>


class Character {
    int initHP, initAtk, initDef, Gold, row, col, curHp, curAtk, curDef;
protected:
    char name;
public:
    void changePosition(int x, int y);
    Character(int initHp, int initAtk, int initDef, int Gold);
    virtual  ~Character();
    int damage(Character *other, float mag = 1);
    bool die();
    virtual void changeHP(int effect);
    virtual void changeAtk(int effect);
    virtual void changeDef(int effect);
    virtual int getHP();
    int getAtk();
    int getDef();
    int getGold();
    int getRow();
    int getCol();
    char getName();
    void initAtkDef();
    void initAll();
    void changeGold(int);
    int getinitHp();
    void changeCurHP(int);
};  

#endif
