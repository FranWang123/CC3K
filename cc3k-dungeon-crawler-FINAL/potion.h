
#ifndef potion_hpp
#define potion_hpp

#include "item.h"

class Potion: public Item {
protected:
    std::string potionType;
public:
    Potion(PC* = nullptr, char itemType = 'P');
    virtual ~Potion();
    std::string getPotionType();
    virtual void useItem(int mag) = 0;
};

class RH: public Potion {
public:
    RH(PC*);
    ~RH() override;
    void useItem(int mag) override;
};

class BA: public Potion {
public:
    BA(PC*);
    ~BA() override;
    void useItem(int mag) override;
};

class BD: public Potion {
public:
    BD(PC*);
    ~BD() override;
    void useItem(int mag) override;
};

class PH: public Potion {
public:
    PH(PC*);
    ~PH() override;
    void useItem(int mag) override;
};

class WA: public Potion {
public:
    WA(PC*);
    ~WA() override;
    void useItem(int mag) override;
};

class WD: public Potion {
public:
    WD(PC*);
    ~WD() override;
    void useItem(int mag) override;
};

#endif /* potion_hpp */
