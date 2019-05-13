#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <typeinfo>
#include "floor.h"
#include "wall.h"
#include "passage.h"
#include "door.h"
#include "stair.h"
#include "spawn.h"
#include "item.h"
#include "message.h"


using namespace std;

int random(int x, int y){
    int ran;
    ran = x + (rand() % (y - x + 1));
    return ran;
}

Floor::Floor(PC *player, bool isFrozen, bool hostile)
:player{player},isFrozen{isFrozen}, hostile{hostile}, level{1}{
    message = new Message;
}


Floor::~Floor() {
    player = nullptr;
    delete message;
}

vector<vector<int>> genEightCord(int i, int j) {
    vector<vector<int>> v;
    vector<int> v1;
    v1.emplace_back(i+1);
    v1.emplace_back(j);
    v.emplace_back(v1);
    vector<int> v2;
    v2.emplace_back(i-1);
    v2.emplace_back(j);
    v.emplace_back(v2);
    vector<int> v3;
    v3.emplace_back(i);
    v3.emplace_back(j+1);
    v.emplace_back(v3);
    vector<int> v4;
    v4.emplace_back(i);
    v4.emplace_back(j-1);
    v.emplace_back(v4);
    vector<int> v5;
    v5.emplace_back(i+1);
    v5.emplace_back(j+1);
    v.emplace_back(v5);
    vector<int> v6;
    v6.emplace_back(i-1);
    v6.emplace_back(j+1);
    v.emplace_back(v6);
    vector<int> v7;
    v7.emplace_back(i+1);
    v7.emplace_back(j-1);
    v.emplace_back(v7);
    vector<int> v8;
    v8.emplace_back(i-1);
    v8.emplace_back(j-1);
    v.emplace_back(v8);
    return v;
}

void Floor::setFrozen(){
    if(isFrozen){
        isFrozen = false;
    } else {
        isFrozen = true;
    }
}

bool Floor::getFrozen(){
    return isFrozen;
}


void Floor::setHostile(bool f){
    hostile = f;
}

bool Floor::getHostile(){
    return hostile;
}

void Floor::printEnemyHP(){
    for (auto e: enemyList) {
        cout << e->getHP() << " ";
    }
    cout << endl;
}

void Floor::prettyPrint(){
    for (int i = 0; i < cellList.size() ; ++i){
        for (int j = 0; j < cellList[i].size(); ++j){
            cellList[i][j]->prettyPrint();
        }
        cout << endl;
    }
}

void Floor::printMessage() {
    
    message->getMessage();
    message->clearMessage();
}

void Floor::clearFloor(){
    
    for (auto i: enemyList){
        delete i;
    }
    
    
    for (auto cellVec : cellList){
        for (auto c: cellVec){
            delete c;
        }
    }
    
    
    for(auto j: roomList){
        delete j;
    }
    
    for(auto t: itemList){
        delete t;
    }
}

void Floor::genEmptyFloor(){
    ifstream fs;
    fs.open("cc3k.txt");
    
    string s;
    int i = 0;
    
    while(getline(fs, s))
    {
        
        vector<Cell*> newVec;
        char c;
        
        for(int j = 0; j < s.size(); ++j)
        {
            c = s[j];
            Cell *newC= nullptr;
            
            if (c == ' ' || c == '-' || c == '|')
            {
                newC = new Wall{c, i, j};
            }
            else if (c == '#')
            {
                newC = new Passage{c, i, j};
            } else if (c == '.')
            {
                newC = new Spawn{c, i, j};
            } else
            {
                newC = new Door{c, i, j};
            }
            newVec.emplace_back(newC);
        }
        
        cellList.emplace_back(newVec);
        ++i;
    }
    fs.close();
    
}

