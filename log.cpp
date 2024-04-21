#include "log.h"

Log *Log::instance = nullptr;

Log::Log(int maxItems) : maxItems(maxItems) {}

void Log::draw(int y, int x, int width, int height) const {
    Console &c = *Console::getInstance();
    int borderY = y++;
    int borderX = x++;
    int borderHeight = height;
    int borderWidth = width;

    c.drawRectangle(borderY, borderX, borderHeight, borderWidth);

    height -= 2;
    width -= 2;
    int newY = y;
    for (const auto &message: messages) {
        if (newY >= y + height) {
            break;
        }
        c << moveCursor(newY++, x) << message.substr(0, width) << flushBuffer;
    }

    c.drawBorder(borderY, borderX, borderHeight, borderWidth, "Log");
}

void Log::add(const std::string &message) {
    messages.push_front(message);
    if (messages.size() > maxItems) {
        messages.pop_back();
    }
}

[[maybe_unused]] void Log::clear() {
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


