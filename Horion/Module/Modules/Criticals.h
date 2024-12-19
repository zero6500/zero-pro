#pragma once
#include "Module.h"
#include <chrono> // لإضافة منطق الزمن

class Criticals : public IModule {
private:
    std::chrono::steady_clock::time_point lastCriticalTime; // لتسجيل وقت آخر ضربة

public:
    Criticals();
    ~Criticals();

    // Inherited via IModule
    virtual const char* getModuleName() override;
    virtual void onSendPacket(C_Packet* packet) override;
};