void Floor::sInit(PC* p, vector<vector<vector<int>>> readFloorVec, int level){
    //get the current floor vec of vec of char
    vector<vector<int>> curFloor = readFloorVec[level];
    for (int i = 0; i < 25; ++i) {
        
        vector<Cell*> newVec;
        int c;
        
        for(int j = 0; j < 79; ++j)
        {
            
            c = curFloor[i][j];
            Cell *newC= nullptr;
            Spawn * newS = nullptr;
            Enemy *newE = nullptr;
            Potion *newP = nullptr;
            Treasure *newT = nullptr;
            
            
            
            if (c == 18)
            {
                newC = new Wall{' ', i, j};
                newVec.emplace_back(newC);
            }
            else if (c == 19)
            {
                newC = new Wall{'-', i, j};
                newVec.emplace_back(newC);
            }
            else if (c == 20)
            {
                newC = new Wall{'|', i, j};
                newVec.emplace_back(newC);
            }
            else if (c == 21)
            {
                newC = new Passage{'#', i, j};
                newVec.emplace_back(newC);
            }
            else if (c == 22)
            {
                newC = new Spawn{'.', i, j};
                newVec.emplace_back(newC);
            }
            else if (c == 23)
            {
                newC = new Door{'+', i, j};
                newVec.emplace_back(newC);
            }
            else if (c == 24)
            {
                newC = new Stair{'\\', i, j};
                newVec.emplace_back(newC);
            }
            else if (c == 0)
            {
                newS = new Spawn{'.', i, j};
                newVec.emplace_back(newS);
                newP = new RH{player};
                newP->changePosition(i, j);
                newS->putItem(newP);
                itemList.emplace_back(newP);
            } else if (c == 1)
            {
                newS = new Spawn{'.', i, j};
                newVec.emplace_back(newS);
                newP = new BA{player};
                newP->changePosition(i, j);
                newS->putItem(newP);
                itemList.emplace_back(newP);
            } else if (c == 2)
            {
                newS = new Spawn{'.', i, j};
                newVec.emplace_back(newS);
                newP = new BD{player};
                newP->changePosition(i, j);
                newS->putItem(newP);
                itemList.emplace_back(newP);
            } else if (c == 3)
            {
                newS = new Spawn{'.', i, j};
                newVec.emplace_back(newS);
                newP = new PH{player};
                newP->changePosition(i, j);
                newS->putItem(newP);
                itemList.emplace_back(newP);
            } else if (c == 4)
            {
                newS = new Spawn{'.', i, j};
                newVec.emplace_back(newS);
                newP = new WA{player};
                newP->changePosition(i, j);
                newS->putItem(newP);
                itemList.emplace_back(newP);
            } else if (c == 5)
            {
                newS = new Spawn{'.', i, j};
                newVec.emplace_back(newS);
                newP = new WD{player};
                newP->changePosition(i, j);
                newS->putItem(newP);
                itemList.emplace_back(newP);
            }
            // cell has treasure
            else if (c == 6)
            {
                newS = new Spawn{'.', i, j};
                newVec.emplace_back(newS);
                newT = new Normal{player};
                newT->changePosition(i, j);
                newS->putItem(newT);
                itemList.emplace_back(newT);
            }
            else if (c == 7)
            {
                newS = new Spawn{'.', i, j};
                newVec.emplace_back(newS);
                newT = new Small{player};
                newT->changePosition(i, j);
                newS->putItem(newT);
                itemList.emplace_back(newT);
            }
            else if (c == 8)
            {
                newS = new Spawn{'.', i, j};
                newVec.emplace_back(newS);
                newT = new MH{player};
                newT->changePosition(i, j);
                newS->putItem(newT);
                itemList.emplace_back(newT);
            }
            else if (c == 9)
            {
                newS = new Spawn{'.', i, j};
                newVec.emplace_back(newS);
                newT = new DH{player};
                newT->changePosition(i, j);
                newS->putItem(newT);
                itemList.emplace_back(newT);
            }
            
            else if (c == 10)
            {
                newS = new Spawn{'.', i, j};
                newVec.emplace_back(newS);
                newE = new Halfling{player};
                newE->changePosition(i, j);
                newS->putCharacter(newE);
                enemyList.emplace_back(newE);
            }
            else if (c == 11)
            {
                newS = new Spawn{'.', i, j};
                newVec.emplace_back(newS);
                newE = new Dwarf{player};
                newE->changePosition(i, j);
                enemyList.emplace_back(newE);
                newS->putCharacter(newE);
            }
            else if (c == 12)
            {
                newS = new Spawn{'.', i, j};
                newVec.emplace_back(newS);
                newE = new Elf{player};
                newE->changePosition(i, j);
                newS->putCharacter(newE);
                enemyList.emplace_back(newE);
            }
            else if (c == 13)
            {
                newS = new Spawn{'.', i, j};
                newVec.emplace_back(newS);
                newE = new Human{player};
                newE->changePosition(i, j);
                enemyList.emplace_back(newE);
                newS->putCharacter(newE);
            }
            else if (c == 14)
            {
                newS = new Spawn{'.', i, j};
                newVec.emplace_back(newS);
                newE = new Orcs{player};
                newE->changePosition(i, j);
                newS->putCharacter(newE);
                enemyList.emplace_back(newE);
            }
            else if (c == 15)
            {
                newS = new Spawn{'.', i, j};
                newVec.emplace_back(newS);
                newE = new Merchant{player};
                newE->changePosition(i, j);
                newS->putCharacter(newE);
                enemyList.emplace_back(newE);
            }
            else if (c == 16)
            {
                newS = new Spawn{'.', i, j};
                newVec.emplace_back(newS);
                newE = new Dragon{player, nullptr};
                newE->changePosition(i, j);
                newS->putCharacter(newE);
                enemyList.emplace_back(newE);
            }
            // cell has player
            else if (c == 17)
            {
                newS = new Spawn{'.', i, j};
                newS->putCharacter(player);
                player->changePosition(i,j);
                newVec.emplace_back(newS);
            }
            else {
            }
            
        }
        
        
        cellList.emplace_back(newVec);
    }
    
    for (auto i : itemList) {
        DH *dHoard = dynamic_cast<DH *>(i);
        if (dHoard) {
            int row = dHoard->getRow();
            int col = dHoard->getCol();
            vector<vector<int>> surround= genEightCord(row, col);
            for(int j = 0; j < 8; j++) {
                int row = surround[j][0];
                int col = surround[j][1];
                Cell * curCell = cellList[row][col];
                Spawn * s = dynamic_cast<Spawn *>(curCell);
                if (s) {
                    if (s->hasCharacter()) {
                       	Character *cur = s->getCharacter();
                       	Enemy *e = dynamic_cast<Enemy *>(cur);
                        Dragon *d = dynamic_cast<Dragon *>(e);
                        if (d){
                            Treasure *t = dynamic_cast<Treasure *>(i);
                            d->putHoard(t);
                        }
                    }
                }
            }
        }
    }
    prettyPrint();
    
    
    
}

