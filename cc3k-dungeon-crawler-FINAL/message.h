#ifndef _MESSAGE_H_
#define _MESSAGE_H_
#include <iostream>
#include <string>

class Message {
    std::string action;
public:
    Message();
    ~Message();
    void clearMessage();
    void addMessage(std::string act);
    void getMessage();
};

#endif
