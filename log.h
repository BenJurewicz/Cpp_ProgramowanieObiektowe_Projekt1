#ifndef PROJEKT1CPP_LOG_H
#define PROJEKT1CPP_LOG_H

#include <list>
#include <string>

#include "console.h"

class Log {
    static Log *instance;

    int maxItems;
    std::list<std::string> messages;

    explicit Log(int maxItems);

public:
    static Log *init(int maxItems = 10);

    static Log *getInstance();

    static void destroyInstance();

    void draw(int y, int x) const;

    void add(const std::string &message);

    void clear();
};


#endif //PROJEKT1CPP_LOG_H