void Floor::init(PC *p){
    
    //Chamber 1
    Chamber *chamberOne = new Chamber{1};
    for (int i = 3; i <= 6; ++i){
        for (int j = 3; j <= 28; ++j){
            Spawn *cur=dynamic_cast<Spawn *>(cellList[i][j]);
            chamberOne->addSpawn(cur);
        }
    }
    roomList.emplace_back(chamberOne);
    
    
    //Chamber 2
    Chamber *chamberTwo = new Chamber{2};
    for (int i = 3; i <= 6; ++i){
        for (int j = 39; j <= 72; ++j){
            if (cellList[i][j]->getType() == '.'){
                Spawn *cur=dynamic_cast<Spawn *>(cellList[i][j]);
                chamberTwo->addSpawn(cur);
            }
        }
    }
    for (int i = 7; i <= 12; ++i){
        for (int j = 61; j <= 75; ++j){
            if (cellList[i][j]->getType() == '.'){
                Spawn *cur=dynamic_cast<Spawn *>(cellList[i][j]);
                chamberTwo->addSpawn(cur);
            }
        }
    }
    roomList.emplace_back(chamberTwo);
    
    
    //Chamber 3
    Chamber *chamberThree = new Chamber{3};
    for (int i = 10; i <= 12; ++i){
        for (int j = 38; j <= 49; ++j){
            Spawn *cur=dynamic_cast<Spawn *>(cellList[i][j]);
            chamberThree->addSpawn(cur);
        }
    }
    roomList.emplace_back(chamberThree);
    
    
    //Chamber 4
    Chamber *chamberFour = new Chamber{4};
    for (int i = 15; i <= 21; ++i){
        for (int j = 4; j <= 24; ++j){
            Spawn *cur=dynamic_cast<Spawn *>(cellList[i][j]);
            chamberFour->addSpawn(cur);
        }
    }
    roomList.emplace_back(chamberFour);
    
    
    //Chamber 5
    Chamber *chamberFive = new Chamber{5};
    for (int i = 19; i <= 21; ++i){
        for (int j = 37; j <= 75; ++j){
            Spawn *cur=dynamic_cast<Spawn *>(cellList[i][j]);
            chamberFive->addSpawn(cur);
        }
    }
    for (int i = 16; i <= 18; ++i){
        for (int j = 65; j <= 75; ++j){
            Spawn *cur=dynamic_cast<Spawn *>(cellList[i][j]);
            chamberFive->addSpawn(cur);
        }
    }
    roomList.emplace_back(chamberFive);

    
    int rP = random(0,4);
    roomList[rP]->assignCharacter(p);
    
    createStair();
    createPotion(10);
    createTreasure(10);
    createEnemy(20);
    prettyPrint();
    
}


