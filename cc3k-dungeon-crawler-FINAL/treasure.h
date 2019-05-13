#ifndef Treasure_hpp
#define Treasure_hpp

#include "item.h"

class Treasure: public Item {
    int value;
    bool protect;
public:
    virtual ~Treasure();
    Treasure(int, bool, PC* player, char itemType = 'G');
    int getValue();
    bool isProtect();
    void useItem(int mag=1) override;
    void changeProtect(bool);
};

class Small: public Treasure {
public:
    Small(PC* player);
    ~Small() override;
};

class Normal: public Treasure {
public:
    Normal(PC* player);
    ~Normal() override;
};

class MH: public Treasure {
public:
    MH(PC* player);
    ~MH() override;
};

class DH: public Treasure {
public:
    DH(PC* player);
    ~DH() override;
};

#endif /* Treasure_hpp */
