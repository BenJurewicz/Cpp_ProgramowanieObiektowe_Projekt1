#include "log.h"

Log *Log::instance = nullptr;

Log::Log(int maxItems) : maxItems(maxItems) {}

void Log::draw(int y, int x) const {
    Console &c = *Console::getInstance();
    for (const auto &message: messages) {
        c << moveCursor(y++, x) << message << flushBuffer;
    }
}

void Log::add(const std::string &message) {
    messages.push_front(message);
    if (messages.size() > maxItems) {
        messages.pop_back();
    }
}

void Log::clear() {
    messages.clear();
}

Log *Log::init(int maxItems) {
    if (instance == nullptr) {
        instance = new Log(maxItems);
    }
    return instance;
}

Log *Log::getInstance() {
    if (instance == nullptr) {
        throw std::runtime_error("Log instance not created");
    }
    return instance;
}

void Log::destroyInstance() {
    delete instance;
    instance = nullptr;
}