int Floor::getLevel(){
    return level;
}

bool Floor::gameOver(){
    if (player->getHP() <= 0){
        return true;
    }
    return false;
}

void Floor::createEnemy(int num){
    while (num > 0){
        
        Enemy *newE = nullptr;
        int r = random(1, 18);
        int r2 = rand()%5;
        
        while(roomList[r2]->getEmptyAmount() < 1){
            r2 = rand()%5;
        }
        
        
        if (r >= 1 && r <= 4) {
            newE = new Human{player};
        } else if (r >= 5 && r <= 7) {
            newE = new Dwarf{player};
        } else if (r >= 8 && r <= 12){
            newE = new Halfling{player};
        } else if (r >= 13 && r <= 14) {
            newE = new Elf{player};
        } else if (r >= 15 && r <= 16) {
            newE = new Orcs{player};
        } else {
            newE = new Merchant{player};
        }
        
        enemyList.emplace_back(newE);
        roomList[r2]->assignCharacter(newE);
        --num;
    }
}


void Floor::createPotion(int num){
    while(num > 0) {
        Item *newP = nullptr;
        int r = random(1, 6);
        int r2 = random(0, 4);
        
        while(roomList[r2]->getEmptyAmount() < 1){
            r2 = random(0, 4);
        }
        
        if (r == 1) {
            newP = new RH{player};
        } else if (r == 2) {
            newP = new BA{player};
        } else if (r == 3){
            newP = new BD{player};
        } else if (r == 4) {
            newP = new PH{player};
        } else if (r == 5) {
            newP = new WA{player};
        } else {
            newP = new WD{player};
        }
        itemList.emplace_back(newP);
        roomList[r2]->assignItem(newP);
        --num;
    }
}


void Floor::createTreasure(int num){
    while(num > 0){
        int r = random(1, 8);
        int chamberR = random(0,4);
        
        while(roomList[chamberR]->getEmptyAmount() < 1){
            chamberR = random(0, 4);
        }
        
        
        // Dragon Hoard
        if (r == 1) {
            
            while(roomList[chamberR]->getEmptyAmount() < 2){
                chamberR = random(0, 4);
            }
            Treasure *newT = new DH{player};
            itemList.emplace_back(newT);
            Dragon *newD = new Dragon{player, newT};
            enemyList.emplace_back(newD);
            roomList[chamberR]->assignTreasure(newT, newD);
        }
        
        // Small Hoard
        else if (r >=2 && r <= 4) {
            Item *newT = new Small{player};
            itemList.emplace_back(newT);
            roomList[chamberR]->assignItem(newT);
        }
        
        // Normal Hoard
        else {
            Item *newT = new Normal{player};
            itemList.emplace_back(newT);
            roomList[chamberR]->assignItem(newT);
        }
        --num;
    }
}

