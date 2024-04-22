#include "log.h"

std::unique_ptr<Log> Log::instance = nullptr;

Log::Log(int maxItems) : maxItems(maxItems) {}

void Log::draw(int y, int x, int width) const {
    Console &c = *Console::getInstance();
    int borderY = y++;
    int borderX = x++;
    int borderWidth = width;

    c.drawRectangle(borderY, borderX, maxItems + 2, borderWidth);

    int height = maxItems;
    width -= 2;
    int newY = y;
    for (const auto &message: messages) {
        if (newY >= y + height) {
            break;
        }
        c << moveCursor(newY++, x) << message.substr(0, width) << flushBuffer;
    }

    c.drawBorder(borderY, borderX, maxItems + 2, borderWidth, "Log");
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
//        instance = new Log(maxItems);
        instance = std::unique_ptr<Log>(new Log(maxItems));
    }
    return instance.get();
}

Log *Log::getInstance() {
    if (instance == nullptr) {
        throw std::runtime_error("Log instance not created");
    }
    return instance.get();
}

void Log::destroyInstance() {
    instance.reset();
}


