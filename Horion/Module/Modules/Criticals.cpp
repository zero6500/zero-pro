#include "Criticals.h"
#include <chrono> // لإدارة الزمن

Criticals::Criticals() : IModule(0, Category::COMBAT, "Each hit is a critical hit") {
    lastCriticalTime = std::chrono::steady_clock::now(); // تعيين الوقت الأولي
}

Criticals::~Criticals() {
}

const char* Criticals::getModuleName() {
    return ("Criticals");
}

void Criticals::onSendPacket(C_Packet* packet) {
    if (packet->isInstanceOf<C_MovePlayerPacket>() && g_Data.getLocalPlayer() != nullptr) {
        // حساب الوقت الحالي
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastCriticalTime);

        // التحقق من مرور 3 ثوانٍ
        if (elapsedTime.count() >= 3) {
            C_MovePlayerPacket* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
            movePacket->onGround = false;

            // تحديث وقت آخر ضربة
            lastCriticalTime = currentTime;
        }
    }
}