void Floor::createStair(){
    // find the number of chamber room that has the player
    int fullRoom;
    for (int i = 0; i < 5; i++) {
        if(roomList[i]->hasPlayer()){
            fullRoom = i;
        }
    }
    
    // randomly generate a chamber room number that does not have the player inside
    int r1 = random(0,4);
    while(r1 == fullRoom){
        r1 = random(0,4);
    }
    int stairRoom = r1;
    
    // randomly generate index of vector of empty spawns to assign the stair
    int num = roomList[stairRoom]->getEmptyAmount();
    int r2 = random(0, num-1);
    
    // find the spawn cell that we are going to replace
    Spawn *tar = (roomList[stairRoom]->getEmptySpawn())[r2];
    // get the row and col indices of the spawn cell we are going to replace
    int row = tar->getRow();
    int col = tar->getCol();
    
    // create the stair cell
    Stair *newStair = new Stair{'/', row, col};
    // assign
    cellList[row][col] = newStair;
    // erase replaced cell from empty spawn list
    roomList[stairRoom]->eraseEmptySpawn(r2);
    
    
    delete tar;
}



bool Floor::movePlayer(string dir){
    Troll *t = dynamic_cast<Troll*>(player);
    string direction;
    if(dir == "no") direction = "North";
    if(dir == "ea") direction = "East";
    if(dir == "we") direction = "West";
    if(dir == "so") direction = "South";
    if(dir == "ne") direction = "Northeast";
    if(dir == "se") direction = "Southeast";
    if(dir == "nw") direction = "Northwest";
    if(dir == "sw") direction = "Southwest";
    // get current position of player
    int curRow = player->getRow();
    int curCol = player->getCol();
    
    // compute new position x and y
    int newRow = curRow;
    int newCol = curCol;
    if (dir == "no") {
        --newRow;
    }
    if (dir == "so") {
        ++newRow;
    }
    if (dir == "ea")  {
        ++newCol;
    }
    if (dir == "we") {
        --newCol;
    }
    if (dir == "ne") {
        --newRow;
        ++newCol;
    }
    if (dir == "nw") {
        --newCol;
        --newRow;
    }
    if (dir == "se") {
        ++newCol;
        ++newRow;
    }
    if (dir == "sw") {
        --newCol;
        ++newRow;
    }
    
    // find the cell player wants to move to
    Cell* cur = cellList[newRow][newCol];
    char c = cur->getType();
    
    
    // if the next cell is wall, spawn, passage, door, or stairs
    
    //WALL
    if (c == ' ' || c == '-' || c == '|') {
        message->addMessage("PC cannot move.");
        if(t){
            t->changeHP(5);
        }
        return true;
    }
    //SPAWN
    else if (c == '.')
    {
        message->addMessage("PC moves to " + direction + ".");
        
	       
        Spawn *curCell =dynamic_cast<Spawn *>(cur);
        // Spawn has an enemy
        if (curCell->hasCharacter())
        {
        }
        
        // Spawn has an item
        else if (curCell->hasItem()) {
            if (curCell->getItem()->getType() == 'G') {
                Item *curI = curCell->getItem();
                Treasure *t = dynamic_cast<Treasure*>(curI);
                if(!t->isProtect()){
                    curI->useItem();
                    simpleMoveCharacter(curRow, curCol, newRow, newCol, player);
                    curCell->putItem(nullptr);
                } else {
                    int cond = jumpCharacter(curRow, curCol, newRow, newCol, player);
                    if(cond == 0){
                        return true;
                    } else if (cond == 1){
                        return false;
                    } else if (cond == 2){
                        cout << "This jump will send the player out of the map, please don't leave the dungeon. We have cake!" << endl;

                    }
                }
            }
        }
        // Spawn is empty
        else {
            simpleMoveCharacter(curRow, curCol, newRow, newCol, player);
        }
        if(t){
            t->changeHP(5);
        }
        return true;
    }
    //PASSAGE
    else if (c == '#'){
        simpleMoveCharacter(curRow, curCol, newRow, newCol, player);
        message->addMessage("PC moves to " + direction + ".");
        if(t){
            t->changeHP(5);
        }
        return true;
    }
    //DOOR
    else if (c == '+'){
        simpleMoveCharacter(curRow, curCol, newRow, newCol, player);
        message->addMessage("PC moves to " + direction + ".");
        if(t){
            t->changeHP(5);
        }
        return true;
    }
    //STAIRS
    else {
        return false;
    }
}


