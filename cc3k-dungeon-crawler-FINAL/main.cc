#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "floor.h"
#include "pc.h"
#include "character.h"

using namespace std;


int main(int argc, char* argv[]) {
    srand(time(0));
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd;
    int level = 1;
    bool isFrozen = false;
    bool hostile = false;
    bool specialInit = false;
    bool loop = false;
    string race;
    
    
    ifstream fs;
    string s;
    vector<vector<vector<int>>> v1;
    if(argc >= 2){
        specialInit = true;
        fs.open(argv[1]);
        for(int h = 0; h < 5; ++h){
            vector<vector<int>> layerOneV;
            for(int i = 0; i < 25; ++i){
                vector<int> layerTwoV;
                getline(fs,s);
                for(int j = 0; j < 79; ++j){
                    if (s[j] == ' ')
                    {
                        layerTwoV.emplace_back(18);
                    }
                    else if (s[j] == '-')
                    {
                        layerTwoV.emplace_back(19);
                    }
                    else if (s[j] == '|')
                    {
                        layerTwoV.emplace_back(20);
                    }
                    else if (s[j] == '#')
                    {
                        layerTwoV.emplace_back(21);
                    }
                    else if (s[j] == '.')
                    {
                        layerTwoV.emplace_back(22);
                        
                    }
                    else if (s[j] == '+')
                    {
                        layerTwoV.emplace_back(23);
                        
                    }
                    else if (s[j] == '\\')
                    {
                        layerTwoV.emplace_back(24);
                        
                    }
                    else if (s[j] == '0'){
                        layerTwoV.emplace_back(0);
                    }
                    else if (s[j] == '1'){
                        layerTwoV.emplace_back(1);
                    }
                    else if (s[j] == '2'){
                        layerTwoV.emplace_back(2);
                    }
                    else if (s[j] == '3'){
                        layerTwoV.emplace_back(3);
                    }
                    else if (s[j] == '4'){
                        layerTwoV.emplace_back(4);
                    }
                    else if (s[j] == '5'){
                        layerTwoV.emplace_back(5);
                    }
                    else if (s[j] == '6'){
                        layerTwoV.emplace_back(6);
                    }
                    else if (s[j] == '7'){
                        layerTwoV.emplace_back(7);
                    }
                    else if (s[j] == '8'){
                        layerTwoV.emplace_back(8);
                    }
                    else if (s[j] == '9'){
                        layerTwoV.emplace_back(9);
                    }
                    else if (s[j] == 'L'){
                        layerTwoV.emplace_back(10);
                    }
                    else if (s[j] == 'W'){
                        layerTwoV.emplace_back(11);
                    }
                    else if (s[j] == 'E'){
                        layerTwoV.emplace_back(12);
                    }
                    else if (s[j] == 'H'){
                        layerTwoV.emplace_back(13);
                    }
                    else if (s[j] == 'O'){
                        layerTwoV.emplace_back(14);
                    }
                    else if (s[j] == 'M'){
                        layerTwoV.emplace_back(15);
                    }
                    else if (s[j] == 'D'){
                        layerTwoV.emplace_back(16);
                    }
                    else if (s[j] == '@'){
                        layerTwoV.emplace_back(17);
                    } else {
                        layerTwoV.emplace_back(30);
                    }
                }
                layerOneV.emplace_back(layerTwoV);
            }
            v1.emplace_back(layerOneV);
        }
    }
    
    if(argc >= 2) {
        fs.close();
    }
    
    
    
    cout << "choose your role" << endl;
    cout << "s for shade" << endl;
    cout << "d for drow" << endl;
    cout << "v for vampire" << endl;
    cout << "t for troll" << endl;
    cout << "g for goblin" << endl;
    cout << "q for quit" << endl;
    
    string role;
    PC *player = nullptr;
    while (getline(cin, role)) {
        
        if (role == "s" || role == "") {
            player = new Shade;
            race = "Shade";
            break;
        } else if (role == "d") {
            player = new Drow;
            race = "Drow";
            break;
        } else if (role == "v") {
            player = new Vampire;
            race = "Vampire";
            break;
        } else if (role == "t") {
            player = new Troll;
            race = "Troll";
            break;
        } else if (role == "g"){
            player = new Goblin;
            race = "Goblin";
            break;
        } else if (role == "q"){
            cout << "Quiting" << endl;
            return 0;
        } else {
            cout << "Invalid role" << endl;
        }
    }
    
    
    
    
    while (level < 6) {
        
        cout << "Entering level " << level << endl;
        player->initAtkDef();
        Floor f(player, isFrozen, hostile);
        
        
        if(argc >= 2){
            f.sInit(player, v1, level-1);
        } else {
            f.genEmptyFloor();
            f.init(player);
        }
        
        string direction;
        string cmd;
        
        cout << "Race: " << race << " Gold: " << player->getGold() << "                                                  Floor " << level << endl;
        cout << "HP: " << player->getHP() << endl;
        cout << "Atk: " << player->getAtk() << endl;
        cout << "Def: " << player->getDef() << endl;
        cout << "Action: ";
        if (level == 1 && cmd =="") {
            cout << "Player character has spawned." << endl;
        }else {
            f.printMessage();
        }
        
        cout<< "Enter a direction: " <<endl;
        
        
        
        
        while (getline(cin, cmd))
        {
            if (cmd == "q")
            {
                cout << "Quiting" << endl;
                
                f.clearFloor();
                delete player;
                return 0;
            }
            if (!loop && (cmd == "no" || cmd=="so" || cmd == "ea" || cmd == "we"
                          || cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw" ))
            {
                if (f.movePlayer(cmd) == false)
                {
                    level++;
                    cout << "Entering level " << level << endl;
                    break;
                }
            }
            else if (!loop && ((cmd == "a no") || (cmd == "a so") || (cmd == "a ea") || (cmd == "a we") || (cmd == "a nw") ||
                               (cmd == "a ne") || (cmd == "a se") || (cmd == "a sw")))
            {
                string dir;
                dir = cmd.substr(2,3);
                f.playerAttack(dir);
                if (player->die()) {
                    cout << "Lost" << endl;
                    cout << "To restart the game, enter in r, to quit, enter in q" << endl;
                    loop = true;
                }
            }
            else if (!loop && ((cmd == "u no") || (cmd == "u so") || (cmd == "u ea") || (cmd == "u we") || (cmd == "u nw") ||
                               (cmd == "u ne") || (cmd == "u se") || (cmd == "u sw")))
            {
                string dir;
                dir = cmd.substr(2,3);
                f.playerUsePotion(dir);
            }
            else if (!loop && (cmd == "b"))
            {
                level++;
                break;
            }
            else if (!loop && (cmd == "f"))
            {
                f.setFrozen();
                cout << "Enemy frozen" << endl;
                cout << "Enter a direction: " << endl;
                continue;
            }
            else if (cmd == "r"){
                // f.clearFloor();
                delete player;
                cout << "choose your role" << endl;
                cout << "s for shade" << endl;
                cout << "d for drow" << endl;
                cout << "v for vampire" << endl;
                cout << "t for troll" << endl;
                cout << "g for goblin" << endl;
                cout << "q for quit" << endl;
                while (getline(cin, role)) {
                    cout << role << endl;
                    if (role == "s" || role == "") {
                        player = new Shade;
                        race = "Shade";
                        break;
                    } else if (role == "d") {
                        player = new Drow;
                        race = "Drow";
                        break;
                    } else if (role == "v") {
                        player = new Vampire;
                        race = "Vampire";
                        break;
                    } else if (role == "t") {
                        player = new Troll;
                        race = "Troll";
                        break;
                    } else if (role == "g"){
                        player = new Goblin;
                        race = "Goblin";
                        break;
                    } else if (role == "q"){
                        cout << "Quiting" << endl;
                        delete player;
                        return 0;
                    } else {
                        cout << "Invalid role" << endl;
                    }
                }
                cmd = "";
                level = 1;
                player->initAll();
                loop = false;
                break;
            }
            
            if(!loop){
                
                f.updateEnemy();
                
                if (player->die()) {
                    cout << "LOST" << endl;
                    cout << "To restart the game, enter in r, to quit, enter in q" << endl;
                    loop = true;
                } else {
                    f.prettyPrint();
                    cout << "Race: " << race << " Gold: " << player->getGold() << "                                                  Floor " <<level << endl;
                    cout << "HP: " << player->getHP() << endl;
                    cout << "Atk: " << player->getAtk() << endl;
                    cout << "Def: " << player->getDef() << endl;
                    cout << "Action: ";
                    f.printMessage();
                    cout<< "Enter a direction: " <<endl;
                }
                
            }
            
            if(loop){
            }
            
        }
        
        isFrozen = f.getFrozen();
        hostile = f.getHostile();
        f.clearFloor();
    }
    
    if(!player->die()) {
        cout << "YOU WON!!!!!" << endl;
        int gold = player->getGold();
        if (role == "s") {
            gold = gold * 2;
        }
        cout << "Gold Amount: " << gold << endl;
        cout << "HP, Atk and Def: " << player->getHP() << " " << player->getAtk() << " " << player->getDef() << endl;
    }
    delete player;
}

