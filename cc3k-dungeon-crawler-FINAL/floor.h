#ifndef __FLOOR_H__
#define __FLOOR_H__
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include "cell.h"
#include "enemy.h"
#include "pc.h"
#include "chamber.h"
#include "treasure.h"
#include "potion.h"
#include "message.h"

class Floor {
    std::vector<std::vector<Cell *>> cellList;
    int level;
    std::vector<Enemy *> enemyList;
    PC *player;
    std::vector<Chamber *> roomList;
    std::vector<Item *> itemList;
    Message *message;
    bool isFrozen;
    bool hostile;
    
public:
    Floor(PC*, bool isFrozen=false, bool hostile = false);
    
    ~Floor();
    
    void prettyPrint();
    
    void clearFloor();
    
    void genEmptyFloor();
    
    void init(PC*);
    
    void sInit(PC*, std::vector<std::vector<std::vector<int>>>, int);
    
    int getLevel();
    
    bool gameOver();
    
    void createEnemy(int);
    
    void createPotion(int);
    
    void createTreasure(int);
    
    void createStair();
    
    bool movePlayer(std::string dir);
    
    void updateEnemy();
    
    void deleteEnemy(int, int);
    
    void simpleMoveCharacter(int, int, int, int, Character *c);
    
    // std::vector<Cell*> produceSurroundEmpty(int, int);
    
    std::vector<Spawn *> scanEmptyEnemy(int, int);
    
    PC* checkPC(int, int);
    
    void playerAttack(std::string);
    
    void playerUsePotion(std::string);
    
    void setFrozen();
    
    bool getFrozen();
    
    void setHostile(bool);
    
    bool getHostile();
    
    void printEnemyHP();
    
    void printMessage();
    
    int jumpCharacter(int, int, int, int, Character *c);
    
};

#endif