void Floor::updateEnemy(){
    if(isFrozen){
        return;
    }
    
    for(int i = 0; i < 25; ++i){
        for (int j = 0; j < 79; ++j){
            if (cellList[i][j]->getType() != '.'){
                continue;
            }
            
            
            Spawn *curSpawn = dynamic_cast<Spawn *>(cellList[i][j]);
            
            //check if cell has character
            if (!curSpawn->hasCharacter()){
                continue;
            }
            
            //cell has character
            Character *c = curSpawn->getCharacter();
            
            //cell has player
            if (c->getName() == '@') {
                continue;
            }
            
            
            //cell has enemy,
            else {
                
                Enemy *curE = dynamic_cast<Enemy*>(c);
                
                //enemy has not moved this round
                if (!curE->getMoved())
                {
                    if (curE->getName() == 'D')
                    {
                        Dragon *d = dynamic_cast<Dragon *>(curE);
                        
                        PC *tarD = checkPC(d->getRow(), d->getCol());
                        
                        Treasure *t = d->getHoard();
                        
                        int tRow = t->getRow();
                        int tCol = t->getCol();
                        if (!tarD) {
                            tarD = checkPC(tRow, tCol);
                        }
                        
                        if (tarD) {
                            d->attack(tarD);
                            int pchurt = player->getDamageE();
                            string act;
                            act += d->getName();
                            message->addMessage
                            (act + " deals " +
                             to_string(0 -pchurt) + " damages to PC.");
                        }
                    }
                    
                    // cell has merchant
                    else if (curE->getName() == 'M')
                    {
                        Merchant *m = dynamic_cast<Merchant *>(c);
                        PC *tar = checkPC(i, j);
                        if (hostile) {
                            if (tar != nullptr){
                                m->attack(tar);
                                int pchurt =player->getDamageE();
                                string act;
                                act += m->getName();
                                message->addMessage
                                (act + " deals " +
                                 to_string(0 -pchurt) + " damages to PC.");
                            } else {
                                
                                vector<Spawn *> surround = scanEmptyEnemy(i, j);
                                
                                if (surround.size() != 0) {
                                    int size = surround.size();
                                    int r = random(0, size - 1);
                                    int newR = surround[r]->getRow();
                                    int newC = surround[r]->getCol();
                                    simpleMoveCharacter(i, j, newR, newC, c);
                                } else {
                                    continue;
                                }
                                
                                
                            }
                        } else {
                            vector<Spawn *> surround = scanEmptyEnemy(i, j);
                            if (surround.size() != 0) {
                                int size = surround.size();
                                int r = random(0, size - 1);
                                int newR = surround[r]->getRow();
                                int newC = surround[r]->getCol();
                                simpleMoveCharacter(i, j, newR, newC, c);
                            } else {
                                continue;
                            }
                        }
                    }
                    
                    
                    // cell has normal enemy
                    else
                    {
                        Enemy *curE = dynamic_cast<Enemy *>(c);
                        PC *tar = checkPC(i, j);
                        if (tar != nullptr)
                        {
                            curE->attack(tar);
                            int pchurt = player->getDamageE();
                            string act;
                            act += curE->getName();
                            message->addMessage(act + " deals " + to_string(0 -pchurt) + " damages to PC.");
                            
                            continue;
                        }
                        else
                        {
                            vector<Spawn *> surround = scanEmptyEnemy(i, j);
                            if (surround.size() != 0) {
                                int size = surround.size();
                                int r = random(0, size - 1);
                                int newR = surround[r]->getRow();
                                int newC = surround[r]->getCol();
                                simpleMoveCharacter(i, j, newR, newC, c);
                            }
                        }
                    }
                    curE->changeMoved();
                }
                
                //enemy has moved already
                else
                {
                    continue;
                }
            }
        }
    }
    
    for(int i = 0; i < 25; ++i){
        for(int j = 0; j < 79; ++j){
            
            if (cellList[i][j]->getType() == '.'){
                
                Spawn *s = dynamic_cast<Spawn*>(cellList[i][j]);
                
                Character *c = s->getCharacter();
                if (c){
                    if (!(c->getName()== '@')){
                        Enemy *e = dynamic_cast<Enemy *>(c);
                        if (e){
                            if (e->getMoved()){
                                e->changeMoved();
                            }
                        }
                    }
                }
            }
        }
    }
}

