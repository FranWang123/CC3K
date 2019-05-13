#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include "chamber.h"
using namespace std;

int random1(int x, int y){
    int ran;
    ran = x + (rand() % (y - x + 1));
    return ran;
}

Chamber::Chamber(int chamberNumber, bool hasP): chamberNumber{chamberNumber}, hasP{hasP}{}

Chamber::~Chamber() {}

Spawn* Chamber::findSpawn(int row, int col){
    for (auto s: emptySpawn) {
        if(s->getRow() == row && s->getCol() == col){
            return s;
        }
    }
    return nullptr;
}



void Chamber::addSpawn(Spawn *s) {
    emptySpawn.emplace_back(s);
}

void Chamber::print(){
    int size = emptySpawn.size();
    cout << size;
    for (int i = 0; i < size; ++i){
        cout << emptySpawn[i]->getType();
    }
    cout << endl;
}


int Chamber::getEmptyAmount() {
    return emptySpawn.size();
}


vector<Spawn *> Chamber::getEmptySpawn() {
    return emptySpawn;
}

void Chamber::assignItem(Item *i){
    int ran;
    if (emptySpawn.size() == 0) {
        ran = 0;
    }else {
        ran= random1(0, emptySpawn.size()-1);
    }
    emptySpawn[ran]->putItem(i);
    int row = emptySpawn[ran]->getRow();
    int col = emptySpawn[ran]->getCol();
    i->changePosition(row, col);
    eraseEmptySpawn(row, col);
}


void Chamber::assignCharacter(Character *c){
    int ran;
    if (emptySpawn.size() <= 0){
    }
    else
    {
        ran= random1(0, emptySpawn.size()-1);
        while(emptySpawn[ran]->hasCharacter()){
            ran= random1(0, emptySpawn.size()-1);
        }
        Spawn *s = emptySpawn[ran];
        int row = s->getRow();
        int col = s->getCol();
        c->changePosition(row, col);
        s->putCharacter(c);
        eraseEmptySpawn(row, col);
        
        
        if (c->getName() == '@') {
            hasP = true;
        }
    }
}


vector<vector<int>> generateEightCord(int i, int j) {
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

void Chamber::assignTreasure(Treasure *t, Dragon *d){
    int ran;
    if (emptySpawn.size() == 0) {
        ran = 0;
    }else {
        ran= random1(0, emptySpawn.size()-1);
    }
    
    Spawn *newS = emptySpawn[ran];
    int tRow = newS->getRow();
    int tCol = newS->getCol();
    newS->putItem(t);
    eraseEmptySpawn(tRow, tCol);
    
    t->changePosition(tRow, tCol);
    
    vector<Spawn*> newVec;
    vector<vector<int>> intVec = generateEightCord(tRow, tCol);
    
    for (int i = 0; i < 8 ; ++i) {
        int r = intVec[i][0];
        int c = intVec[i][1];
        Spawn *s = findSpawn(r, c);
        if(s!=nullptr){
            newVec.emplace_back(s);
        }
    }
    
    int size = newVec.size();
    int ranD= random1(0, size-1);
    
    
    
    Spawn *dragonSpawn = newVec[ranD];
    dragonSpawn->putCharacter(d);
    
    int dRow = dragonSpawn->getRow();
    int dCol = dragonSpawn->getCol();
    
    
    d->changePosition(dRow, dCol);
    eraseEmptySpawn(dRow, dCol);
}


bool Chamber::hasPlayer(){
    return hasP;
}



int Chamber::getNum(){
    return chamberNumber;
}


void Chamber::eraseEmptySpawn(int i) {
    emptySpawn.erase(emptySpawn.begin() + i);
}


void Chamber::eraseEmptySpawn(int x, int y) {
    int index;
    for(int i = 0; i < emptySpawn.size(); ++i){
        if (emptySpawn[i]->getRow() == x && emptySpawn[i]->getCol() == y){
            index = i;
        }
    }
    emptySpawn.erase(emptySpawn.begin() + index);
}


