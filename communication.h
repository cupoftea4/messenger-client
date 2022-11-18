#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <functional>
#include <string>

class Communication {

public:
    virtual ~Communication() {};
    virtual bool init() = 0;
    virtual bool isInited() = 0;
    virtual bool isServer() = 0;
    virtual void sendMessage(std::wstring) = 0;
    virtual void setMessageReceiver(std::function<void(std::wstring)>) = 0;
    virtual void disconnect() = 0;

};

#endif // COMMUNICATION_H