void Floor::deleteEnemy(int row, int col){
    int i = 0;
    for (auto e: enemyList) {
        if (e->getRow() == row && e->getCol() == col) {
            break;
        }
        ++i;
    }
    delete enemyList[i];
    enemyList.erase(enemyList.begin() + i);
}


void Floor::simpleMoveCharacter(int oldRow, int oldCol, int row, int col, Character *c){
    NormalCell *oldCell = dynamic_cast<NormalCell*>(cellList[oldRow][oldCol]);
    oldCell->putCharacter(nullptr);
    NormalCell *newCell = dynamic_cast<NormalCell*>(cellList[row][col]);
    c->changePosition(row, col);
    newCell->putCharacter(c);

    vector<vector<int>> sets;
    sets = genEightCord(row, col);

    if(dynamic_cast<PC*>(c)){
        for(int i = 0; i < 8; ++i){
            int newR = sets[i][0];
            int newC = sets[i][1];
            Cell *ce = cellList[newR][newC];
            Spawn *s = nullptr;
            if(ce->getType() == '.' ){
                s = dynamic_cast<Spawn*>(cellList[newR][newC]);
                if(s->getItem() != nullptr &&
                    s->getItem()->getType() == 'P') {
                    message->addMessage("PC sees an unknown potion.");
                break;
               }
           }
       }
    }
    
}


int Floor::jumpCharacter(int oldRow, int oldCol, int row, int col, Character *c){
    int deltaR = row - oldRow;
    int deltaC = col - oldCol;
    int newR = row + deltaR;
    int newC = col + deltaC;
    if (newR > 24 || newR < 0) {
        return 2;
    } else if (newC > 79 || newC < 0) {
        return 2;
    } else {
        Cell *curCell = cellList[newR][newC];
        Spawn *s = dynamic_cast<Spawn*>(curCell);
        Passage *pCell = dynamic_cast<Passage*>(curCell);
        Door *dCell = dynamic_cast<Door*>(curCell);
        Stair *sCell = dynamic_cast<Stair*>(curCell);
        if (s) {
            if (!s->hasCharacter() && !s->hasItem()){
                simpleMoveCharacter(oldRow, oldCol, newR, newC, c);
            }
        } else if (pCell || dCell) {
            simpleMoveCharacter(oldRow, oldCol, newR, newC, c);            
        } else if (sCell){
            return 1;
        }
    }
    return 0;
}



vector<Spawn *> Floor::scanEmptyEnemy(int i, int j){
    vector<vector<int>> newCords = genEightCord(i,j);
    vector<Spawn *> newVec;
    for (int i = 0; i < 8; ++i) {
        int newR = newCords[i][0];
        int newC = newCords[i][1];
        Cell *curCell = cellList[newR][newC];
        if(curCell->getType() == '.'){
            Spawn *curSpawn = dynamic_cast<Spawn *>(curCell);
            if(!curSpawn->hasItem() && !curSpawn->hasCharacter()){
                newVec.emplace_back(curSpawn);
            }
        }
    }
    return newVec;
}


PC* Floor::checkPC(int i, int j){
    vector<vector<int>> newCords = genEightCord(i,j);
    vector<Spawn *> newVec;
    for (int i = 0; i < 8; ++i) {
        int newR = newCords[i][0];
        int newC = newCords[i][1];
        Cell *curCell = cellList[newR][newC];
        
        if(curCell->getType() == '.')
        {
            
            Spawn *curSpawn = dynamic_cast<Spawn *>(curCell);
            
            if(!(curSpawn->hasCharacter()))
            {
                continue;
            }
            
            
            
            if (curSpawn->getCharacter()->getName() == '@')
            {
                PC *p = dynamic_cast<PC*>(curSpawn->getCharacter());
                return p;
            }
        }
    }
    return nullptr;
}



void Floor::playerUsePotion(string dir) {
    int curRow = player->getRow();
    int curCol = player->getCol();
    
    // compute new position x and y
    int newRow = curRow;
    int newCol = curCol;
    if (dir == "no") {
        --newRow;
    }
    if (dir == "so") {
        ++newRow;
    }
    if (dir == "ea") {
        ++newCol;
    }
    if (dir == "we") {
        --newCol;
    }
    if (dir == "ne") {
        --newRow;
        ++newCol;
    }
    if (dir == "nw") {
        --newCol;
        --newRow;
    }
    if (dir == "se") {
        ++newCol;
        ++newRow;
    }
    if (dir == "sw") {
        --newCol;
        ++newRow;
    }
    
    
    if (cellList[newRow][newCol]->getType() == '.') {
        Spawn *s = dynamic_cast<Spawn*>(cellList[newRow][newCol]);
        if(s->hasItem()) {
            if (s->getItem()->getType() == 'P'){
                Potion * p = dynamic_cast<Potion *>(s->getItem());
                if (p) {
                    Drow *d = dynamic_cast<Drow *>(player);
                    if(d) {
                        p->useItem(150);
                    } else {
                        p->useItem(100);
                    }
                    message->addMessage("PC uses " + p->getPotionType() +".");
                    s->putItem(nullptr);
                }
            }
        }
    }
}






void Floor::playerAttack(string dir) {
    int newCol = player->getCol();
    int newRow = player->getRow();
    if (dir == "no"){
        --newRow;
    }
    if (dir == "so") {
        ++newRow;
    }
    if (dir == "ea") {
        ++newCol;
    }
    if (dir == "ne") {
        --newRow;
        ++newCol;
    }
    if (dir == "we") {
        --newCol;
    }
    if (dir == "nw") {
        --newRow;
        --newCol;
    }
    if (dir == "sw") {
        --newCol;
        ++newRow;
    }
    if (dir == "se") {
        ++newRow;
        ++newCol;
    }
    
    Spawn * s = nullptr;
    
    if (cellList[newRow][newCol]->getType() == '.'){
        s = dynamic_cast<Spawn*>(cellList[newRow][newCol]);
        
        if (s->hasCharacter()) {
            
            Enemy * e = dynamic_cast<Enemy *> (s->getCharacter());
            
            if (e) {
                if (e->getName() == 'M'){
                    if(!hostile){
                        hostile=true;
                    }
                    
                }
                player->attack(e);
                int damage = e->getDamagePC();
                
                message->addMessage("PC deals " + to_string(0-damage) + " damages to " + e->getName() + "(" + to_string(e->getHP()) + " HP).");
                
                if (e->getHP() <= 0) {
                    if (e->getName()=='M')
                    {
                        
                        Item *h= new Normal{player};
                        itemList.emplace_back(h);
                        
                        // assign treasure
                        s->putItem(h);
                        s->putCharacter(nullptr);
                        
                    }
                    
                    
                    else if (e->getName() == 'H')
                    {
                        Item *hoardOne = new Normal{player};
                        Item *hoardTwo = new Normal{player};
                        itemList.emplace_back(hoardOne);
                        itemList.emplace_back(hoardTwo);
                        
                        int eRow = e->getRow();
                        int eCol = e->getCol();
                        
                        vector<Spawn*> newVec = scanEmptyEnemy(eRow, eCol);
                        
                        int size = newVec.size();
                        int ran = random(0,size-1);
                        
                        
                        
                        //assign treasure one
                        
                        s->putItem(hoardOne);
                        s->putCharacter(nullptr);
                        
                        //assign treasure two
                        
                        Spawn *chosen = newVec[ran];
                        chosen->putItem(hoardTwo);
                        
                    } else if (e->getName() == 'D') {
                        Dragon *d = dynamic_cast<Dragon *>(e);
                        Treasure *t = d->getHoard();
                        t->changeProtect(false);
                        s->putCharacter(nullptr);
                        
                    }
                    
                    else {
                        s->putCharacter(nullptr);
                        
                    }
                }
            }
        }
    }
}


